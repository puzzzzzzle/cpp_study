/
// Created by tao on 19-3-29.
//

#ifndef PERSONAL_FILE_PROTECTOR_COMMON_CLASSES_H
#define PERSONAL_FILE_PROTECTOR_COMMON_CLASSES_H
#include <stdlib.h>

#include <mutex>

    class LockGround {
    std::mutex *mlock;

public:
    LockGround(std::mutex *_lock) : mlock(_lock) { mlock->lock(); }

    ~LockGround() { mlock->unlock(); }
};
#endif  // PERSONAL_FILE_PROTECTOR_COMMON_CLASSES_H
