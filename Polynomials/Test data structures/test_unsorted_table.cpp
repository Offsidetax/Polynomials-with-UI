//#include "unsorted_table.h"
//#include <gtest.h>
//
//TEST(UnsortedTableIteratorTest, IteratorBeginEnd) {
//    UnsortedTable<int, std::string> table;
//    table.insert(1, "one");
//    table.insert(2, "two");
//    table.insert(3, "three");
//
//    auto it = table.begin();
//    EXPECT_NE(it, table.end());
//}
//
//TEST(UnsortedTableIteratorTest, IteratorIncrement) {
//    UnsortedTable<int, std::string> table;
//    table.insert(1, "one");
//    table.insert(2, "two");
//
//    auto it = table.begin();
//    auto prev = it;
//    ++it;
//    EXPECT_NE(prev, it);
//}
//
//TEST(UnsortedTableIteratorTest, IteratorDereference) {
//    UnsortedTable<int, std::string> table;
//    table.insert(1, "one");
//
//    auto it = table.begin();
//    EXPECT_EQ(it->first, 1);
//    EXPECT_EQ(it->second, "one");
//}
//
//TEST(UnsortedTableIteratorTest, FindExistingElement) {
//    UnsortedTable<int, std::string> table;
//    table.insert(42, "answer");
//
//    auto it = table.find(42);
//    EXPECT_NE(it, table.end());
//    EXPECT_EQ(it->second, "answer");
//}
//
//TEST(UnsortedTableIteratorTest, FindNonExistingElement) {
//    UnsortedTable<int, std::string> table;
//    table.insert(42, "answer");
//
//    auto it = table.find(99);
//    EXPECT_EQ(it, table.end());
//}
//
//TEST(UnsortedTableIteratorTest, EraseElement) {
//    UnsortedTable<int, std::string> table;
//    table.insert(1, "one");
//    table.insert(2, "two");
//
//    auto it = table.erase(1);
//    EXPECT_EQ(table.find(1), table.end());
//    EXPECT_NE(it, table.end());
//}
