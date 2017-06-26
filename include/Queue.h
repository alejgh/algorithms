#ifndef ALGORITHMS_QUEUE_H
#define ALGORITHMS_QUEUE_H

#include "List/SinglyLinkedList.h"

template<typename T>
class Queue {
private:
    ds::SinglyLinkedList<T> elements;

public:
    Queue() {}

    void Enqueue(const T& element)
    {
        elements.AddLast(element);
    }

    T Dequeue()
    {
        T temp = elements.GetFirst();
        elements.RemoveFirst();
        return temp;
    }

    T& Peek() const
    {
        return elements.GetFirst();
    }

};

#endif //ALGORITHMS_QUEUE_H
