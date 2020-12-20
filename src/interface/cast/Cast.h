
#ifndef CPP_PRACTICE_CAST_H
#define CPP_PRACTICE_CAST_H

class Cast {
public:
    //prohabit implicit conversion
    explicit Cast(int iNum);
    Cast(double iNum);
    operator int();
    operator double();

private:
    int iNum_;
};


#endif //CPP_PRACTICE_CAST_H
