//
// Created by Will Lee on 2021/12/11.
//

#include <iostream>
#include <deque>

int main() {
    std::cout << "deque test" << std::endl;

    std::deque<int> container;
    container.push_back(1);
    auto it = container.begin();
    for (int i = 0; i < 10; ++i) {
        container.push_back(i);
        std::cout << (void*)&(*container.begin()) << std::endl;
        container.push_front(i);
        std::cout << (void*)&(*container.end()) << std::endl;
    }
    std::cout << *it << std::endl;
    std::cout << container.begin() - it << std::endl;
    container.resize(container.size() + 50);
    std::cout << container.end() - it << std::endl;
    container.resize(container.size() + 50);
    std::cout << container.end() - it << std::endl;
}