//
// Created by khalidzhang on 2023/1/21.
//
#include "common_includes.h"
#include <fstream>
TEST(read,1)
{
  LOG_DEBUG("read file ")
  std::ifstream in("./data/boost_log_settings.ini",std::ios::binary|std::ios::in);
  ASSERT_TRUE(in.good());
  char buff[1024];
  size_t len{};
  std::ostringstream oss{};
  while (len = in.readsome(buff,sizeof (buff)))
  {
    for(size_t i = 0;i<len;++i)
    {
      isprint()
      oss<<buff[i];
    }
  }
  LOG_DEBUG(oss.str())
}