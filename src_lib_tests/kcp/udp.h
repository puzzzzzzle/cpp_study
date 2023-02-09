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
#include <cerrno>
#include <cstring>
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
#include <winsock2.h>
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
struct SocketAddr {
  union {
    sockaddr_in v4;
    sockaddr_in6 v6;
  };
  inline bool IsV4() const { return ((sockaddr *)this)->sa_family == AF_INET; }
  inline bool IsV6() const { return ((sockaddr *)this)->sa_family == AF_INET6; }
  inline socklen_t CSize() const {
    if (IsV4()) {
      return sizeof(sockaddr_in);
    } else if (IsV6()) {
      return sizeof(sockaddr_in6);
    } else {
      return sizeof(SocketAddr);
    }
  }
  inline sockaddr *AsCAddr() const { return (sockaddr *)this; }
  static SocketAddr FromAddress(bool v6, const char *ip, int port) {
    SocketAddr out{};
    if (v6) {
      auto *my_addr = &out.v6;
      memset(my_addr, 0, sizeof(sockaddr_in6));
      my_addr->sin6_family = AF_INET6;
      inet_pton(AF_INET6, ip, &(my_addr->sin6_addr));
      my_addr->sin6_port = htons(port);
    } else {
      auto *my_addr = &out.v4;
      memset(my_addr, 0, sizeof(sockaddr_in));
      my_addr->sin_family = AF_INET;
      inet_pton(AF_INET, ip, &(my_addr->sin_addr));
      my_addr->sin_port = htons(port);
    }
    return out;
  }
  std::string IP() const {
    //  "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:12345" : ipv6 最大 45 个字符
    char buff[100]{"unknown"};
    if (IsV6()) {
      auto my_addr = (sockaddr_in6 *)&v6;
      inet_ntop(AF_INET6, &(my_addr->sin6_addr), buff, sizeof(buff));
    } else if (IsV4()) {
      auto my_addr = (sockaddr_in *)&v4;
      inet_ntop(AF_INET, &(my_addr->sin_addr), buff, sizeof(buff));
    }
    return std::string(buff);
  }
  int Port() const {
    if (IsV6()) {
      auto my_addr = (sockaddr_in6 *)&v6;
      return ntohs(my_addr->sin6_port);
    } else if (IsV4()) {
      auto my_addr = (sockaddr_in *)&v4;
      return ntohs(my_addr->sin_port);
    } else {
      return -1;
    }
  }
  std::string ToString() const { return IP() + ":" + std::to_string(Port()); }
};

inline const SocketHandle UdpSocket(bool v6) {
  if (v6) {
    return {socket(AF_INET6, SOCK_DGRAM, 0), true};

  } else {
    return {socket(AF_INET, SOCK_DGRAM, 0), false};
  }
}

inline int UdpBind(const SocketHandle &s, const SocketAddr &addr) {
  return bind(s.socket, addr.AsCAddr(), addr.CSize());
}
inline int UdpConn(const SocketHandle &s, const SocketAddr &addr) {
  return connect(s.socket, addr.AsCAddr(), addr.CSize());
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
  SocketAddr recv_addr_{};
  // 工作模式
  WorkMode mode_{};
  // client 模式下表示服务器的ip port
  // server 模式下表示服务器监听的ip port
  std::string ip_{};
  int port_{};
  // 上面的ip port对应的 addr
  SocketAddr init_addr_{};

  public:
  Udp() {}

  Udp(const Udp &) = delete;
  Udp(Udp &&input) {
      Move(std::move(input));
  };
  Udp &operator=(const Udp &) = delete;
  Udp &operator=(Udp &&input) {
      Move(std::move(input));
    return *this;
  };
  void Move(Udp &&input)
  {
    // 基础数据clone
    socket_ = input.socket_;
    inited_ = input.inited_;
    std::copy(std::begin(input.conf_), std::end(input.conf_),
              std::begin(conf_));
    // buff
    buf_len_ = input.buf_len_;
    buf_ = input.buf_;

    // recv_addr_
    recv_addr_ = input.recv_addr_;
    // 拷贝ip信息
    mode_ = input.mode_;
    ip_ = std::move(input.ip_);
    port_ = input.port_;
    init_addr_ = input.init_addr_;

    input.buf_ = nullptr;
    input.buf_len_ = 0;
  }
  ~Udp() {
    delete[] buf_;
    Close();
  }
  /**
   * 获取杂项配置
   * @param k
   * @param default_value
   * @return
   */
  int GetConf(UdpConfig k, int default_value = 0) const {
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
    init_addr_ = SocketAddr::FromAddress(socket_.is_ip_v6, ip_.c_str(), port_);
  }

  public:
  Udp Clone() const {
    if (!inited_) {
      throw NetException("already Bind");
    }
    Udp clone{};
    // 基础数据clone
    clone.socket_ = socket_;
    clone.inited_ = inited_;
    std::copy(std::begin(conf_), std::end(conf_), std::begin(clone.conf_));
    // buff新创建
    clone.buf_len_ = buf_len_;
    clone.buf_ = new char[buf_len_];

    // recv_addr_置空
    memset(&clone.recv_addr_, 0, sizeof(recv_addr_));
    // 拷贝ip信息
    clone.mode_ = mode_;
    clone.ip_ = ip_;
    clone.port_ = port_;
    clone.init_addr_ = init_addr_;
    return clone;
  }
  /**
   * 设置进入server模式并绑定
   * 初始化， 之后就不允许再调整配置了
   * @return
   */
  Udp &Bind() {
    Init();
    mode_ = WorkMode::kServer;
    int ret = UdpBind(socket_, init_addr_);
    if (ret) {
      throw NetException("UdpBind fail " + std::to_string(ret) +
                         " ;reason maybe: " + strerror(errno));
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

    int ret = UdpConn(socket_, init_addr_);
    if (ret) {
      throw NetException("UdpConn fail " + std::to_string(ret) +
                         " ; reason maybe: " + std::strerror(errno));
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
  const SocketAddr &InitAddress() const { return init_addr_; }
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
  std::tuple<SocketAddr *, char *, ssize_t> GetBuf() {
    return {&recv_addr_, buf_, buf_len_};
  }
  /**
   * 接受数据， 并写在本对象的缓存中
   * 在下一次Recv()前可用
   * 获取到的数据指向 GetBuf()
   * 不保证读完
   * @return
   */
  ssize_t Recv() {
    socklen_t socklen = recv_addr_.CSize();
    // server 接收任意来源的数据， 并且保存来源地址
    // client 由于调用过bind，  只从绑定的server接收
    auto len = recvfrom(socket_.socket, buf_, buf_len_, MSG_WAITALL,
                        recv_addr_.AsCAddr(), &socklen);
    return len;
  }
  ssize_t ClientSend(const char *buf, ssize_t buf_len) {
    if (mode_ != WorkMode::kClient) {
      throw NetException("only for client mode");
    }
    return SendTo(buf, buf_len, &init_addr_);
  }
  /**
   * 写， 不保证写完
   * @param buf
   * @param buf_len
   * @param addr
   * @return
   */
  ssize_t SendTo(const char *buf, ssize_t buf_len, const SocketAddr *addr) {
    auto len =
        sendto(socket_.socket, buf, buf_len, 0, addr->AsCAddr(), addr->CSize());

    return len;
  }
};
}  // namespace Udp
