
#include "Data.h"
#include <iostream>

using namespace std;

Data::Data() : s_("hello world") {}

Data *Data::GetPoint() {
    return this;
}

void Data::Print() {
    std::cout << s_ << std::endl;
}

SecondLayer::SecondLayer(Data *pData) : pData_(pData) {}

SecondLayer *SecondLayer::GetPoint() {
    return this;
}

SecondLayer &ThirdLayer::operator->() {
    return secondelayer_;
}

Data *SecondLayer::operator->() {
    return pData_;
}

ThirdLayer::ThirdLayer(Data *pData)
        : secondelayer_(pData) {}


SecondLayer &ThirdLayer::operator*() {
    return secondelayer_;
}

ForthLayer::ForthLayer(Data *pData) : thirdLayer_(pData) {}

ThirdLayer &ForthLayer::operator->() {
    return thirdLayer_;
}

ThirdLayer &operator*(ForthLayer &forthLayer) {
    return forthLayer.thirdLayer_;
}

int main() {
    cout << "Date Test" << endl;
    Data data;
    data.Print();
    data.GetPoint()->Print();
    data.GetPoint()->GetPoint()->Print();

    cout << "Second Layer Test" << endl;

    SecondLayer secondLayer(new Data);
    secondLayer->Print();
    secondLayer.GetPoint()->operator->()->Print();

    cout << "Third Layer Test" << endl;

    ThirdLayer thirdLayer(new Data);
    thirdLayer->Print();
    (*thirdLayer)->Print();

    cout << "Forth Layer Test" << endl;

    ForthLayer forthLayer(new Data);
    forthLayer->Print();
    (*forthLayer)->GetPoint()->Print();
}
