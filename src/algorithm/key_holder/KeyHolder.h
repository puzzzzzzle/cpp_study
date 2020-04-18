/************************************************
 * @author khalidzhang
 * @email khalidzhang@tencent.com
 * @desc 管理不重复的单元, 并实现O1时间的 添加 删除 随机选择
 * @time 2020/3/12
 * @file KeyHolder.h
 * @version
 * version        author            desc
 * 1.0            khalidzhang       create
 ************************************************/

#pragma once
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>

#define RAND(begin, end) ((rand() % ((end) - (begin))) + (begin))

 template<class KeyType >
class KeyHolder {
private:
    KeyType *              keys{};
    int                    point{0};
    const int              MAX_SIZE;
    std::unordered_map<KeyType, int> keyMap{};

public:
    KeyHolder(KeyHolder &)  = delete;
    KeyHolder(KeyHolder &&) = delete;

    KeyHolder(int maxSize) : MAX_SIZE(maxSize) { keys = new KeyType[maxSize]; }
    ~KeyHolder() {
        if (keys != nullptr) {
            delete[] keys;
            keys = nullptr;
        }
    }
    int Add(const KeyType &key) {
        if (point >= MAX_SIZE) {
            return -2;
        }
        keys[point] = key;
        auto ret    = keyMap.insert(std::make_pair(key, point));
        if (!ret.second) {
            return -1;
        }
        ++point;
        return 0;
    }
    int Rand(KeyType *outKey) {
        if (point == 0) {
            return 1;
        }
        int randNum = RAND(0, point);
        (*outKey)   = keys[randNum];

        return 0;
    }
    int Remove(const KeyType &key) {
        auto it = keyMap.find(key);
        if (it == keyMap.end()) {
            return -1;
        }
        int index = it->second;

        // 和最后一个交换位置
        keys[index]         = keys[point - 1];
        keyMap[keys[index]] = keys[index];
        --point;

        // 移除
//        if (keyMap.erase(key) != 1) {
//            return -1;
//        }

        return 0;
    }
};