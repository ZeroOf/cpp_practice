
#ifndef CPP_PRACTICE_BRNODE_H
#define CPP_PRACTICE_BRNODE_H

#include "../Node.h"

enum Color {
    RED,
    BLACK
};

struct BRNode : public Node {
    Color color_;
};
#endif //CPP_PRACTICE_BRNODE_H
