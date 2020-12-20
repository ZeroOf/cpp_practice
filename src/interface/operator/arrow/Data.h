
#ifndef CPP_PRACTICE_INTERFACE_ARROW_DATA_H_
#define CPP_PRACTICE_INTERFACE_ARROW_DATA_H_

#include <string>

class Data {
public:
    Data();

    Data *GetPoint();

    void Print();

private:
    std::string s_;

    friend std::ostream &operator<<(std::ostream &ost, const Data &data);
};

class SecondLayer {
public:
    SecondLayer(Data *pData);

    SecondLayer *GetPoint();

    Data *operator->();

private:
    Data *pData_;
};

class ThirdLayer {
public:
    ThirdLayer(Data *pData);

    SecondLayer &operator->();

    SecondLayer &operator*();

private:
    SecondLayer secondelayer_;
};

class ForthLayer {
public:
    ForthLayer(Data *pData);

    ThirdLayer &operator->();

    friend ThirdLayer &operator*(ForthLayer &forthLayer);

private:
    ThirdLayer thirdLayer_;
};

#endif //CPP_PRACTICE_INTERFACE_ARROW_DATA_H_
