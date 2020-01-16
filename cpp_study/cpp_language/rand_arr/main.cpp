//
// Created by tao on 19-1-17.
//
#include <sys/time.h>

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <set>

#include "common_includes.h"

/**
 * 随机一个不重复数组，通过map与交换实现，适合很大的范围中随机
 * @param iMiniNum 开始数字
 * @param iMaxNum 结束数字
 * @param iArrlen 数组输出的数组长度
 * @param aiOutArr 输出的数组
 */
void RandUinqueArr(int iMiniNum, int iMaxNum, int iArrlen, int aiOutArr[]) {
    assert(iMiniNum >= 0);
    assert(iMiniNum < iMaxNum);
    assert((iMaxNum - iMiniNum) >= iArrlen);
    std::map<int, int> swapInfo{};
    int                gap = iMaxNum - iMiniNum;
    for (int i = 0; i < gap && i < iArrlen; ++i) {
        // rand
        int randNum = rand() % (gap - i) + i;

        // find for swap
        auto lhs  = swapInfo.find(i);
        int  ilhs = lhs == swapInfo.end() ? i + iMiniNum : lhs->second;

        // find for out
        auto rhs  = swapInfo.find(randNum);
        int  irhs = rhs == swapInfo.end() ? randNum + iMiniNum : rhs->second;

        // swap
        swapInfo[i]       = irhs;
        swapInfo[randNum] = ilhs;
        aiOutArr[i]       = irhs;  // swapInfo[i]
    }
}

/**
 * 从给出的数组中随机找几个放在最前面
 * @param iInArrlen
 * @param aiInArr
 * @param iTargetArrlen
 */
void RandArrPos(int iInArrlen, int aiInArr[], int iTargetArrlen) {
    assert(iInArrlen >= iTargetArrlen);
    for (int i = 0; i < iTargetArrlen; ++i) {
        int randNum = rand() % (iInArrlen - i) + i;
        std::swap(aiInArr[i], aiInArr[randNum]);
    }
}

/**
 * 随机一个不重复数组,通过构建一个数组，然后交换元素实现
 * @param iMiniNum
 * @param iMaxNum
 * @param iArrlen
 * @param aiOutArr
 */
void RandUinqueArrByArrWarrper(int iMiniNum, int iMaxNum, int iArrlen, int aiOutArr[]) {
    int *arr = new int[iMaxNum - iMiniNum];
    for (int i = 0; i < iMaxNum - iMiniNum; ++i) {
        arr[i] = i + iMiniNum;
    }
    RandArrPos(iMaxNum - iMiniNum, arr, iArrlen);
    for (int i = 0; i < iArrlen; ++i) {
        aiOutArr[i] = arr[i];
    }
    delete[] arr;
}

/**
 * 随机一个不重复数组，通过set实现，当gap和iArrlen接近时，会有很大的碰撞几率，导致卡死
 * @param iMiniNum 开始数字
 * @param iMaxNum 结束数字
 * @param iArrlen 数组输出的数组长度
 * @param aiOutArr 输出的数组
 */
void RandUinqueArrBySet(int iMiniNum, int iMaxNum, int iArrlen, int aiOutArr[]) {
    assert(iMiniNum >= 0);
    assert(iMiniNum < iMaxNum);
    assert((iMaxNum - iMiniNum) >= iArrlen);
    int           gap = iMaxNum - iMiniNum;
    std::set<int> checkSet;
    for (int i = 0; i < gap && i < iArrlen;) {
        // rand
        int randNum = rand() % gap;
        if (checkSet.insert(randNum).second) {
            aiOutArr[i] = randNum + iMiniNum;  // swapInfo[i]
            ++i;
        }
    }
}

template <class T>
void printArr(int len, T value[], std::ostream &os) {
    os << "values :\t[";
    for (int i = 0; i < len; ++i) {
        os << value[i] << ", ";
    }
    os << "]" << std::endl;
}

// template <class T>
// bool checkDuplicated(int len, T value[])
//{
//    std::set<T> checkSet;
//    for (int i = 0; i < len; ++i)
//    {
//        if (!checkSet.insert(value[i]).second)
//        {
//            return false;
//        }
//    }
//    return true;
//}

int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    // testing::InitGoogleTest(&argc, argv);
    // iRet = RUN_ALL_TESTS();
    srand((unsigned int)time(NULL));

    int         start = 1000;
    std::string split = ",\t";
    int         gap[]{10, 100, 1000, 10000, 100000, 1000000, 10000000};
    int         targetLen[]{10, 100, 1000, 10000, 100000, 1000000, 10000000};
    int         setStopBar = 10000;
    for (unsigned int i = 0; i < sizeof(gap) / sizeof(gap[0]); ++i) {
        for (unsigned int j = 0; j < sizeof(targetLen) / sizeof(targetLen[0]); ++j) {
            if (targetLen[j] > gap[i]) {
                continue;
            }
            int *outArr = new int[targetLen[j]];
            int *inArr  = new int[gap[i]];
            if (outArr == nullptr || inArr == nullptr) {
                std::cout << "mem full" << std::endl;
                return -1;
            }
            std::cout << gap[i] << split << targetLen[j] << split << std::flush;

            for (int k = 0; k < gap[i]; ++k) {
                inArr[k] = k + start;
            }
            // time_t startTime = time(NULL);
            // time_t endTime = time(NULL);
            struct timeval startTime, endTime;

            gettimeofday(&startTime, NULL);
            RandArrPos(gap[i], inArr, targetLen[j]);
            for (int k = 0; k < targetLen[j]; ++k) {
                outArr[k] = inArr[k];
            }
            gettimeofday(&endTime, NULL);
            assert(checkDuplicated(targetLen[j], outArr));
            std::cout << (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec) << split
                      << std::flush;

            gettimeofday(&startTime, NULL);
            RandUinqueArrByArrWarrper(start, start + gap[i], targetLen[j], outArr);
            gettimeofday(&endTime, NULL);
            assert(checkDuplicated(targetLen[j], outArr));
            std::cout << (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec) << split
                      << std::flush;

            gettimeofday(&startTime, NULL);
            RandUinqueArr(start, start + gap[i], targetLen[j], outArr);
            gettimeofday(&endTime, NULL);

            assert(checkDuplicated(targetLen[j], outArr));
            std::cout << (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec) << split
                      << std::flush;

            gettimeofday(&startTime, NULL);
            RandUinqueArrBySet(start, start + gap[i], targetLen[j], outArr);
            gettimeofday(&endTime, NULL);
            assert(checkDuplicated(targetLen[j], outArr));
            std::cout << (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec)
                      << std::flush;

            std::cout << std::endl;
            delete[] outArr;
            delete[] inArr;
        }
    }

    return iRet;
}