#ifndef CPP_PRACTICE_BRACE_H
#define CPP_PRACTICE_BRACE_H

class Brace {
public:
    int operator()(int i, int j);
    int operator()(int i, int j, int k);
    int count_= 0;
};

#endif //CPP_PRACTICE_BRACE_H
