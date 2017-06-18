#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Utils.h"
#include "List/DoublyLinkedList.h"

template<typename T>
void TryAddOutOfRange(ds::DoublyLinkedList<T> &list, const T &element, int pos);

TEST_CASE("Simple test") {
    ds::DoublyLinkedList<int> intList;
    utils::CheckString(intList, "[]");
    intList.AddLast(5).AddFirst(3).Add(1, 1);
    REQUIRE(intList.Get(2) == 5);
    REQUIRE(intList.Get(1) == 1);
    REQUIRE(intList.Get(0) == 3);
    utils::CheckString(intList, "[3, 1, 5]");
    REQUIRE(intList.GetSize() == 3);
    for (int i = 0; i < 10000; ++i) {
        intList.AddFirst(i);
        intList.AddLast(i);
    }
    for (int i = 0; i < 10000; ++i) {
        intList.RemoveFirst();
        intList.RemoveLast();
    }

    REQUIRE(intList.GetSize() == 3);
    intList.Remove(1);
    utils::CheckString(intList, "[3, 5]");
    intList.RemoveFirst();
    utils::CheckString(intList, "[5]");
    intList.RemoveLast();
    REQUIRE(intList.GetSize() == 0);
}

TEST_CASE("Bounds checking") {
    ds::DoublyLinkedList<char> charList;
    charList.AddFirst('a');
    TryAddOutOfRange(charList, 'b', -1);
    TryAddOutOfRange(charList, 'c', 2);
    charList.AddLast('d');
    charList.Add('b', 1);
    charList.Add('c', 2);
    utils::CheckString(charList, "[a, b, c, d]");
    ds::DoublyLinkedList<char> anotherCharList;
    anotherCharList = charList;
    utils::CheckString(anotherCharList, "[a, b, c, d]");
    anotherCharList.Remove(1);
    anotherCharList.Remove(1);
    utils::CheckString(anotherCharList, "[a, d]");
    utils::CheckString(charList, "[a, b, c, d]");
}

template<typename T>
void TryAddOutOfRange(ds::DoublyLinkedList<T> &list, const T &element, int pos) {
    try {
        list.Add(element, pos);
        REQUIRE(false); // the list should have thrown an exception
    } catch (std::out_of_range) {
        REQUIRE(true);
    }
}