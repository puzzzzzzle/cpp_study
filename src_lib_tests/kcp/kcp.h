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
  kNodelay,
  kInterval,
  kResend,
  kNc,
  kSndwnd,
  kRcvwnd,
  kMtu,
  kRto,

  kMax,
};
class KcpServer {
  private:

  public:
      KcpServer() = default;
      KcpServer(const KcpServer &) = delete;
      KcpServer(const KcpServer &&) = delete;
      KcpServer &operator=(const KcpServer &) = delete;
      KcpServer &operator=(const KcpServer &&) = delete;
  /**
   * 设置杂项配置
   * @param conf
   * @param value
   * @return
   */
  KcpServer &Config(KcpConfig k, int value) {
  }


};
}  // namespace Kcp