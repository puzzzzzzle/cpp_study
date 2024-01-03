#include "common_includes.h"
#include "rocksdb/db.h"

TEST(simple, 1) {
  using namespace rocksdb;
  DB* db;
  Options opt{};
  opt.create_if_missing = true;
  auto status = DB::Open(opt, "/tmp/rocksdb_test1", &db);
  ASSERT_TRUE(status.ok());

  ASSERT_TRUE(status.ok());
  std::string value{};

  // 增删改查
  status = db->Put(WriteOptions(), "k1", "hello");
  ASSERT_TRUE(status.ok());
  status = db->Get(ReadOptions(), "k1", &value);
  ASSERT_TRUE(status.ok());
  ASSERT_EQ(value, "hello");
  LOG_DEBUG(value);

  status = db->Delete(WriteOptions(), "k1");
  ASSERT_TRUE(status.ok());
  status = db->Get(ReadOptions(), "k1", &value);
  ASSERT_TRUE(status.IsNotFound());

  WriteBatch batch{};
  batch.Put("k2", "v2");
  batch.Put("k3", "v3");
  batch.Delete("k2");
  status = db->Write(WriteOptions(), &batch);
  ASSERT_TRUE(status.ok());
  status = db->Get(ReadOptions(), "k2", &value);
  ASSERT_TRUE(status.IsNotFound());
  status = db->Get(ReadOptions(), "k3", &value);
  ASSERT_TRUE(status.ok());
  ASSERT_EQ(value, "v3");
  LOG_DEBUG(value);

  
  delete db;
}

int main(int argc, char** argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}