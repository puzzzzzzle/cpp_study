#pragma once

#ifdef TIMER_MOVE_SIZE
#error "TIMER_MOVE_SIZE already def"
#endif

#define TIMER_MOVE_SIZE 0x7ff

class DefTest {
public:
    int test() { return 0; }
};
