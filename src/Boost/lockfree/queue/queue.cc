//
// Created by Will Lee on 2021/10/27.
//

#include <boost/lockfree/queue.hpp>
#include <iostream>

int main() {
    std::cout << "hello lockFree queue" << std::endl;
    boost::lockfree::queue<int> queue(10);
    queue.push(1);
    int i;
    std::cout <<queue.pop(i) << std::endl;
}