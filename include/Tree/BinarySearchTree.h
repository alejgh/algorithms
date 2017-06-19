#ifndef ALGORITHMS_BINARYTREE_H
#define ALGORITHMS_BINARYTREE_H

namespace ds {

    template<typename T>
    class SinglyLinkedList; // used to provide the 'ToList' function

    /**
     *
     * @tparam T
     */
    template<typename T>
    class BinarySearchTree {
    public:
        typedef void (*CallbackFunction)(Node& node);

        class Node {
            T mData;
            Node *mRight;
            Node *mLeft;

            Node(T& data) : mData(data) {}
        };

        enum class TraverseTypes {
            IN_ORDER,
            PRE_ORDER,
            POST_ORDER
        };

        BinarySearchTree() : mRoot(nullptr) {}

        BinarySearchTree(const BinarySearchTree& cpTree) : mRoot(nullptr) {
            auto initFunc = [this](Node& node) -> void {
                this->Add(node.mData);
            };
            this->ApplyFunction(initFunc, TraverseTypes::PRE_ORDER);
        }

        ~BinarySearchTree() {
            auto deleteFunc = [this](Node& node) -> void {
                this->Remove()
            };
        }

        void Add(T data) {
            Add(mRoot, data);
        }

        bool Remove(const Node& nodeToRemove) {
            return Remove(mRoot, nodeToRemove);
        }

        const Node& Get(const T& data) const {
            return Get(mRoot, data);
        }

        void ApplyFunction(CallbackFunction func, TraverseTypes travType = TraverseTypes::IN_ORDER) {
            switch(travType) {
                case TraverseTypes::IN_ORDER:
                    ApplyFunctionInOrder(mRoot, func);
                    break;
                case TraverseTypes::PRE_ORDER:
                    ApplyFunctionPreOrder(mRoot, func);
                    break;
            }
        }

        SinglyLinkedList<T> ToList() {
            SinglyLinkedList<T> ret;

            auto addFunc = [&ret](Node& node)-> void {
                    ret.AddLast(node.mData);
            };

            ApplyFunction(addFunc, TraverseTypes::IN_ORDER);

            return ret;
        }

    private:
        Node *mRoot;

        void Add(Node& localRoot, T data) {
            if(localRoot == nullptr)
                localRoot = new Node(data);
            else {
                if(data > localRoot.mData)
                    Add(localRoot.mRight, data);
                else if(data < localRoot.mData)
                    Add(localRoot.mLeft, data);
                else
                    throw std::runtime_error("Duplicate elements are not allowed.");
            }
        }

        bool Remove(Node& localRoot, const Node& nodeToRemove) {
            if(localRoot == nullptr)
                return false;
            else {
                if(nodeToRemove < localRoot)
                    return Remove(localRoot.mLeft, nodeToRemove);
                else if(nodeToRemove > localRoot)
                    return Remove(localRoot.mRight, nodeToRemove);
                else {
                    // node found: need to know if it has children
                    if (localRoot.mLeft != nullptr && localRoot.mRight != nullptr) {
                        Node *maximumAtTheLeft = localRoot.mLeft;
                        while (maximumAtTheLeft->mRight != nullptr) {
                            maximumAtTheLeft = maximumAtTheLeft->mRight;
                        }
                        localRoot.mData = maximumAtTheLeft->mData;
                        Remove(localRoot.mLeft, maximumAtTheLeft);
                    } else if (localRoot.mLeft != nullptr) {
                        delete localRoot;
                        localRoot = localRoot.mLeft;
                    }else if(localRoot.mRight != nullptr) {
                        delete localRoot;
                        localRoot = localRoot.mRight;
                    } else {
                        // no children
                        delete localRoot;
                        localRoot = nullptr;
                    }
                    return true;
                }
            }
        }

        const Node& Get(const Node& localRoot, const T& data) const {
            if(localRoot == nullptr || localRoot.mData == data)
                return localRoot;
            else if(data < localRoot.mData)
                return Get(localRoot.mLeft, data);
            else
                return Get(localRoot.mRight, data);
        }

        void ApplyFunctionInOrder(Node& localRoot, CallbackFunction func) {
            if(localRoot == nullptr)
                return;
            ApplyFunctionInOrder(localRoot.mLeft, func);
            func(localRoot);
            ApplyFunctionInOrder(localRoot.mRight, func);
        }

        void ApplyFunctionPreOrder(Node& localRoot, CallbackFunction func) {
            if(localRoot == nullptr)
                return;
            func(localRoot);
            ApplyFunctionPreOrder(localRoot.mLeft, func);
            ApplyFunctionPreOrder(localRoot.mRight, func);
        }

        void ApplyFunctionPostOrder(Node& localRoot, CallbackFunction func) {
            if(localRoot == nullptr)
                return;
            ApplyFunctionPostOrder(localRoot.mLeft, func);
            ApplyFunctionPostOrder(localRoot.mRight, func);
            func(localRoot);
        }

    };
}

#endif //ALGORITHMS_BINARYTREE_H
