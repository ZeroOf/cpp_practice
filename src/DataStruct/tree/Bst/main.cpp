
#include "BinaryTree.h"
#include <iostream>
#include <openssl/rand.h>
using namespace std;

int main() {
    int random[20]{};
    RAND_bytes(reinterpret_cast<unsigned char *>(random), sizeof random);
    BinaryTree tree;
    for(auto num : random) {
        std::cout << num << "\t";
        tree.Append(num);
    }
    std::cout << std::endl;
    std::cout << "test PreOrder" << std::endl;
    tree.PreOrder();
    cout << endl;
    cout << "test Level" << endl;
    tree.LevelOrder();

    cout << "test extream" << endl;
    cout << tree.Min(tree.root_)->value_ << endl;
    cout << tree.Max(tree.root_)->value_ << endl;

    cout << "test Search" << endl;
    cout << tree.Search(0) << endl;
}