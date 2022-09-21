/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2022/9/21
 * @file mem_gap.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#include <fcntl.h>
#include <malloc.h>

#include <fstream>
#include <sstream>
#include <string>

struct CurrProcessMemInfo {
  size_t m_inUse{};
};

class MemGap {
  private:
  CurrProcessMemInfo m_info{};

  public:
  MemGap() { m_info = GetCurrProcessMem(); }
  CurrProcessMemInfo GetCurrProcessMem() {
    // crete buff
    char* buffer = NULL;
    size_t bufferSize = 0;
    auto ss = open_memstream(&buffer, &bufferSize);

    // get status
    int ret = malloc_info(0, ss);
    fflush(ss);
    if (ret) {
      fprintf(stderr, "call malloc_info fail %d", ret);
      return {};
    }

    // parse memInfo
    printf("%s\n", buffer);
    CurrProcessMemInfo info{};

    // close
    fclose(ss);
    free(buffer);

    {
      auto procName =
          std::string("/proc/" + std::to_string(getpid()) + "/status");
      std::fstream procFile(procName, std::ios::in);
      std::ostringstream oss{};
      while (procFile.good() && !procFile.eof())
      {
        std::string temp{};
        procFile>>temp;
        oss<<temp<<"\n";
      }
      printf("%s\n", oss.str().c_str());
    }
    return info;
  }
};