#include "gtest/gtest.h"
#include <string>
#include <unordered_map>

struct Record {
    int id;
    std::string name;
};

struct Database {
    bool connect(const std::string& database_name) {
        name = database_name;
        connected = true;
        return connected;
    }

    void disconnect() {
        connected = false;
        records.clear();
    }

    bool insert(const Record& record) {
        if (!connected) {
            return false;
        }

        return records.emplace(record.id, record).second;
    }

    bool delete_record(int id) {
        if (!connected) {
            return false;
        }

        records.erase(id);
        return true;
    }

    std::string name;
    bool connected = false;
    std::unordered_map<int, Record> records;
};

class DatabaseTest : public::testing::Test {
protected:
    void SetUp() override {
        // 连接到测试数据库
        db.connect("test_db");
    }

    void TearDown() override {
        // 断开数据库连接
        db.disconnect();
    }

    Database db;
};

TEST_F(DatabaseTest, InsertRecord) {
    Record record = {1, "Test"};
    EXPECT_TRUE(db.insert(record));
}

TEST_F(DatabaseTest, DeleteRecord) {
    EXPECT_TRUE(db.delete_record(1));
}
