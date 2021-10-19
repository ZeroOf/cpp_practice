// question 1
class Base {
public:
    void DoSomeThing() {

    }

    void DoSomeThing(int i) {

    }

    virtual void LetChildDo() {

    }

    virtual ~Base() {

    }
};

class Derive : public Base {
public:
    void LetChildDo() override {

    }

    void DoSomeThing(int i, int j) {
    }

    virtual ~Derive() {

    }

};

int main() {
    Base *pBase = new Derive;
    pBase->LetChildDo();
    pBase->DoSomeThing();
    Derive *pDerive = dynamic_cast<Derive *>(pBase);
    pDerive->DoSomeThing(1, 2);
}