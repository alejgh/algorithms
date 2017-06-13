//
// Created by Alejandro on 02/06/2017.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "singly_linked_list.h"
#include "iostream"
#include <chrono>

template <typename T>
void CheckStrings(const ds::SinglyLinkedList<T> &list, const std::string &want){
    std::stringstream want_ss;
    std::stringstream result;
    want_ss << want;
    result << list;
    want_ss.flush();
    result.flush();
    REQUIRE(want_ss.str() == result.str());
}

TEST_CASE("Additions and size.") {
    ds::SinglyLinkedList<int> my_list;
    REQUIRE(my_list.IsEmpty());
    CheckStrings(my_list, "[]");
    my_list.AddFirst(5);
    REQUIRE(!my_list.IsEmpty());
    REQUIRE(my_list.GetSize()==1);
    my_list.AddFirst(6);
    CheckStrings(my_list, "[6, 5]");
    my_list.AddFirst(7);
    REQUIRE(my_list.Get(0) == 7);
    REQUIRE(my_list.Get(1) == 6);
    REQUIRE(my_list.Get(2) == 5);
    my_list.AddFirst(1);
    REQUIRE(my_list.GetSize()==4);
    CheckStrings(my_list, "[1, 7, 6, 5]");
    my_list.AddLast(9);
    REQUIRE(my_list.GetSize()==5);
    CheckStrings(my_list, "[1, 7, 6, 5, 9]");
    my_list.Add(3, 2);
    REQUIRE(my_list.GetSize()==6);
    CheckStrings(my_list, "[1, 7, 3, 6, 5, 9]");
}

TEST_CASE("Delete test.") {
    ds::SinglyLinkedList<std::string> str_list;
    str_list.AddFirst("Seoul");
    str_list.AddFirst("Ulan Bator");
    CheckStrings(str_list, "[Ulan Bator, Seoul]");
    REQUIRE(str_list.GetSize() == 2);
    REQUIRE(str_list.RemoveFirst());
    REQUIRE(str_list.GetSize() == 1);
    CheckStrings(str_list, "[Seoul]");
    REQUIRE(str_list.RemoveLast());
    REQUIRE(str_list.GetSize() == 0);
    CheckStrings(str_list, "[]");
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
    CheckStrings(char_list, "[a, b, c, d, z]");
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
    CheckStrings(list1, "[5, 6, 7]");
    CheckStrings(list2, "[5, 6, 7]");
    REQUIRE(list1.GetSize() == list2.GetSize());
    list1.Remove(1);
    CheckStrings(list1, "[5, 7]");
    CheckStrings(list2, "[5, 6, 7]");
    REQUIRE(list1.GetSize() == 2);
    REQUIRE(list2.GetSize() == 3);

    list2.Add(2, 1);
    list2.Add(1, 1);
    list1 = list2;
    REQUIRE(list1.GetSize() == list2.GetSize());
    CheckStrings(list1, "[5, 1, 2, 6, 7]");
    CheckStrings(list2, "[5, 1, 2, 6, 7]");
    list2.RemoveFirst();
    list2.RemoveFirst();
    CheckStrings(list1, "[5, 1, 2, 6, 7]");
    CheckStrings(list2, "[2, 6, 7]");
}