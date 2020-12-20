
#ifndef CPP_PRACTICE_NODE_H
#define CPP_PRACTICE_NODE_H

struct Node {
    Node *parent_ = nullptr;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
    int value_ = 0;
};

#endif //CPP_PRACTICE_NODE_H
