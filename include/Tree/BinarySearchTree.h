#ifndef ALGORITHMS_BINARYTREE_H
#define ALGORITHMS_BINARYTREE_H

#include <algorithm>
#include <functional>
#include <string>
#include "List/SinglyLinkedList.h"

namespace ds {

    template<typename TKey, typename TValue>
    class BinarySearchTree {
    private:
        struct BinaryNode {
            TKey key;
            TValue value;
            BinaryNode *right;
            BinaryNode *left;

            BinaryNode(TKey key, TValue val) : key(key), value(val), right(nullptr), left(nullptr) {}

            friend std::ostream& operator<<(std::ostream& os, const BinaryNode& node) {
                os << "(" << node.key << "," << node.value << ")";
                return os;
            }
        };

        enum class TraverseTypes {
            IN_ORDER,
            PRE_ORDER,
            POST_ORDER
        };

        typedef std::function<void (BinaryNode*)> CallbackAction;

        BinaryNode *mRoot;
    public:

        BinarySearchTree() : mRoot(nullptr) {}

        BinarySearchTree(const BinarySearchTree& cpTree) : mRoot(nullptr) {
            auto initFunc = [this](BinaryNode* node) -> void {
                this->Add(node->key, node->value);
            };
            cpTree.ApplyAction(initFunc, TraverseTypes::PRE_ORDER);
        }

        ~BinarySearchTree() {
            std::function<void (BinaryNode*)> deleteFunc = [this](BinaryNode* node) -> void {
                this->Remove(node->key);
            };
            this->ApplyAction(deleteFunc, TraverseTypes::POST_ORDER);
        }

        BinarySearchTree& operator=(const BinarySearchTree& rhsTree) {
            if(this == &rhsTree) return *this;

            BinarySearchTree temp(rhsTree);
            std::swap(temp.mRoot, this->mRoot);
            return *this;
        }

        void Add(const TKey& key, const TValue& val) {
            Add(mRoot, key, val);
        }

        bool Remove(const TKey& keyToRemove) {
            return Remove(mRoot, keyToRemove);
        }

        BinaryNode* Get(const TKey& key) {
            BinaryNode *current = mRoot;

            while (current != nullptr && current->key != key) {
                if (key < current->key)
                    current = current->left;
                else
                    current = current->right;
            }
            return current;
        }

        BinaryNode* GetMin() {
            return GetMin(mRoot);
        }

        BinaryNode* GetMax() {
            return GetMax(mRoot);
        }

        bool IsEmpty() {
            return this->mRoot == nullptr;
        }

        void ApplyAction(CallbackAction action, TraverseTypes travType = TraverseTypes::IN_ORDER) const {
            switch(travType) {
                case TraverseTypes::IN_ORDER:
                    ApplyActionInOrder(mRoot, action);
                    break;
                case TraverseTypes::PRE_ORDER:
                    ApplyActionPreOrder(mRoot, action);
                    break;
                case TraverseTypes::POST_ORDER:
                    ApplyActionPostOrder(mRoot, action);
                    break;
            }
        }

        SinglyLinkedList<BinaryNode> ToList() {
            SinglyLinkedList<BinaryNode> ret;

            auto addFunc = [&ret](BinaryNode* node)-> void {
                    ret.AddLast(*node);
            };

            ApplyAction(addFunc, TraverseTypes::PRE_ORDER);

            return ret;
        }

        friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree) {
            std::stringstream ss;
            ss << "[";
            auto printAction = [&ss] (BinaryNode *nodePtr) -> void {
                ss << *nodePtr << ", ";
            };
            tree.ApplyAction(printAction, TraverseTypes::PRE_ORDER);
            std::string ret = ss.str();
            if(ret.length() > 1) ret.erase(ret.length() - 2, 2); // remove trailing ", "
            ret += "]";
            os << ret;
            return os;
        }

    private:
        void Add(BinaryNode*& localRoot, const TKey& key, const TValue& val) {
            if(localRoot == nullptr)
                localRoot = new BinaryNode(key, val); // this is why we need to pass the pointer by ref
            else {
                if(key > localRoot->key)
                    Add(localRoot->right, key, val);
                else if(key < localRoot->key)
                    Add(localRoot->left, key, val);
                else
                    throw std::runtime_error("Duplicate keys are not allowed.");
            }
        }

        bool Remove(BinaryNode*& localRoot, const TKey& keyToRemove) {
            if(localRoot == nullptr)
                return false;
            else {
                if(keyToRemove < localRoot->key)
                    return Remove(localRoot->left, keyToRemove);
                else if(keyToRemove > localRoot->key)
                    return Remove(localRoot->right, keyToRemove);
                else {
                    // node found: need to know if it has children
                    if (localRoot->left != nullptr && localRoot->right != nullptr) {
                        BinaryNode *maximumAtTheLeft = GetMax(localRoot->left);

                        localRoot->key = maximumAtTheLeft->key;
                        localRoot->value = maximumAtTheLeft->value;
                        Remove(localRoot->left, maximumAtTheLeft->key);
                    } else if (localRoot->left != nullptr) {
                        delete localRoot;
                        localRoot = localRoot->left;
                    }else if(localRoot->right != nullptr) {
                        delete localRoot;
                        localRoot = localRoot->right;
                    } else {
                        // no children
                        delete localRoot;
                        localRoot = nullptr;
                    }
                    return true;
                }
            }
        }

        BinaryNode* GetMax(BinaryNode* localRoot) {
            if(localRoot == nullptr || localRoot->right == nullptr)
                return localRoot;
            else return GetMax(localRoot->right);
        }

        BinaryNode* GetMin(BinaryNode* localRoot) {
            if(localRoot == nullptr || localRoot->left == nullptr)
                return localRoot;
            else return GetMin(localRoot->left);
        }

        void ApplyActionInOrder(BinaryNode* localRoot, CallbackAction action) const {
            if(localRoot == nullptr)
                return;
            ApplyActionInOrder(localRoot->left, action);
            action(localRoot);
            ApplyActionInOrder(localRoot->right, action);
        }

        void ApplyActionPreOrder(BinaryNode* localRoot, CallbackAction action) const {
            if(localRoot == nullptr)
                return;
            action(localRoot);
            ApplyActionPreOrder(localRoot->left, action);
            ApplyActionPreOrder(localRoot->right, action);
        }

        void ApplyActionPostOrder(BinaryNode* localRoot, CallbackAction action) const {
            if(localRoot == nullptr)
                return;
            ApplyActionPostOrder(localRoot->left, action);
            ApplyActionPostOrder(localRoot->right, action);
            action(localRoot);
        }
    };
}

#endif //ALGORITHMS_BINARYTREE_H
