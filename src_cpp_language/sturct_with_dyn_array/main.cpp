#include "common_includes.h"
inline char *mutable_string_data(std::string *s) { return &(*s)[0]; }
inline char *remake_mutable_string_data(std::string *s, size_t size) {
  s->clear();
  s->resize(size);
  return mutable_string_data(s);
}
struct WithDynArray {
  int v1{};
  uint64_t arr_size{};
  char name[0];
  std::string ToString() const {
    std::ostringstream oss{};
    oss << "v1:" << v1;
    oss << ";arr_size:" << arr_size;
    oss << ";name:" << name;
    return oss.str();
  }
  static void Serialization(std::string *value, const WithDynArray &mem) {
    auto size = sizeof(WithDynArray) + mem.arr_size * sizeof(char);
    auto ptr = remake_mutable_string_data(value, size);
    memcpy(ptr, &mem, size);
  }
  static WithDynArray *Deserialization(const std::string &value) {
    auto *ret = (WithDynArray *)malloc(value.size());
    memcpy(ret, value.c_str(), value.size());
    return ret;
  }
  static WithDynArray *Make(int v1, const std::string &name) {
    auto *ret = (WithDynArray *)std::malloc(sizeof(WithDynArray) +
                                            name.size() * sizeof(char));
    ret->v1 = v1;
    ret->arr_size = name.size();
    memcpy(ret->name, name.c_str(), name.size());
    return ret;
  }
};
static_assert(std::is_trivially_copyable_v<WithDynArray>);
TEST(test_test, 1) {
  auto v1 = WithDynArray::Make(111, "puzzzzzzle");
  std::string buffer{};
  WithDynArray::Serialization(&buffer, *v1);
  auto v2 = WithDynArray::Deserialization(buffer);
  LOG_DEBUG(v2->ToString())
  ASSERT_EQ(v1->ToString(), v2->ToString());
  free(v1);
  free(v2);
}

int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}