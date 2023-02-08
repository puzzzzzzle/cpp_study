/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2023/2/7
 * @file kcp_server.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <atomic>
#include <functional>
#include <string>
#include <thread>

/* In Unix systems a file descriptor is a regular signed int, with -1
 * representing an invalid descriptor. In Windows it is a SOCKET
 * (32- or 64-bit unsigned integer depending on the architecture), where
 * all bits set (~0) is INVALID_SOCKET.  */
#ifdef _WIN32
#ifdef _WIN64
typedef unsigned long long SocketType; /* SOCKET = 64-bit UINT_PTR */
#else
typedef unsigned long SocketType; /* SOCKET = 32-bit UINT_PTR */
#endif
#define INVALID_SOCKET ((SocketType)(~0)) /* INVALID_SOCKET */
#include<winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
typedef int SocketType;
#define INVALID_SOCKET -1
#endif

namespace Udp {

struct SocketHandle {
  SocketType socket{};
  bool is_ip_v6{};
};
inline const SocketHandle UdpSocket(bool v6) {
  if (v6) {
    return {socket(AF_INET6, SOCK_DGRAM, 0), true};

  } else {
    return {socket(AF_INET, SOCK_DGRAM, 0), false};
  }
}
inline std::pair<sockaddr *, socklen_t> UdpStringToAddress(bool v6,
                                                           const char *ip,
                                                           int port) {
  sockaddr *ret_addr{};
  socklen_t addr_len{};
  if (v6) {
    auto *my_addr = new sockaddr_in6;
    ret_addr = (sockaddr *)my_addr;
    my_addr->sin6_family = AF_INET6;
    inet_pton(AF_INET6, ip, &(my_addr->sin6_addr));
    my_addr->sin6_port = htons(port);
    addr_len = sizeof(sockaddr_in6);
  } else {
    auto *my_addr = new sockaddr_in;
    ret_addr = (sockaddr *)my_addr;
    my_addr->sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(my_addr->sin_addr));
    my_addr->sin_port = htons(port);
    addr_len = sizeof(sockaddr_in);
  }
  return {ret_addr, addr_len};
}
inline std::pair<std::string, int> UdpAddrToString(bool v6,
                                                   const sockaddr *addr) {
  //  "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:12345" : ipv6 最大 45 个字符

  char buff[100]{0};
  if (v6) {
    auto my_addr = (sockaddr_in6 *)addr;
    inet_ntop(AF_INET6, &(my_addr->sin6_addr), buff, sizeof(buff));
    return {std::string(buff), ntohs(my_addr->sin6_port)};
  } else {
    auto my_addr = (sockaddr_in *)addr;
    inet_ntop(AF_INET, &(my_addr->sin_addr), buff, sizeof(buff));
    return {std::string(buff), ntohs(my_addr->sin_port)};
  }
}
inline int UdpBind(const SocketHandle &s, const char *ip, int port) {
  sockaddr *ret_addr{};
  socklen_t addr_len{};
  std::tie(ret_addr, addr_len) = UdpStringToAddress(s.is_ip_v6, ip, port);
  int ret = bind(s.socket, ret_addr, addr_len);
  delete ret_addr;
  return ret;
}
inline int UdpSetTimeout(const SocketHandle &s, bool is_recv, int us) {
  timeval t{};
  t.tv_sec = 0;
  t.tv_usec = us;
  int ret{};
  if (is_recv) {
    ret = setsockopt(s.socket, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t));
  } else {
    ret = setsockopt(s.socket, SOL_SOCKET, SO_SNDTIMEO, &t, sizeof(t));
  }
  return ret;
}

inline int UdpConn(const SocketHandle &s, sockaddr *init_addr,
                   socklen_t init_addr_len) {
  return connect(s.socket, init_addr, init_addr_len);
}
// 一些杂项配置
enum class UdpConfig {
  kUseIpV6,
  kBuffSize,
  kSendTimeOut,
  kRecvTimeOut,

  // 总是在最后
  kMax,
};
enum class WorkMode {
  kClient,
  kServer,
};
class NetException : public std::exception {
  std::string what_{};

  public:
  NetException() = default;
  NetException(std::string what) : what_(what) {}

  public:
  const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
    return what_.c_str();
  }
};
// Udp server
// 非多线程安全
// 传入的数据， 如果不能立即处理， 需要拷贝走， 下一个请求的会立马覆盖
using RecvFunc =
    std::function<void(char *buff, ssize_t len, const sockaddr *addr,
                       socklen_t addr_len, bool is_ip_v6)>;
class Udp final {
  public:
  private:
  // socket handle
  SocketHandle socket_;
  bool inited_{};

  // 配置等
  int conf_[(int)UdpConfig::kMax]{};
  // buf
  // udp 最大可发送2^16-head的数据
  // 但是不建议大于mtu， 过大的包会被拆分为mtu大小的包
  // 任何一个丢包， 都会导致大包整体丢包
  ssize_t buf_len_{};
  char *buf_{};
  // 表示本次接受到数据来源
  // client 模式下只是拿来校验
  sockaddr *recv_addr_{};
  socklen_t recv_addr_len_{};

  // 工作模式
  WorkMode mode_{};
  // client 模式下表示服务器的ip port
  // server 模式下表示服务器监听的ip port
  std::string ip_{};
  int port_{};

  public:
  Udp() = default;
  Udp(const Udp &) = delete;
  Udp(const Udp &&) = delete;
  Udp &operator=(const Udp &) = delete;
  Udp &operator=(const Udp &&) = delete;
  ~Udp() {
    delete[] buf_;
    delete recv_addr_;
    Close();
  }
  /**
   * 获取杂项配置
   * @param k
   * @param default_value
   * @return
   */
  int GetConf(UdpConfig k, int default_value = 0) {
    if (conf_[(int)k] == 0) {
      return default_value;
    }
    return conf_[(int)k];
  }
  /**
   * 设置杂项配置
   * @param conf
   * @param value
   * @return
   */
  Udp &Config(UdpConfig k, int value) {
    conf_[(int)k] = value;
    return *this;
  }

  private:
  void Init() {
    if (inited_) {
      throw NetException("already Bind");
    }
    inited_ = true;
    socket_ = UdpSocket(GetConf(UdpConfig::kUseIpV6, false));
    buf_len_ = GetConf(UdpConfig::kBuffSize, UINT16_MAX);
    buf_ = new char[buf_len_];
    if (socket_.is_ip_v6) {
      recv_addr_ = (sockaddr *)(new sockaddr_in6);
      recv_addr_len_ = sizeof(sockaddr_in6);
    } else {
      recv_addr_ = (sockaddr *)(new sockaddr_in);
      recv_addr_len_ = sizeof(sockaddr_in);
    }
  }

  public:
  /**
   * 设置进入server模式并绑定
   * 初始化， 之后就不允许再调整配置了
   * @return
   */
  Udp &Bind() {
    Init();
    mode_ = WorkMode::kServer;
    int ret = UdpBind(socket_, ip_.c_str(), port_);
    if (ret) {
      throw NetException("UdpBind fail " + std::to_string(ret));
    }
    // 每 100 ms timeout一次， 方便线程退出
    UdpSetTimeout(socket_, true, GetConf(UdpConfig::kRecvTimeOut, 1000 * 100));
    // 发送超时
    UdpSetTimeout(socket_, false,
                  GetConf(UdpConfig::kSendTimeOut, 1000 * 3000));
    return *this;
  }
  /**
   * 设置进入client模式， 并虚拟连接
   * 即使服务器不存在，也会conn成功
   * @return
   */
  Udp &Conn() {
    Init();
    mode_ = WorkMode::kClient;
    // 设置服务器地址
    sockaddr *init_addr{};
    socklen_t init_addr_len{};
    std::tie(init_addr, init_addr_len) =
        UdpStringToAddress(socket_.is_ip_v6, ip_.c_str(), port_);
    int ret = UdpConn(socket_, init_addr, init_addr_len);
    delete init_addr;
    if (ret) {
      throw NetException("UdpConn fail " + std::to_string(ret));
    }
    // 接收超时
    UdpSetTimeout(socket_, true, GetConf(UdpConfig::kRecvTimeOut, 1000 * 3000));
    // 发送超时
    UdpSetTimeout(socket_, false,
                  GetConf(UdpConfig::kSendTimeOut, 1000 * 3000));
    return *this;
  }
  /**
   * 设置地址
   * @param ip
   * @param port
   * @return
   */
  Udp &Address(const std::string &ip, int port) {
    ip_ = ip;
    port_ = port;
    return *this;
  }
  /**
   * 关闭server
   */
  void Close() {
    if (socket_.socket == INVALID_SOCKET) {
      return;
    }
    int ret = close(socket_.socket);
    if (ret) {
      //      throw NetException("UdpClose fail " + std::to_string(ret));
    }
    socket_.socket = INVALID_SOCKET;
  }
  /**
   * 本对象的缓存信息
   * 可以值获取一次， 多次使用
   * 对象存活期间均可用， 且地址不会变
   * @return
   */
  std::tuple<sockaddr *, socklen_t *, char *, ssize_t> GetBuf() {
    return {recv_addr_, &recv_addr_len_, buf_, buf_len_};
  }
  /**
   * 接受数据， 并写在本对象的缓存中
   * 在下一次Recv()前可用
   * 获取到的数据指向 GetBuf()
   * @return
   */
  ssize_t Recv() {
    ssize_t ret{};
    if (mode_ == WorkMode::kClient) {
      // client 只从绑定的server接收
      ret = recv(socket_.socket, buf_, buf_len_, 0);
    } else {
      // server 接收任意来源的数据， 并且保存来源地址
      ret = recvfrom(socket_.socket, buf_, buf_len_, 0, recv_addr_,
                     &recv_addr_len_);
    }
    return ret;
  }
  ssize_t ClientSend(const char *buf, ssize_t buf_len) {
    if (mode_ != WorkMode::kClient) {
      throw NetException("only for client mode");
    }
    if (buf_len <= 0) {
      return 0;
    }
    ssize_t write_len = 0;
    while (true) {
      auto len = send(socket_.socket, buf + write_len, buf_len - write_len, 0);
      if (len < 0) {
        return -1;
      }
      write_len += len;
      if (write_len >= buf_len) {
        break;
      }
    }
    return write_len;
  }
  ssize_t SendTo(const char *buf, ssize_t buf_len, const sockaddr *addr,
                 socklen_t addr_len) {
    if (buf_len <= 0) {
      return 0;
    }
    ssize_t write_len = 0;
    while (true) {
      write_len += sendto(socket_.socket, buf, buf_len, 0, addr, addr_len);
      if (write_len >= buf_len) {
        break;
      }
    }
    return write_len;
  }
  std::string AddrToString(const sockaddr *addr) {
    if (addr == nullptr) {
      return "nullptr";
    }
    const auto [ip, port] = UdpAddrToString(socket_.is_ip_v6, addr);
    return ip + ":" + std::to_string(port);
  }
};
}  // namespace Udp
