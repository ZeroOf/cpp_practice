
#include "BinaryTree.h"
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

BinaryTree::BinaryTree()
        : root_(nullptr) {}

void BinaryTree::Append(int value) {
    Node *pNode = new Node{nullptr, nullptr, nullptr, value};
    if (nullptr == root_) {
        root_ = pNode;
        return;
    }
    AppendToNode(root_, pNode);
}

void BinaryTree::AppendToNode(Node *pPos, Node *pAppend) {
    if (pPos->value_ < pAppend->value_) {
        if (pPos->right_ != nullptr) {
            AppendToNode(pPos->right_, pAppend);
            return;
        }
        pPos->right_ = pAppend;
        pAppend->parent_ = pPos;
        return;
    }
    if (pPos->left_ != nullptr) {
        AppendToNode(pPos->left_, pAppend);
        return;
    }
    pPos->left_ = pAppend;
    pAppend->parent_ = pPos;
}

void BinaryTree::PreOrder() {
    PreOrder(root_);
}

void BinaryTree::PreOrder(Node *pNode) {
    if (nullptr == pNode) {
        return;
    }
    if (pNode->left_ != nullptr) {
        PreOrder(pNode->left_);
    }
    std::cout << std::setw(13) << std::left << pNode->value_;
    if (pNode->right_ != nullptr) {
        PreOrder(pNode->right_);
    }
}

void BinaryTree::LevelOrder() {
    Node *pPos = root_;
    queue<Node *> nodeQ;
    nodeQ.push(pPos);
    int layer = 0;
    while (0 != nodeQ.size()) {
        cout << "layer " << ++layer << ":";
        size_t count = nodeQ.size();
        for (int i = 0; i < count; ++i) {
            Node *pCur = nodeQ.front();
            nodeQ.pop();
            if (nullptr != pCur) {
                cout << setw(13) << pCur->value_;
                if (nullptr != pCur->left_) {
                    nodeQ.push(pCur->left_);
                }
                if (nullptr != pCur->right_) {
                    nodeQ.push(pCur->right_);
                }
            }
        }
        cout << endl;
    }
}

Node *BinaryTree::Min(Node *pNode) {
    while (pNode != nullptr && pNode->left_ != nullptr) {
        pNode = pNode->left_;
    }
    return pNode;
}

Node *BinaryTree::Max(Node *pNode) {
    while (pNode != nullptr && pNode->right_ != nullptr) {
        pNode = pNode->right_;
    }
    return pNode;
}

Node *BinaryTree::Search(Node *pPos, int value) {
    Node *pRet = pPos;
    while (pRet != nullptr && pRet->value_ != value) {
        if (pRet->value_ > value) {
            pRet = pRet->left_;
            continue;
        }
        if (pRet->value_ < value) {
            pRet = pRet->right_;
        }
    }
    return pRet;
}

Node *BinaryTree::Search(int value) {
    return Search(root_, value);
}
