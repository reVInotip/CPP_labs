#include "buffer/buffer.h"
#include <iostream>

int main() {
    CircularBuffer<int> buffer(5, 2);
    buffer.print();
    std::cout << "-----------------" << std::endl;
    buffer.pushBack(10);
    buffer.pushBack(8);
    buffer.print();
    std::cout << "-----------------" << std::endl;
    buffer.pushFront(7);
    buffer.pushFront(5);
    buffer.print();
    std::cout << "-----------------" << std::endl;
    if (!buffer.isLinearized()) {
        buffer.linearize();
    }
    buffer.print();
    std::cout << "-----------------" << std::endl;
    buffer.rotate(3);
    buffer.print();
    std::cout << "-----------------" << std::endl;
    CircularBuffer<int> buffer2(2, 3);
    buffer2.resize(3, 4);
    buffer2.print();
    std::cout << "-----------------" << std::endl;
    buffer.swap(buffer2);
    buffer.print();
    buffer2.print();
    std::cout << "-----------------" << std::endl;
    buffer.resize(2);
    buffer.print();
    std::cout << "-----------------" << std::endl;
    buffer2.erase(2, 5);
    buffer2.print();
}