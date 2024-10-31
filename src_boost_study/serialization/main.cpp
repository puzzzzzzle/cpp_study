#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "common_includes.h"
class TestSerialize {
  public:
  int val1_{};
  double val2_{};
  std::string val3_{};

  public:
  TestSerialize() = default;
  TestSerialize(int val1, double val2, const std::string &val3)
      : val1_(val1), val2_(val2), val3_(val3) {}

  public:
  std::string ToString() const {
    return std::format("{} {} {}", val1_, val2_, val3_);
  }
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar & BOOST_SERIALIZATION_NVP(val1_);
    ar & BOOST_SERIALIZATION_NVP(val2_);
    ar & BOOST_SERIALIZATION_NVP(val3_);
  }
};
TEST(serialize_test, text) {
  std::stringstream ss{};
  {
    TestSerialize dump(22, 33.5, "hello world");
    LOG_DEBUG(dump.ToString());
    boost::archive::text_oarchive os(ss);
    os << dump;
    FLOG_DEBUG("serialized str is : {}", ss.str());
  }
  ss.seekg(0);
  {
    TestSerialize load{};
    boost::archive::text_iarchive is(ss);
    is >> load;
    LOG_DEBUG(load.ToString());
  }
}
TEST(serialize_test, xml) {
  std::stringstream ss{};
  {
    TestSerialize dump(22, 33.5, "hello world");
    LOG_DEBUG(dump.ToString());
    boost::archive::xml_oarchive os(ss);
    os << BOOST_SERIALIZATION_NVP(dump);
    FLOG_DEBUG("serialized str is : {}", ss.str());
  }
  ss.seekg(0);
  {
    TestSerialize load{};
    boost::archive::xml_iarchive is(ss);
    is >> BOOST_SERIALIZATION_NVP(load);
    LOG_DEBUG(load.ToString());
  }
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}