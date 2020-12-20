
#ifndef CPP_PRACTICE_BINARYTREE_H
#define CPP_PRACTICE_BINARYTREE_H

#include "../Node.h"

class BinaryTree {
public:
    BinaryTree();

    void Append(int value);

    void PreOrder();

    void LevelOrder();

    Node *Search(int value);

    Node *Min(Node *pNode);

    Node *Max(Node *pNode);

    void AppendToNode(Node *pPos, Node *pAppend);

    void PreOrder(Node *);

    Node *Search(Node *pPos, int value);

    Node *root_;
};


#endif //CPP_PRACTICE_BINARYTREE_H
