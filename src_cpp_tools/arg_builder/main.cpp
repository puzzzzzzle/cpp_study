#include "common_includes.h"

struct Addr {
  std::string addr_;
  int port_;
};
struct Auth {
  std::string id_;
  std::string key_;
};
class Timeout {
  public:
  Timeout() = default;
  Timeout(const std::chrono::milliseconds& duration) : ms{duration} {}
  Timeout(const std::int32_t& milliseconds)
      : Timeout{std::chrono::milliseconds(milliseconds)} {}
  Timeout(const std::chrono::seconds& duration)
      : ms{std::chrono::milliseconds(duration).count()} {}
  std::chrono::milliseconds ms;
};
struct AdditionalData {
  std::string key_;
  std::string value_;
};
struct Session {
  Addr addr_;
  Auth auth_;
  Timeout timeOut_;
  std::map<std::string, std::string> additionalData_;
  std::string ToString()
  {
    std::ostringstream oss;
    oss << "addr:"<<addr_.addr_<<":"<<addr_.port_<<";";
    oss << "auth:"<<auth_.id_<<":"<<auth_.key_<<";";
    oss << "timeOut:"<<timeOut_.ms<<";";
    for (const auto &[k,v]:additionalData_)
    {
      oss << "additionalData:"<<k<<":"<<v<<";";
    }
    return oss.str();
  }
};

template <typename CurrentType>
void set_opt_impl(Session& session, CurrentType&&);

template <>
void set_opt_impl<Addr>(Session& session, Addr&& val) {
  session.addr_ = val;
}
template <>
void set_opt_impl<Auth>(Session& session, Auth&& val) {
  session.auth_ = val;
}
template <>
void set_opt_impl<Timeout>(Session& session, Timeout&& val) {
  session.timeOut_ = val;
}
template <>
void set_opt_impl<AdditionalData>(Session& session, AdditionalData&& val) {
  session.additionalData_[val.key_] = val.value_;
}
// c++ 17
template <typename CurrType, typename... Ts>
void build_session(Session& session, CurrType&& curr, Ts&&... types) {
  set_opt_impl(session, std::forward<CurrType>(curr));
  if constexpr (sizeof...(types) > 0) {
    build_session<Ts...>(session, std::forward<Ts>(types)...);
  }
}

// c++11
// template <typename CurrType, typename... Ts>
// void build_session(Session& session, CurrType&& curr, Ts&&... types) {
//  set_opt_impl(session, std::forward<CurrType>(curr));
//  build_session(session, std::forward<Ts>(types)...);
//}
// void build_session(Session& session) {
//}

TEST(test_test, 1) {
  Session session;
  build_session(session, Timeout{3000}, Addr{"127.0.0.1", 8000}, Auth{"name", "key"},
                AdditionalData{"1", "v1"}, AdditionalData{"2", "v2"});
  LOG_DEBUG(session.ToString());
  ASSERT_EQ(session.ToString(),"addr:127.0.0.1:8000;auth:name:key;timeOut:3000ms;additionalData:1:v1;additionalData:2:v2;");
}

int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}