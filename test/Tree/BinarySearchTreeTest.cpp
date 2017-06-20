#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Utils.h"
#include "Tree/BinarySearchTree.h"

TEST_CASE("Simple test.") {
    ds::BinarySearchTree<int, char> bst;
    REQUIRE(bst.IsEmpty());
    utils::CheckString(bst, "[]");
    bst.Add(5, 'c');
    utils::CheckString(bst, "[(5,c)]");
    bst.Add(3, 'g');
    utils::CheckString(bst, "[(5,c), (3,g)]");
    bst.Add(8, 'g');
    bst.Add(9, 'f');
    bst.Add(6, 'z');
    bst.Add(7, 'a');
    utils::CheckString(bst, "[(5,c), (3,g), (8,g), (6,z), (7,a), (9,f)]");
    bst.Remove(8);
    utils::CheckString(bst, "[(5,c), (3,g), (7,a), (6,z), (9,f)]");

    ds::BinarySearchTree<int, char> anotherTree(bst);

    // this will create a degenerated tree (like a list), so performance will be bad

    for(int i = 100; i < 10000; i++)
        bst.Add(i, static_cast<char>(i));

    utils::CheckString(anotherTree.ToList(), "[(5,c), (3,g), (7,a), (6,z), (9,f)]");

    for (int i = 100; i < 10000; i++)
        REQUIRE(bst.Get(i)->value == static_cast<char>(i));

    for(int i = 100; i < 10000; i++)
        bst.Remove(i);

    utils::CheckString(bst, "[(5,c), (3,g), (7,a), (6,z), (9,f)]");
    REQUIRE_THROWS(bst.Add(9, 'l'));
}

TEST_CASE("Test 2.") {
    ds::BinarySearchTree<int, std::string> bst;
    bst.Add(20, "Goodbye");
    bst.Add(8, "Hot");
    bst.Add(14, "Bad");
    bst.Add(5, "Pound");
    bst.Add(2, "Assert");
    bst.Add(3, "Bike");
    bst.Add(7, "Here");
    bst.Add(26, "Ulan Bator");

    utils::CheckString(bst, "[(20,Goodbye), (8,Hot), (5,Pound), (2,Assert),"
            " (3,Bike), (7,Here), (14,Bad), (26,Ulan Bator)]");

    bst.Add(23, "Coco");
    bst.Add(21, "Asd");
    bst.Add(28, "Proud");
    bst.Add(27, "Dash");
    bst.Add(31, "Vital");
    bst.Add(24, "Mona");
    bst.Add(29, "Cry");
    bst.Add(25, "Last");

    utils::CheckString(bst, "[(20,Goodbye), (8,Hot), (5,Pound), (2,Assert),"
            " (3,Bike), (7,Here), (14,Bad), (26,Ulan Bator), (23,Coco), (21,Asd),"
            " (24,Mona), (25,Last), (28,Proud), (27,Dash), (31,Vital), (29,Cry)]");

    bst.Add(12, "Ups");
    bst.Remove(20);
    utils::CheckString(bst, "[(14,Bad), (8,Hot), (5,Pound), (2,Assert),"
            " (3,Bike), (7,Here), (12,Ups), (26,Ulan Bator), (23,Coco), (21,Asd),"
            " (24,Mona), (25,Last), (28,Proud), (27,Dash), (31,Vital), (29,Cry)]");
    bst.Remove(2);
    utils::CheckString(bst, "[(14,Bad), (8,Hot), (5,Pound), (3,Bike),"
            " (7,Here), (12,Ups), (26,Ulan Bator), (23,Coco), (21,Asd),"
            " (24,Mona), (25,Last), (28,Proud), (27,Dash), (31,Vital), (29,Cry)]");
    bst.Remove(26);
    bst.Remove(28);
    bst.Remove(31);
    utils::CheckString(bst, "[(14,Bad), (8,Hot), (5,Pound), (3,Bike),"
            " (7,Here), (12,Ups), (25,Last), (23,Coco), (21,Asd),"
            " (24,Mona), (27,Dash), (29,Cry)]");
    ds::BinarySearchTree<int, std::string> anotherBst;
    anotherBst = bst;
    bst.Remove(14);
    bst.Remove(8);
    bst.Remove(5);
    bst.Remove(3);
    bst.Remove(7);
    bst.Remove(12);
    bst.Remove(25);
    bst.Remove(23);
    bst.Remove(29);
    bst.Remove(27);
    bst.Remove(21);
    bst.Remove(24);
    utils::CheckString(anotherBst, "[(14,Bad), (8,Hot), (5,Pound), (3,Bike),"
            " (7,Here), (12,Ups), (25,Last), (23,Coco), (21,Asd),"
            " (24,Mona), (27,Dash), (29,Cry)]");
    REQUIRE(bst.IsEmpty());
}