//
// Created by Will Lee on 2021/9/5.
//
#include <iostream>

class Visitor;

class ConcreteElement;

class Element {
public:
    virtual void Accept(Visitor &visitor) = 0;

    virtual void Do() = 0;
};

class Visitor {
public:
    virtual void VisitElement(Element &element) = 0;

    virtual void VisitElement(ConcreteElement &element) = 0;
};

class ConcreteElement : public Element {
public:
    void Accept(Visitor &visitor) override {
        visitor.VisitElement(*this);
    }

    void Do() override {
        std::cout << "visit this " << __LINE__ << std::endl;
    }
};

class ConcreteVisitor : public Visitor {
public:
    void VisitElement(Element &element) override {
        element.Do();
    }

    void VisitElement(ConcreteElement &element) override {
        element.Do();
    }
};


int main() {
    ConcreteElement element;
    ConcreteVisitor visitor;
    visitor.VisitElement(element);
}