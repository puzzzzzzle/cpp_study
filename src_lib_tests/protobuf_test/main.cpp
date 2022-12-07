//
// Created by tao on 19-1-17.
//
#include "addressbook.pb.h"
#include "common_includes.h"
#include "google/protobuf/util/json_util.h"
using namespace std;
namespace tutorial {
REGISTER(Person);
}

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

TEST(protobuf, 1) {
  tutorial::Person test;
  test.set_name("ahahahah");
  test.set_id(222);
  test.set_email("sefsgasdgfds");
  LOG_DEBUG("sizeof Person" << sizeof(test));
  // test.add_phones(tutorial::Person_PhoneNumber phone())
  string buff;
  google::protobuf::util::MessageToJsonString(test, &buff);
  cout << buff;
}
int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  //    testing::InitGoogleTest();
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}