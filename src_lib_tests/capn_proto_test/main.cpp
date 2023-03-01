#include <capnp/message.h>
#include <capnp/serialize.h>

#include "common_includes.h"
#include "myschema.capnp.h"

TEST(capnp, 1) {
  ::capnp::MallocMessageBuilder message{};
  {
    auto data = message.initRoot<Date>();
    data.setDay(23);
    data.setMonth(8);
    data.setYear(2023);
    LOG_DEBUG(data.toString().flatten().cStr())
  }

  auto arr = capnp::messageToFlatArray(message);

  ::capnp::FlatArrayMessageReader reader(arr);
  {
    auto data = reader.getRoot<Date>();
    LOG_DEBUG(data.toString().flatten().cStr())
  }
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  sleep(1);
  return iRet;
}