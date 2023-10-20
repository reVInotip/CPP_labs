#include "buffer/buffer.h"
#include <iostream>

int main() {
    CircularBuffer<int> buffer(5, 2);
    buffer.print();
    buffer.pushBack(10);
    buffer.pushBack(8);
    buffer.print();
    buffer.linearize();
    buffer.print();
    //std::cout << buffer.at(3) << std::endl;
}