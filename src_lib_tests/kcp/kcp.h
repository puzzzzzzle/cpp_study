/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2023/2/8
 * @file kcp.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <ikcp.h>

#include "udp.h"
namespace Kcp {
enum class KcpConfig {
  // ikcp 配置
  kNodelay,
  kInterval,
  kResend,
  kNc,
  kSndwnd,
  kRcvwnd,
  kMtu,
  kRto,

  // kcp配置
  //  kWorkerNum,
  kMax,
};
class KcpException : public std::exception {
  std::string what_{};

  public:
  KcpException() = default;
  KcpException(const std::string &what) : what_(what) {}

  public:
  const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
    return what_.c_str();
  }
};
struct Connection {
  uint32_t conv;
  Udp::SocketAddr addr;
  ikcpcb *kcp_{};
};

class KcpServer {
  private:
  Udp::Udp udp_{};
  int conf_[(int)KcpConfig::kMax]{};
  std::unordered_map<uint32_t, Connection> conn_{};
  bool inited_{};

  // udp buf quick get
  char *udp_buf_{};
  Udp::SocketAddr *udp_recv_addr_;

  public:
  KcpServer() = default;
  KcpServer(const KcpServer &) = delete;
  KcpServer(const KcpServer &&) = delete;
  KcpServer &operator=(const KcpServer &) = delete;
  KcpServer &operator=(const KcpServer &&) = delete;
  void Init() {
    if (inited_) {
      throw KcpException("already inited");
    }
    if (!udp_.IsInited()) {
      throw KcpException("udp not inited");
    }
    inited_ = true;
    ssize_t udp_buf_len{};
    std::tie(udp_recv_addr_, udp_buf_, udp_buf_len) = udp_.GetBuf();
  }
  Udp::Udp &UdpNet() { return udp_; }
  /**
   * 获取杂项配置
   * @param k
   * @param default_value
   * @return
   */
  int GetConf(KcpConfig k, int default_value = 0) const {
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
  KcpServer &Config(KcpConfig k, int value) {
    conf_[(int)k] = value;
    return *this;
  }

  /**
   * 等待接收， block
   * @return
   */
  bool Recv() {
    auto size = udp_.Recv();
    // 最少要一个int， 获取conv
    if (size <= 4) {
      return false;
    }
    uint32_t conv{};
    memcpy(&conv,udp_buf_,4);
    return true;
  }
  /**
   * 等待发送， block， 不过udp缓冲区不满， 一般不会block
   * @return
   */
  bool Send() {
    return true;
  }
};
}  // namespace Kcp