#ifndef ALGORITHMS_STACK_H
#define ALGORITHMS_STACK_H

#include "List/SinglyLinkedList.h"

namespace ds {

    /**
     * Implementation of a simple stack class
     * using a Linked List.
     *
     * @tparam T Type of the elements of the stack.
     */
    template<typename T>
    class Stack {
    public:
        Stack() : mElements() {}

        /**
         * Pushes an element to the top of the stack
         * @param data Element to be pushed to the stack.
         */
        void Push(T data) {
            mElements.AddFirst(data);
        }

        /**
         * Pops the last element added to the stack,
         * removing it from the stack and returning it.
         * @return Last element added to the stack.
         */
        T& Pop() {
            T &temp = this->GetFirst();
            mElements.RemoveFirst();
            return temp;
        }

        /**
         * Returns the last element added to the stack,
         * but the element is not removed from the stack.
         * @return Last element added to the stack.
         */
        const T& Peek() const {
            return this->GetFirst();
        }

        /**
         * Prints the string representation of the stack
         * to the specified output stream.
         * @param o Original ostream to print the stack.
         * @return Resulting ostream after the stack is printed.
         */
        std::ostream& Print(std::ostream &o) const {
            return mElements.Print(o);
        }

    private:
        ds::SinglyLinkedList<T> mElements;

        T& GetFirst() const {
            try {
                return mElements.GetFirst();
            } catch(std::out_of_range) {
                throw std::out_of_range("The stack is empty.");
            }
        }
    };

    template<typename T>
    std::ostream& operator<<(std::ostream &os, const Stack<T> &rhsStack) {
        return rhsStack.Print(os);
    }
}



#endif //ALGORITHMS_STACK_H
