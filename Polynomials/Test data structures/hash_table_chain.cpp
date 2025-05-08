//#include "hash_table_chain.h" 
//#include <gtest.h>
//#include <string>
//
//TEST(ChainHashTableTest, FindExistingKey) {
//    ChainHashTable<int, std::string> table(5);
//    table.insert(42, "answer");
//
//    auto* result = table.find(42);
//
//    EXPECT_EQ(*result, "answer");
//}
//
//TEST(ChainHashTableTest, FindNonExistingKey) {
//    ChainHashTable<int, std::string> table(5);
//    table.insert(1, "one");
//
//    auto* result = table.find(999);
//
//    EXPECT_EQ(result, nullptr);
//}
//
//TEST(ChainHashTableTest, OverwriteValue) {
//    ChainHashTable<int, std::string> table(5);
//    table.insert(5, "first");
//    table.insert(5, "second");
//
//    auto* result = table.find(5);
//
//    EXPECT_EQ(*result, "second");
//}
//
//TEST(ChainHashTableTest, IteratorBeginEnd) {
//    ChainHashTable<int, std::string> table(5);
//    table.insert(1, "one");
//
//    auto it = table.begin();
//
//    EXPECT_NE(it, table.end());
//}
//
//TEST(ChainHashTableTest, IteratorIncrement) {
//    ChainHashTable<int, std::string> table(5);
//    table.insert(1, "one");
//    table.insert(2, "two");
//
//    auto it = table.begin();
//    auto first = *it;
//    ++it;
//    auto second = *it;
//
//    EXPECT_NE(first.first, second.first);
//}
//
//TEST(ChainHashTableTest, IterateOverAllElements) {
//    ChainHashTable<int, std::string> table(5);
//    table.insert(1, "one");
//    table.insert(2, "two");
//    table.insert(3, "three");
//
//    std::set<int> keys;
//    for (const auto& kv : table) {
//        keys.insert(kv.first);
//    }
//
//    EXPECT_EQ(keys.size(), 3);
//}
//
//TEST(ChainHashTableTest, CanEraseExistingElement) {
//    ChainHashTable<int, string> table(5);
//
//    table.insert(1, "one");
//
//    EXPECT_TRUE(table.erase(1));
//}
//
//TEST(ChainHashTableTest, EraseExistingElementCorrectly) {
//    ChainHashTable<int, string> table(5);
//
//    table.insert(1, "one");
//    table.erase(1);
//
//    EXPECT_EQ(table.find(1), nullptr);
//}
//
//TEST(ChainHashTableTest, EraseNonExistingElement) {
//    ChainHashTable<int, string> table(5);
//
//    table.insert(1, "one");
//
//    EXPECT_FALSE(table.erase(2));
//}