#include <common_includes.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/message_differencer.h>

#include "test_data.pb.h"

using namespace test_data;

bool proto_to_json(const google::protobuf::Message &message,
                   std::string &json) {
  using google::protobuf::util::JsonStringToMessage;
  google::protobuf::util::JsonPrintOptions options;
  options.add_whitespace = true;
  options.always_print_primitive_fields = true;
  options.preserve_proto_field_names = true;
  return MessageToJsonString(message, &json, options).ok();
}
std::string proto_to_json(const google::protobuf::Message &message) {
  std::string result{};
  assert(proto_to_json(message, result));
  return result;
}
bool json_to_proto(const std::string &json,
                   google::protobuf::Message &message) {
  using google::protobuf::util::JsonStringToMessage;
  return JsonStringToMessage(json, &message).ok();
}
inline std::ostream &operator<<(std::ostream &os,
                                const ::google::protobuf::Message &msg) {
  os << proto_to_json(msg);
  return os;
}
inline std::ostream &operator<<(std::ostream &os,
                                const ::google::protobuf::Message *const msg) {
  if (msg != nullptr) {
    os << proto_to_json(*msg);
  } else {
    os << "nullptr";
  }
  return os;
}
TEST(diff, 1) {
  OneOfMessage m1{};
  {
    m1.mutable_v1()->set_i1(42);
    Values v1{};
    v1.set_f3(44.3);
    m1.mutable_v3()->mutable_m3()->operator[](33)=v1;
    m1.mutable_v3()->mutable_l2()->Add()->CopyFrom(v1);
  }


  OneOfMessage m2{};
  {
    Values v2{};
    v2.set_i1(456);
    m2.mutable_v3()->mutable_m3()->operator[](33)=v2;
    m2.mutable_v3()->mutable_m3()->operator[](34)=v2;
    m2.mutable_v3()->mutable_l2()->Add()->CopyFrom(v2);
    m2.mutable_v1()->set_i1(43);
  }


  google::protobuf::util::MessageDifferencer differencer;

  std::string difference;
  differencer.ReportDifferencesToString(&difference);
  if (differencer.Compare(m1, m2)) {
    std::cout << "The messages are equal." << std::endl;
  } else {
    std::cout << "The messages are not equal." << std::endl;
    std::cout << "The differences are:" << std::endl;
    std::cout << difference << std::endl;
  }
  LOG_DEBUG(m1)
}
int main(int argc, char **argv) {
  int iRet = 0;

  //    testing::InitGoogleTest();
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}