//#include "RedBlack_tree.h"
//#include <gtest.h>
//
////TEST(RedBlackTreeTest, ConstructsCorrectly) {
////    EXPECT_NO_THROW(TRedBlackTree<int, std::string> tree;);
////}
//
//TEST(RedBlackTreeTest, InsertWorks) {
//    TRedBlackTree<int, std::string> tree;
//    tree.Insert(10, "value10");
//
//    EXPECT_NE(tree.Find(10), nullptr);
//}
//
////TEST(RedBlackTreeTest, InsertMaintainsBalance) {
////    TRedBlackTree<int, std::string> tree;
////    tree.Insert(10, "A");
////    tree.Insert(20, "B");
////    tree.Insert(30, "C");
////
////    EXPECT_EQ(tree.Find(20)->color, TRedBlackTree<int, std::string>::BLACK);
////}
//
//TEST(RedBlackTreeTest, FindExistingKey) {
//    TRedBlackTree<int, std::string> tree;
//    tree.Insert(15, "value15");
//
//    EXPECT_NE(tree.Find(15), nullptr);
//}
//
//TEST(RedBlackTreeTest, FindNonExistentKey) {
//    TRedBlackTree<int, std::string> tree;
//    EXPECT_EQ(tree.Find(42), nullptr);
//}
//
//TEST(RedBlackTreeTest, DeleteWorks) {
//    TRedBlackTree<int, std::string> tree;
//    tree.Insert(10, "value10");
//    tree.Delete(10);
//
//    EXPECT_EQ(tree.Find(10), nullptr);
//}
//
////TEST(RedBlackTreeTest, DeleteMaintainsBalance) {
////    TRedBlackTree<int, std::string> tree;
////    tree.Insert(30, "A");
////    tree.Insert(20, "B");
////    tree.Insert(40, "C");
////    tree.Delete(30);
////
////    EXPECT_EQ(tree.Find(20)->color, TRedBlackTree::BLACK);
////}
//
//TEST(RedBlackTreeTest, ThrowsOnDeleteNonExistentKey) {
//    TRedBlackTree<int, std::string> tree;
//    EXPECT_THROW(tree.Delete(99), const char*);
//}
//
//TEST(RedBlackTreeTest, CorrectTreeHeight) {
//    TRedBlackTree<int, std::string> tree;
//
//    tree.Insert(10, "ten");
//    tree.Insert(20, "twenty");
//    tree.Insert(30, "thirty");
//    tree.Insert(15, "fifteen");
//    tree.Insert(25, "twenty-five");
//    tree.Delete(20);
//    tree.Insert(10, "A");
//    tree.Insert(20, "B");
//    tree.Insert(30, "C");
//
//    EXPECT_EQ(tree.GetHeight(), 3);
//}