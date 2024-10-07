//#include <catch2/catch_test_macros.hpp>
//#include <iostream>
//#include <string>
//#include <sstream>
//
//#define private public
//
//#include "AVL.h"
//
//
//using namespace std;
//
//// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
//TEST_CASE("Test 1", "[flag]"){
//	// instantiate any class members that you need to test here
//    AVL tree;
//    tree.search("Adam");
//    REQUIRE("unsuccessful");
//    tree.search("12341234");
//    REQUIRE("unsuccessful");
//
//    string name1 = "bhavana1";
//    string name2 = "meg";
//    string name3 = "Amy";
//    string ufid1 = "11111111";
//    string ufid2 = "33333333b";
//    string ufid3 = "2222222222";
//
//    tree.insertNameID(name1,ufid1);
//    REQUIRE("unsuccessful");
//    tree.insertNameID(name2,ufid2);
//    REQUIRE("unsuccessful");
//    tree.insertNameID(name3,ufid3);
//    REQUIRE("unsuccessful");
//
//}
//TEST_CASE("Test 2", "[flag]"){
//	// you can also use "sections" to share setup code between tests, for example:
//    string name1 = "bhavana1";
//    string id = "12341234";
//
//    AVL tree;
//
//    tree.removeID("14322141");
//    REQUIRE("unsuccessful");
//    tree.search("Adam");
//    REQUIRE("unsuccessful");
//    tree.search("12341234");
//    REQUIRE("unsuccessful");
//
//
//	// each section runs the setup code independently to ensure that they don't affect each other
//}
//TEST_CASE("Test 3", "[flag]"){
//    AVL tree;
//    tree.insertNameID("Adam", "33333333");
//    REQUIRE("successful");
//    tree.insertNameID("Bob", "11111111");
//    REQUIRE("successful");
//    tree.insertNameID("Carter", "22222222");
//    REQUIRE("successful");
//    tree.insertNameID("David", "55555555");
//    REQUIRE("successful");
//    tree.insertNameID("Ethan", "44444444");
//    REQUIRE("successful");
//
//
//    tree.printInOrder();
//    REQUIRE("Bob, Carter, Adam, Ethan, David");
//}
//TEST_CASE("Test 4", "[flag]"){
//    AVL tree;
//    tree.insertNameID("Adam", "11111111");
//    REQUIRE("successful");
//    tree.insertNameID("Bob", "22222222");
//    REQUIRE("successful");
//    tree.insertNameID("Carter", "33333333");
//    REQUIRE("successful");
//
//    tree.removeID("22222222");
//    REQUIRE("successful");
//    tree.removeID("33333333");
//    REQUIRE("successful");
//    tree.removeID("11111111");
//    REQUIRE("successful");
//}
//TEST_CASE("Test 5", "[flag]"){
//    AVL tree;
//    string name = "bhavana";
//    //getting IDs
//    vector <int> ufids;
//    while(ufids.size() != 100)
//        ufids.push_back(rand()% 90000000 + 10000000);
//
//    //inserting
//    for(int id : ufids) {
//        tree.insertNameID(name, to_string(id));
//        REQUIRE("successful");
//    }
//    //random indexes
//    vector<int> randIndexes;
//    while(randIndexes.size() <10){
//        randIndexes.push_back(rand()%100);
//    }
//    for(int index: randIndexes){
//        tree.removeID(to_string(ufids[index]));
//        REQUIRE("successful");
//    }
//}
