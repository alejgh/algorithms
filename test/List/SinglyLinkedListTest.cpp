#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Utils.h"
#include "List/SinglyLinkedList.h"



TEST_CASE("Additions and size.") {
    ds::SinglyLinkedList<int> my_list;
    REQUIRE(my_list.IsEmpty());
    utils::CheckString(my_list, "[]");
    my_list.AddFirst(5);
    REQUIRE(!my_list.IsEmpty());
    REQUIRE(my_list.GetSize()==1);
    my_list.AddFirst(6);
    utils::CheckString(my_list, "[6, 5]");
    my_list.AddFirst(7);
    REQUIRE(my_list.Get(0) == 7);
    REQUIRE(my_list.Get(1) == 6);
    REQUIRE(my_list.Get(2) == 5);
    my_list.AddFirst(1);
    REQUIRE(my_list.GetSize()==4);
    utils::CheckString(my_list, "[1, 7, 6, 5]");
    my_list.AddLast(9);
    REQUIRE(my_list.GetSize()==5);
    utils::CheckString(my_list, "[1, 7, 6, 5, 9]");
    my_list.Add(3, 2);
    REQUIRE(my_list.GetSize()==6);
    utils::CheckString(my_list, "[1, 7, 3, 6, 5, 9]");
}

TEST_CASE("Delete test.") {
    ds::SinglyLinkedList<std::string> str_list;
    str_list.AddFirst("Seoul");
    str_list.AddFirst("Ulan Bator");
    utils::CheckString(str_list, "[Ulan Bator, Seoul]");
    REQUIRE(str_list.GetSize() == 2);
    REQUIRE(str_list.RemoveFirst());
    REQUIRE(str_list.GetSize() == 1);
    utils::CheckString(str_list, "[Seoul]");
    REQUIRE(str_list.RemoveLast());
    REQUIRE(str_list.GetSize() == 0);
    utils::CheckString(str_list, "[]");
}

TEST_CASE("Get test.") {
    ds::SinglyLinkedList<char> char_list;
    REQUIRE_THROWS(char_list.GetFirst());
    REQUIRE_THROWS(char_list.Get(0));
    REQUIRE_THROWS(char_list.GetLast());
    char_list.AddLast('z');
    REQUIRE(char_list.GetFirst() == 'z');
    REQUIRE(char_list.Get(0) == 'z');
    REQUIRE(char_list.GetLast() == 'z');
    char_list.AddFirst('a');
    char_list.Add('d', 1);
    REQUIRE(char_list.GetFirst() == 'a');
    REQUIRE(char_list.Get(1) == 'd');
    REQUIRE(char_list.GetLast() == 'z');
    char_list.Add('b', 1);
    char_list.Add('c', 2);
    utils::CheckString(char_list, "[a, b, c, d, z]");
    REQUIRE(char_list.GetFirst() == 'a');
    REQUIRE(char_list.Get(2) == 'c');
    REQUIRE(char_list.GetLast() == 'z');
    REQUIRE(char_list.GetSize() == 5);
}

TEST_CASE("Copy constructor and assignment.") {
    ds::SinglyLinkedList<int> list1;
    list1.AddLast(5);
    list1.AddLast(6);
    list1.AddLast(7);
    ds::SinglyLinkedList<int> list2(list1);
    utils::CheckString(list1, "[5, 6, 7]");
    utils::CheckString(list2, "[5, 6, 7]");
    REQUIRE(list1.GetSize() == list2.GetSize());
    list1.Remove(1);
    utils::CheckString(list1, "[5, 7]");
    utils::CheckString(list2, "[5, 6, 7]");
    REQUIRE(list1.GetSize() == 2);
    REQUIRE(list2.GetSize() == 3);

    list2.Add(2, 1);
    list2.Add(1, 1);
    list1 = list2;
    REQUIRE(list1.GetSize() == list2.GetSize());
    utils::CheckString(list1, "[5, 1, 2, 6, 7]");
    utils::CheckString(list2, "[5, 1, 2, 6, 7]");
    list2.RemoveFirst();
    list2.RemoveFirst();
    utils::CheckString(list1, "[5, 1, 2, 6, 7]");
    utils::CheckString(list2, "[2, 6, 7]");
}

TEST_CASE("Constant linked list showcase ^.^") {
    // not really a test, just to show constant linked lists
    ds::SinglyLinkedList<int> int_list;
    int_list.AddLast(5);
    int_list.AddFirst(1);
    const ds::SinglyLinkedList<int> const_list(int_list);
    const_list.Get(0);
    const_list.GetSize();
    const_list.IsEmpty();
    const_list.GetFirst();
    const_list.GetLast();
    // any other method (e.g RemoveFirst()) --> compiler error
}