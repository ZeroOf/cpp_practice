//
// Created by Will Lee on 2021/9/11.
//

struct A {
    virtual ~A() = default;
};

struct B {
    virtual ~B() = default;
};

struct D : A, B {
};

int main() {

    B *pb = new D();
//    A *pa = static_cast<A *>(pb); // OK
    A *pa = dynamic_cast<A *>(pb); // OK
}