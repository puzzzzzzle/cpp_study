#include <cpr/cpr.h>

#include "common_includes.h"

const char *TEST_URL = "http://www.baidu.com/";
TEST(cpr, simple) {
  auto rsp = cpr::Get(cpr::Url(TEST_URL));
  EXPECT_EQ(rsp.status_code, cpr::status::HTTP_OK);
  LOG_DEBUG(rsp.text);
}
TEST(cpr, with_header) {
//  cpr::Authentication auth{"name","passwd",cpr::AuthMode::BASIC};
  auto rsp = cpr::Get(cpr::Url(TEST_URL),cpr::Header{{"User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36"},{"Content-Type","text/plain"}});
  EXPECT_EQ(rsp.status_code, cpr::status::HTTP_OK);
  LOG_DEBUG(rsp.text);
}
TEST(cpr, async) {
  auto rsp_fu = cpr::GetAsync(cpr::Url(TEST_URL),cpr::Header{{"User-Agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36"},{"Content-Type","text/plain"}});
  LOG_DEBUG("get req send, wait rsp")
  auto rsp = rsp_fu.get();
  EXPECT_EQ(rsp.status_code, cpr::status::HTTP_OK);
  LOG_DEBUG(rsp.text);
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}