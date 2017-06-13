#ifndef ALGORITHMS_SINGLY_LINKED_LIST_H
#define ALGORITHMS_SINGLY_LINKED_LIST_H

#include <algorithm>
#include <ostream>
#include <vector>

namespace ds {

    /**
     * Singly linked list implementation.
     *
     * @tparam T Type of the elements the linked list
     * will store.
     */
    template<typename T>
    class SinglyLinkedList {
    public:
        SinglyLinkedList() : size(0), head(nullptr), last(nullptr) { }

        SinglyLinkedList(const SinglyLinkedList& cp_list) : size(0), head(nullptr), last(nullptr) {
            Node *curr_node = cp_list.head;
            while(curr_node) {
                AddLast(curr_node->data);
                curr_node = curr_node->next;
            }
        }

        SinglyLinkedList& operator=(const SinglyLinkedList& rhs_list) {
            SinglyLinkedList temp(rhs_list);
            std::swap(temp.head, this->head);
            this->size = rhs_list.size;
            return *this;
        }

        ~SinglyLinkedList() {
            Node *temp = head;
            while (head != nullptr) {
                temp = head->next;
                delete head;
                head = temp;
            }
        }

        void AddLast(T data) {
            Node *node = new Node(data);

            if (this->IsEmpty()) {
                this->head = node;
                this->last = node;
            } else {
                this->last->next = node;
                this->last = node;
            }

            this->size++;
        }

        void Add(T data, int pos) {
            if (this->IsEmpty() || pos == 0) {
                AddFirst(data);
            } else if (pos == this->size) {
                AddLast(data);
            } else if (pos > this->size) {
                throw std::out_of_range("Invalid position.");
            }

            int index = 1;
            Node *curr = head;
            while (index != pos) {
                curr = curr->next;
                index++;
            }

            Node *newNode = new Node(data);
            newNode->next = curr->next;
            curr->next = newNode;
            this->size++;
            return;
        }

        void AddFirst(T data) {
            Node *node = new Node(data);

            if (this->IsEmpty()) {
                this->head = node;
                this->last = node;
            } else {
                node->next = this->head;
                this->head = node;
            }
            this->size++;
        }

        T Get(int pos) {
            if (pos >= this->size) {
                throw std::out_of_range("Invalid position.");
            }

            Node *temp = head;
            int curr_index = 0;
            while (curr_index != pos) {
                temp = temp->next;
                curr_index++;
            }

            T data = temp->data;
            return data;
        }

        T GetFirst() {
            if (this->IsEmpty()){
                throw std::out_of_range("The list is empty.");
            }
            return head->data;
        }

        T GetLast() {
            if (this->IsEmpty()){
                throw std::out_of_range("The list is empty.");
            }
            return last->data;
        }

        bool Remove(int pos) {
            if (this->IsEmpty()) {
                return false;
            } else if (pos == 0) {
                return RemoveFirst();
            } else if (pos == this->size - 1) {
                return RemoveLast();
            }

            Node *temp = head;
            Node *previous = nullptr;
            int index = 0;
            while (index != pos) {
                previous = temp;
                temp = temp->next;
                index++;
            }

            previous->next = temp->next;
            temp->next = nullptr;
            delete temp;
            this->size--;
            return true;
        }

        bool RemoveFirst() {
            if (this->IsEmpty()) {
                return false;
            }

            Node *temp = head;
            head = head->next;
            if (size == 1) {
                last = last->next;
            }
            delete temp;
            size--;
            return true;
        }

        bool RemoveLast() {
            if (this->IsEmpty()) {
                return false;
            } else if (this->GetSize() == 1) {
                return RemoveFirst();
            }

            Node *temp = head;
            // get to second-to-last node
            for (int i = 0; i < this->size - 2; i++) {
                temp = temp->next;
            }
            last = temp;
            delete last->next;
            last->next = nullptr;
            size--;
            return true;
        }

        bool IsEmpty() {
            return size == 0;
        }

        int GetSize() {
            return this->size;
        }

        /**
         * Prints the string representation of the current
         * state of the list into the specified output stream.
         * @param o Output stream to write the string to.
         * @return Modified output stream.
         */
        virtual std::ostream& Print(std::ostream &o) const {
            o << "[";
            Node *temp = head;
            while (temp != nullptr) {
                o << temp->data;
                if (temp->next != nullptr) {
                    o << ", ";
                }
                temp = temp->next;
            }
            o << "]";
            return o;
        }

    private:
        struct Node {
            T data;
            Node *next;

            Node() : data(T()), next(nullptr) {}

            Node(const T &pData) : data(pData), next(nullptr) {}

            Node(const Node &cpNode) : data(cpNode.data) {
                this->next = new Node(cpNode.next);
            }

            ~Node() {}
        };

        Node *head;
        Node *last; // to get O(1) with operations on last element
        size_t size;
    };

    template<typename T>
    std::ostream &operator<<(std::ostream &o, const SinglyLinkedList<T> &l) { return l.Print(o); }
}

#endif //ALGORITHMS_SINGLY_LINKED_LIST_H
