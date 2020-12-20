#include <iostream>

using std::cout;
using std::endl;

class Heap {
public:
    Heap()
            : _i(1), _j(2) {
        cout << "Heap " << endl;
    }

    void print() {
        cout << "_i = " << _i << endl
             << "_j = " << _j << endl;
    }

    void destroy() {
        cout << "destroy" << endl;
        delete this;
    }

private:
    int _i;
    int _j;

    ~Heap() {
        cout << "~Heap()" << endl;
    }
};

int main() {
    Heap *p = new Heap;
    p->print();
    p->destroy();
    return 0;
}

