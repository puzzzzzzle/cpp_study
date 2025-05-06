#include <filesystem>

#include "common_includes.h"
namespace fs = std::filesystem;

TEST(path, 1) {
  fs::path p("./");
  LOG_DEBUG(p)
  p = fs::absolute(p);
  LOG_DEBUG(p)

  ASSERT_TRUE(exists(p));
  ASSERT_TRUE(is_directory(p));
  for (const auto& item : fs::directory_iterator(p)) {
    LOG_DEBUG(item.path() << "\t" << item.path().filename())
  }
  auto dataPath = p / "data";
  if (fs::exists(dataPath) && fs::is_directory(dataPath)) {
    LOG_DEBUG("data exists, copy one")

    fs::remove_all(p / "data_copy");
    // 直接拷贝, 会把软连接变为普通文件
    //    fs::copy(dataPath,p/"data_copy");
    //
    fs::copy(dataPath, p / "data_copy",
             fs::copy_options::copy_symlinks | fs::copy_options::recursive);
  }
  bool throwErr = false;
  try {
    fs::copy("not_exists", p / "111");
  } catch (const fs::filesystem_error& r) {
    throwErr = true;
  }
  ASSERT_TRUE(throwErr);
}

int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}