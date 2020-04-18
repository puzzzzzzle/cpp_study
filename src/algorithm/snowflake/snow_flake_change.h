/************************************************
 * @desc 改进的snowflake算法, 设计每ms生成4095个id, 过高将自旋等待
 *       依赖机器时间(ms), 如果时间被回调, 那么将陷入自旋等待, 并不断的告警
 *       通过的测试用例: 单次生成1亿个id并插入set, 不应有错误, 连续跑100次, 不应有错误
 *          测试用例在我的练手项目中, 后续想办法搬过来
 *
 *       !!!多线程不安全, 如需多线程使用, 自行加锁!!!
 ************************************************/

#pragma once

#include <sys/time.h>

#include <chrono>
#include <ctime>

const uint64_t getNowMs() {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
class SnowFlakeChange {
private:
    int64_t m_epoch{};
    int64_t m_lastUpdateTime{};
    int64_t curr{};
    int     m_id{};
    int     m_sequence{};

public:
    std::string DumpInfo() {
        std::stringstream oss{};
        oss << "m_epoch:\t" << m_epoch << "\n";
        oss << "m_lastUpdateTime:\t" << m_lastUpdateTime << "\n";
        oss << "curr:\t" << curr << "\n";
        oss << "m_id:\t" << m_id << "\n";
        oss << "m_sequence:\t" << m_sequence << "\n";
        return oss.str();
    }
    void SetEpoch(uint64_t epoch) {
        this->m_epoch = epoch;
        //        m_lastUpdateTime = epoch;
    }
    void SetID(int id) { this->m_id = id; }

    int64_t Generate() {
        int64_t value{};
        int64_t timeGap{};
        // 防止时间回调  每ms不够时自旋等待的 snowflake
        while (true) {
            curr    = getNowMs();
            timeGap = curr - m_lastUpdateTime;
            // 防止时间被回调
            // 如果真有人手贱改了生产环境的时间, 就只能自旋等了
            if (timeGap < 0) {
//                LOG_WARNING("time go back!!! is any one change it ??? " << timeGap)
                continue;
            } else if (timeGap == 0) {
                if (m_sequence >= 0xFFF) {
                    //                    LOG_WARNING("one time get too much id so spin lock")
                    continue;
                } else {
                    ++m_sequence;
                    break;
                }
            } else {
                //                LOG_DEBUG("reset seq " << m_sequence << "\t" << m_lastUpdateTime - m_epoch + timeGap)
                m_sequence       = 0;
                m_lastUpdateTime = curr;
                continue;
            }
        }

        value |= (m_lastUpdateTime - m_epoch + timeGap) << 22;
        value |= m_id & 0x3FF << 12;
        //        HTLOG_DEBUG("timeGap\t" << timeGap << "\tseq\t" << m_sequence)
        value |= m_sequence & 0xFFF;
        value &= 0x7FFFFFFFFFFFFFFF;  // 最高位不应该有数字强制抹去最高位
        return value;
    }
};