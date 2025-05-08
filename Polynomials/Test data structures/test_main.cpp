//#include "polynomials.h"
//#include <iostream>
//#include <vector>
//#include "translator.h"
//#include "unsorted_table.h"
//#include <gtest.h>
//#include "RedBlack_tree.h"
//#include "hash_table_chain.h"
//
//
//#define LOOPS 1000000
//
//using namespace std;
//
//int main() {
//    //TRedBlackTree<int, std::string> tree;
//
//    //tree.Insert(10, "ten");
//    //tree.Insert(20, "twenty");
//    //tree.Insert(30, "thirty");
//    //tree.Insert(15, "fifteen");
//    //tree.Insert(25, "twenty-five");
//
//    //std::cout << "Tree after insertions:" << std::endl;
//    //tree.Print();
//
//    //tree.Delete(20);
//    //std::cout << "Tree after deleting 20:" << std::endl;
//
//    //tree.Insert(10, "A");
//    //tree.Insert(20, "B");
//    //tree.Insert(30, "C");
//    //std::cout << "Height: " << tree.GetHeight() << std::endl;
//
//    ////tree.Print();
//
//    //std::cout << "Started insert of " << LOOPS << " objects..." << std::endl;
//
//    //for (int i = 0; i < LOOPS; ++i) {
//    //    tree.Insert(i, "value");
//    //}
//
//    ////tree.Print();
//    //std::cout << "Insert ended, started delete..." << std::endl;
//    //std::cout << "Height: " << tree.GetHeight() << std::endl;
//    //
//    //for (int i = 0; i < LOOPS/2; ++i) {
//    //    tree.Delete(i);
//    //}
//
//    //std::cout << "Delete ended" << std::endl;
//    //
//    //for (int i = 0; i < LOOPS/2; ++i) {
//    //    tree.Insert(i, "value");
//    //}
//
//    //for (int i = LOOPS; i < LOOPS + LOOPS / 2; ++i) {
//    //    tree.Insert(i, "value");
//    //}
//
//    //std::cout << "Height: " << tree.GetHeight() << std::endl;
//
//    //////////////////////////////////////////////////////////////////////////////treeeeeee////////////////////////////////////////////////////////////////////
//    //std::cout << "Insert element as a root: " << std::endl;
//    //tree.Insert(10, "ten");  // —лучай 1: корень
//    //tree.Print();
//    //std::cout << std::endl;
//
//    //std::cout << "Insert element with a black parent: " << std::endl;
//    //tree.Insert(5, "five");   // —лучай 2 : родитель чЄрный
//    //tree.Print();
//    //std::cout << std::endl;
//
//    //std::cout << "Insert element with a black parent: " << std::endl;
//    //tree.Insert(15, "fifteen");  // —лучай 2 : родитель чЄрный
//    //tree.Print();
//    //std::cout << std::endl;
//
//    //std::cout << "Insert element with red parent and uncle: " << std::endl;
//    //tree.Insert(1, "one");   // —лучай 3 : родитель и д€д€ красные
//    //tree.Print();
//    //std::cout << std::endl;
//
//    //std::cout << "Insert element with parent, which is left child, and black uncle: " << std::endl;
//    //tree.Insert(0,"zero");   // —лучай 4 : родитель Ч левый ребЄнок, д€д€ чЄрный
//    //tree.Print();
//    //std::cout << std::endl;
//
//    //std::cout << "Insert element with parent, which is right child, and black uncle: " << std::endl;
//    //tree.Insert(20, "twenty");   // —лучай 5 (оставшийс€)
//    //tree.Print();
//    //std::cout << std::endl;
//
//    //for (auto it = tree.begin(); it != tree.end(); ++it) {
//    //    std::cout << it->key << ": " << it->value << std::endl;
//    //}
//
//    ///*
//    // std::cout << "Copied tree: " << std::endl;
//    //TRedBlackTree<int, std::string> treeClone;
//    //treeClone = tree;
//    //treeClone.Print();*/
//
//    //////////////////////////////////////////////////////////////////////////////treeeeeee////////////////////////////////////////////////////////////////////
//
//
//    ////////////////////////////////////////////////////////////////////////////haaasshhh////////////////////////////////////////////////////////////////////    
//    ChainHashTable<string, string> table(4);
//
//    //table.insert("one", "1");
//    //table.insert("neo", "12");
//    //table.insert("oen", "123");
//    //table.insert("two", "2");
//    //table.insert("three", "3");
//    //table.insert("four", "4");
//
//    //if (auto* val = table.find("three"))
//    //cout << "Found: " << *val << endl;
//
//    //for (const auto& pair : table) {
//    //    cout << pair.first << " : " << pair.second << endl;
//    //}
//
//    //table.insert("abc", "11");
//    //table.insert("acb", "22"); // друга€ строка, но может быть тот же хеш
//
//    //table.debugPrint();
//
//    ChainHashTable<long int, long int> table1(10);
//
//    std::cout << "Started stress test" << std::endl;
//
//    for (int i = 0; i < LOOPS; ++i) {
//        table1.insert(i, i);
//    }
//
//    std::cout << "It works!" << std::endl;
//
//    table1.debugPrint();
//
//    return 0;
//
//    ////////////////////////////////////////////////////////////////////////////haaasshhh////////////////////////////////////////////////////////////////////
//}
//
////int main(int argc, char** argv)
////{
////    ::testing::InitGoogleTest(&argc, argv);
////    return RUN_ALL_TESTS();
////}