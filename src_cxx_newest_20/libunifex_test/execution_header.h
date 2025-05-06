/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2022/9/1
 * @file execution_head.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once

#if true
#include <unifex/just.hpp>
#include <unifex/let_done.hpp>
#include <unifex/scheduler_concepts.hpp>
#include <unifex/sequence.hpp>
#include <unifex/static_thread_pool.hpp>
#include <unifex/stop_when.hpp>
#include <unifex/sync_wait.hpp>
#include <unifex/then.hpp>
#include <unifex/timed_single_thread_context.hpp>
#include <unifex/when_all.hpp>
using namespace unifex;
#else
#error "cannot use std execution now"
#endif