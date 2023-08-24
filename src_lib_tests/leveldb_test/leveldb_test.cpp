//
// Created by khalidzhang on 2023/2/6.
//
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

#include "common_includes.h"

TEST(leveldb, rw) {
  leveldb::DB *db{};
  leveldb::Options opt{};
  opt.create_if_missing = true;
  auto status = leveldb::DB::Open(opt, "./testdb", &db);
  ASSERT_TRUE(status.ok());
  std::string value{};

  // 增删改查
  status = db->Put(leveldb::WriteOptions(), "k1", "hello");
  ASSERT_TRUE(status.ok());
  status = db->Get(leveldb::ReadOptions(), "k1", &value);
  ASSERT_TRUE(status.ok());
  ASSERT_EQ(value, "hello");
  LOG_DEBUG(value);

  status = db->Delete(leveldb::WriteOptions(), "k1");
  ASSERT_TRUE(status.ok());
  status = db->Get(leveldb::ReadOptions(), "k1", &value);
  ASSERT_TRUE(status.IsNotFound());

  leveldb::WriteBatch batch{};
  batch.Put("k2", "v2");
  batch.Put("k3", "v3");
  batch.Delete("k2");
  status = db->Write(leveldb::WriteOptions(), &batch);
  ASSERT_TRUE(status.ok());
  status = db->Get(leveldb::ReadOptions(), "k2", &value);
  ASSERT_TRUE(status.IsNotFound());
  status = db->Get(leveldb::ReadOptions(), "k3", &value);
  ASSERT_TRUE(status.ok());
  ASSERT_EQ(value, "v3");
  LOG_DEBUG(value);

  delete db;
}
inline char *mutable_string_data(std::string *s) { return &(*s)[0]; }
inline char *remake_mutable_string_data(std::string *s, size_t size) {
  s->clear();
  s->resize(size);
  return mutable_string_data(s);
}
template <typename T>
  requires std::is_trivially_copyable_v<T>
void pod_struct_serialization(std::string *value, const T &obj) {
  auto ptr = remake_mutable_string_data(value, sizeof(T));
  memcpy(ptr, &obj, sizeof(T));
}
template <typename T>
  requires std::is_trivially_copyable_v<T>
void pod_struct_deserialization(T *obj, const std::string &value) {
  assert(value.size() == sizeof(T));
  memcpy(obj, value.data(), sizeof(T));
}
TEST(leveldb, bin) {
  leveldb::DB *db{};
  leveldb::Options opt{};
  opt.create_if_missing = true;
  auto status = leveldb::DB::Open(opt, "./testdb", &db);
  ASSERT_TRUE(status.ok());

  struct MemSt {
    int v1{};
    double d2{};
    char name[100]{};
    std::string ToString() const {
      std::ostringstream oss{};
      oss << "v1:" << v1;
      oss << ";d2:" << d2;
      oss << ";name:" << name;
      return oss.str();
    }
  };
  MemSt src{.v1 = 1024, .d2 = 3.14, .name = "hello leveldb"};
  std::string value{};
  LOG_DEBUG(src.ToString());
  // set
  pod_struct_serialization(&value, src);
  status = db->Put(leveldb::WriteOptions(), "k1", value);
  ASSERT_TRUE(status.ok());

  // get
  value.clear();
  status = db->Get(leveldb::ReadOptions(), "k1", &value);
  ASSERT_TRUE(status.ok());
  MemSt read{};
  pod_struct_deserialization(&read, value);
  LOG_DEBUG(read.ToString());
  ASSERT_EQ(src.ToString(), read.ToString());
}