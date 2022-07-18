//
// Created by khalidzhang on 2021/10/19.
//

#pragma once
#include "auto_wired.h"
extern AutoWiredImpl<> g_autoWired;

class Test1{
  int * a_1{};
  AUTO_WIRED(g_autoWired,a_1)
};