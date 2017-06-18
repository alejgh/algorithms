#ifndef ALGORITHMS_DOUBLYLINKEDLIST_H
#define ALGORITHMS_DOUBLYLINKEDLIST_H

#include <ostream>

namespace ds {

    /**
     * Doubly linked list implementation.
     *
     * @tparam T Type of the elements of the linked list.
     */
    template<typename T>
    class DoublyLinkedList {
    public:
        DoublyLinkedList() : mSize(0), mTail(nullptr), mHead(nullptr) {}

        DoublyLinkedList(const DoublyLinkedList& copyList) : mSize(0), mTail(nullptr), mHead(nullptr) {
            Node *currentNode = copyList.mHead;
            while(currentNode) {
                AddLast(currentNode->mData);
                currentNode = currentNode->mNext;
            }
        }

        ~DoublyLinkedList() {
            Node *currentNode = mHead;
            while(currentNode) {
                currentNode = currentNode->mNext;
                delete mHead;
                mHead = currentNode;
            }
        }

        DoublyLinkedList& operator=(const DoublyLinkedList& rhsList) {
            if(this == &rhsList) return *this;

            DoublyLinkedList temp(rhsList);
            std::swap(temp.mHead, this->mHead);
            this->mSize = rhsList.mSize;
            return *this;
        }

        DoublyLinkedList& AddFirst(const T& data) {
            Node *newNode = new Node(data);

            if(this->IsEmpty()) {
                mHead = newNode;
                mTail = newNode;
            } else {
                mHead->mPrevious = newNode;
                Node *temp = mHead;
                mHead = newNode;
                mHead->mNext = temp;
            }

            this->mSize++;
            return *this;
        }

        DoublyLinkedList& AddLast(const T& data) {
            Node *newNode = new Node(data);

            if(this->IsEmpty()) {
                mHead = newNode;
                mTail = newNode;
            } else {
                Node *currentNode = mTail;
                mTail = newNode;
                currentNode->mNext = newNode;
                newNode->mPrevious = currentNode;
            }

            this->mSize++;
            return *this;
        }

        DoublyLinkedList& Add(const T& data, int pos) {
            CheckValidPosition(pos);

            if(this->IsEmpty() || pos == 0)
                return AddFirst(data);
            else if(pos == mSize)
                return AddLast(data);
            else {
                int index = 0;
                Node *newNode = new Node(data);
                Node *currentNode = mHead;
                while(index != pos) {
                    currentNode = currentNode->mNext;
                    index++;
                }
                currentNode->mPrevious->mNext = newNode;
                newNode->mPrevious = currentNode->mPrevious;
                newNode->mNext = currentNode;
                currentNode->mPrevious = newNode;
                this->mSize++;
                return *this;
            }
        }

        T& Get(int pos) const {
            CheckValidPosition(pos);
            Node *currentNode = mHead;
            int index = 0;
            while(index != pos) {
                currentNode = currentNode->mNext;
                index++;
            }
            return currentNode->mData;
        }

        DoublyLinkedList& Remove(int pos) {
            CheckValidPosition(pos);

            if(pos == 0)
                return RemoveFirst();
            else if(pos == mSize - 1)
                return RemoveLast();
            else {

                int index = 0;
                Node *currentNode = mHead;
                while (index != pos) {
                    currentNode = currentNode->mNext;
                    index++;
                }
                currentNode->mPrevious->mNext = currentNode->mNext;
                currentNode->mNext->mPrevious = currentNode->mPrevious;
                delete currentNode;

                mSize--;
                return *this;
            }
        }

        DoublyLinkedList& RemoveFirst() {
            if(this->IsEmpty()) return *this;

            Node *temp = mHead;
            mHead = mHead->mNext;
            if(mSize == 1)
                mTail = mTail->mNext;
            else
                mHead->mPrevious = nullptr;
            delete temp;
            mSize--;
            return *this;
        }

        DoublyLinkedList& RemoveLast() {
            if(this->IsEmpty()) return *this;
            else if(mSize == 1) return RemoveFirst();

            Node *temp = mTail;
            mTail = mTail->mPrevious;
            mTail->mNext = nullptr;
            delete temp;
            mSize--;
            return *this;
        }

        size_t GetSize() const {
            return mSize;
        }

        bool IsEmpty() const {
            return mSize == 0;
        }

        /**
        * Prints the string representation of the current
        * state of the list into the specified output stream.
        * @param o Output stream to write the string to.
        * @return Modified output stream.
        */
        std::ostream& Print(std::ostream &o) const {
            o << "[";
            Node *temp = mHead;
            while (temp != nullptr) {
                o << temp->mData;
                if (temp->mNext != nullptr) {
                    o << ", ";
                }
                temp = temp->mNext;
            }
            o << "]";
            return o;
        }

    private:
        struct Node{
            T mData;
            Node *mPrevious;
            Node *mNext;

            Node(const T& data) : mData(data), mPrevious(nullptr), mNext(nullptr) {}
        };

        void CheckValidPosition(int position) const {
            if(position < 0 || position >= mSize)
                throw std::out_of_range("Invalid position.");
        }

        Node *mTail;
        Node *mHead;
        size_t mSize;
    };

    template<typename T>
    std::ostream& operator<<(std::ostream &os, const DoublyLinkedList<T> &rhsList) {
        return rhsList.Print(os);
    }
}

#endif //ALGORITHMS_DOUBLYLINKEDLIST_H
