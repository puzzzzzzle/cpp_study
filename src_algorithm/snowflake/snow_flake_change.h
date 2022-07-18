/************************************************
 * @desc 改进的snowflake算法, 设计每ms生成4095个id, 过高将自旋等待
 *       依赖机器时间(ms), 如果时间被回调, 那么将陷入自旋等待, 并不断的告警
 *       通过的测试用例: 单次生成1亿个id并插入set, 不应有错误, 连续跑100次,
 *不应有错误 测试用例在我的练手项目中, 后续想办法搬过来
 *
 *       !!!多线程不安全, 如需多线程使用, 自行加锁!!!
 ************************************************/

#pragma once

#include <sys/time.h>

#include <chrono>
#include <ctime>
#include <mutex>

class SnowFlakeChange {
  private:
  int64_t m_epoch{};
  int64_t m_lastUpdateTime{};
  int64_t m_curr{};
  int m_id{};
  int m_sequence{};

  uint64_t GetNowMs() {
    struct timeval tv {};

    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
  }

  public:
  std::string DumpInfo() {
    std::stringstream oss{};
    oss << "m_epoch:\t" << m_epoch << "\n";
    oss << "m_lastUpdateTime:\t" << m_lastUpdateTime << "\n";
    oss << "m_curr:\t" << m_curr << "\n";
    oss << "m_id:\t" << m_id << "\n";
    oss << "m_sequence:\t" << m_sequence << "\n";
    return oss.str();
  }
  /**
   * 系统起始时间 ms
   * @param epoch
   */
  void SetEpoch(uint64_t epoch) { this->m_epoch = epoch; }
  /**
   * 序列的ID, 可以用来区分多个机器 或者 单个机器内区分不同的类型以提高效率
   * @param id
   */
  void SetID(int id) { this->m_id = id; }

  virtual int64_t Generate() {
    int64_t value{};
    int64_t timeGap{};
    // 防止时间回调  每ms不够时自旋等待的 snowflake
    while (true) {
      // 考虑到TNOW系列有可能用于假时间, 但是ID生成不能接受,
      // 还是使用自己的时间获取方式
      m_curr = GetNowMs();
      timeGap = m_curr - m_lastUpdateTime;
      // 防止时间被回调
      // 没人回调生产环境的时间吧? 如果真有人手贱改了生产环境的时间,
      // 就只能自旋等了
      if (timeGap < 0) {
        // ERROR("time go back!!! is any one change it ??? " << timeGap)
        continue;
      } else if (timeGap == 0) {
        if (m_sequence >= 0xFFF) {
          continue;
        } else {
          // 唯一出口, 会造成seq 0 不会出现 可接受
          ++m_sequence;
          break;
        }
      } else {
        m_sequence = 0;
        m_lastUpdateTime = m_curr;
        continue;
      }
    }

    // timeGap  始终为0 但是还是加一下好
    value |= (m_lastUpdateTime - m_epoch + timeGap)
             << 22;  // 41 位表示时间(自epoch 起 ms), 可用69.7年
    value |= m_id & 0x3FF << 12;  // 10 位(1024个) 表示机器ID或者类型ID,
                                  // 用来表示机器ID时, 可以做到多机唯一
    value |= m_sequence & 0xFFF;  // 12 位(4095个) 表示序列, 没毫秒4095个可用ID
    value &= 0x7FFFFFFFFFFFFFFF;  // 最高位不应该有数字强制抹去最高位
    return value;
  }
};

class ThreadSafeSnowFlake : public SnowFlakeChange {
  private:
  std::mutex m_lock{};

  public:
  /**
   * 多线程安全的获取唯一ID
   * @return
   */
  int64_t Generate() override {
    std::lock_guard<std::mutex> lockGard(m_lock);
    return SnowFlakeChange::Generate();
  }
};