#include "buffer.h"
#include <cstddef>
#include <new>
#include <stdexcept>
#include <iostream>

using std::out_of_range, std::invalid_argument;

// private functions

template<typename valueType>
void CircularBuffer<valueType>::swapElements(valueType* a, valueType* b) {
    valueType c = *a;
    *a = *b;
    *b = c;
}

// end
// public functions

template<typename valueType>
CircularBuffer<valueType>::CircularBuffer() {}

template<typename valueType>
CircularBuffer<valueType>::~CircularBuffer() {
    delete [] buffer;
    cap = 0;
    currSize = 0;
    end = 0;
    start = 0;
}

template<typename valueType>
CircularBuffer<valueType>::CircularBuffer(int capacity) {
    buffer = new valueType[capacity];
    cap = capacity;
}

template<typename valueType>
CircularBuffer<valueType>::CircularBuffer(int capacity, const valueType& elem) {
    buffer = new valueType[capacity];
    for(size_t i = 0; i < capacity; ++i) {
        buffer[i] = elem + i; // временно для тестов, удалить позже
    }
    cap = capacity;
    end = capacity - 1;
    currSize = capacity;
}

// TO-DO Протестить проверку на совпадение типов
template<typename valueType>
CircularBuffer<valueType>::CircularBuffer(const CircularBuffer<valueType>& cb) {
    buffer = new valueType[cb.cap];
    for(size_t i = 0; i < cb.currSize; ++i) {
        buffer[i] = cb.buffer[i];
    }
    cap = cb.cap;
    start = cb.start;
    end = cb.end;
    currSize = cb.currSize;
}

template<typename valueType>
valueType& CircularBuffer<valueType>::operator [] (int i) {
    return buffer[start + i];
}

template<typename valueType>
const valueType& CircularBuffer<valueType>::operator [] (int i) const {
    return buffer[start + i];
}

template<typename valueType>
valueType& CircularBuffer<valueType>::at(int i) {
    if (i >= cap) {
        throw out_of_range("Circular buffer index out of range!");
    }
    return buffer[(start + i) % cap];
}

template<typename valueType>
const valueType& CircularBuffer<valueType>::at(int i) const {
    if (i >= cap) {
        throw out_of_range("Circular buffer index out of range!");
    }
    return buffer[(start + i) % cap];
}

template<typename valueType>
valueType& CircularBuffer<valueType>::front() {
    if (cap == 0) {
        throw out_of_range("Circular buffer index out of range!");
    }
    return buffer[start];
}

template<typename valueType>
const valueType& CircularBuffer<valueType>::front() const {
    if (cap == 0) {
        throw out_of_range("Circular buffer index out of range!");
    }
    return buffer[start];
}

template<typename valueType>
valueType& CircularBuffer<valueType>::back() {
    if (cap == 0) {
        throw out_of_range("Circular buffer index out of range!");
    }
    return buffer[end];
}

template<typename valueType>
const valueType& CircularBuffer<valueType>::back() const {
    if (cap == 0) {
        throw out_of_range("Circular buffer index out of range!");
    }
    return buffer[end];
}

template<typename valueType>
valueType* CircularBuffer<valueType>::linearize() {
    if (cap == 0) {
        return nullptr;
    }

    for(size_t i = 0; i < start; ++i) {
        for(size_t j = 0; j < currSize - 1; ++j) {
            swapElements(&buffer[j], &buffer[j + 1]);
        }
    }

    start = 0;
    end = currSize - 1;
    return &buffer[0];
}

template<typename valueType>
bool CircularBuffer<valueType>::isLinearized() const {
    return (start == 0) && (end == currSize - 1);
}

template<typename valueType>
void CircularBuffer<valueType>::rotate(int newBegin) {
    if (cap == 0) {
        return;
    } else if (newBegin < currSize) {
        throw out_of_range("Circular buffer have not elements on this index!");
    }

    for(size_t i = 0; i < newBegin; ++i) {
        for(size_t j = 0; j < currSize - 1; ++j) {
            swapElements(&buffer[j], &buffer[j + 1]);
        }
    }

    start = start - newBegin;
    if (start < 0) {
        start += currSize;
    }

    end = end - newBegin;
    if (end < 0) {
        end += currSize;
    }
}

template<typename valueType>
int CircularBuffer<valueType>::size() const {
    return currSize;
}

template<typename valueType>
bool CircularBuffer<valueType>::empty() const {
    return currSize == 0;
}

template<typename valueType>
bool CircularBuffer<valueType>::full() const {
    return cap == currSize;
}

template<typename valueType>
int CircularBuffer<valueType>::reserve() const {
    return cap - currSize;
}

template<typename valueType>
int CircularBuffer<valueType>::capacity() const {
    return cap;
}

template<typename valueType>
void CircularBuffer<valueType>::setCapacity(int newCapacity) {
    if (newCapacity > cap) {
        return;
    }

    linearize();
    cap = newCapacity;
    end = newCapacity - 1;
}

template<typename valueType>
void CircularBuffer<valueType>::resize(int newSize, const valueType& item) {
    if (newSize < 0) {
        throw invalid_argument("New buffer size is invalid!");
    } else if (newSize == cap) {
        return;
    }

    valueType* newBuffer = new valueType[newSize];
    linearize();

    for(size_t i = 0; i < newSize; ++i) {
        if (i <= currSize - 1) {
            newBuffer[i] = buffer[i];
        } else {
            newBuffer[i] = item;
        }
    }

    delete [] buffer;
    buffer = newBuffer;
    cap = newSize;
    currSize = newSize;
    end = newSize - 1;
}

template<typename valueType>
CircularBuffer<valueType>& CircularBuffer<valueType>::operator = (const CircularBuffer& cb) {
    if (&cb != this) {
        buffer = new valueType[cb.cap];
        for(size_t i = 0; i < cb.currSize; ++i) {
            buffer[i] = cb.buffer[i];
        }
        cap = cb.cap;
        start = cb.start;
        end = cb.end;
        currSize = cb.currSize;
    }

    return *this;
}

template<typename valueType>
void CircularBuffer<valueType>::swap(CircularBuffer& cb) {
    CircularBuffer<valueType> a = *this;
    cb = *this;
    *this = a;
}

// убрать это
template<typename valueType>
void CircularBuffer<valueType>::print() {
    std::cout << "Start: " << start << "\t" << "End: " << end << "\n";
    for(int i = 0; i < currSize; ++i) {
        std::cout << buffer[i % cap] << "\t";
    }
    std::cout << std::endl;
}

template<typename valueType>
void CircularBuffer<valueType>::pushBack(const valueType& item) {
    if (cap == 0) {
        out_of_range("Circular buffer capacity is zero!");
    }

    if (currSize < cap) {
        end = (end + 1) % cap;
    } else {
        start = (start + 1) % cap;
        end = (end + 1) % cap;
    }
    buffer[end] = item;
    currSize = (currSize == cap) ? currSize : currSize + 1;
}

template<typename valueType>
void CircularBuffer<valueType>::pushFront(const valueType& item) {
    if (cap == 0) {
        out_of_range("Circular buffer capacity is zero!");
    }

    if (currSize < cap) {
        start = (start == 0) ? cap - 1 : start - 1;
    } else {
        start = (start == 0) ? cap - 1 : start - 1;
        end = (end == 0) ? cap - 1 : end - 1;
    }
    buffer[start] = item;
    currSize = (currSize == cap) ? currSize : currSize + 1;
}

template<typename valueType>
void CircularBuffer<valueType>::popBack() {
    if (currSize == 0) {
        throw out_of_range("Circular buffer alredy clear!");
    }
    end = (end == 0) ? cap - 1 : end - 1;
    --currSize;
}

template<typename valueType>
void CircularBuffer<valueType>::popFront() {
    if (currSize == 0) {
        throw out_of_range("Circular buffer alredy clear!");
    }
    start = (start + 1) % cap;
    --currSize;
}

template<typename valueType>
void CircularBuffer<valueType>::insert(int pos, const valueType& item) {
    if (pos >= cap) {
        throw out_of_range("Circular buffer index out of range!");
    }
    buffer[(start + pos) % cap] = item;
}

template<typename valueType>
void CircularBuffer<valueType>::erase(int first, int last) {
    if (first >= currSize || last - 1 >= currSize || first < 0 || last < 0 || first > last - 1) {
        throw out_of_range("Circular buffer index out of range!");
    }

    int j = 0;
    for (size_t i = last - 1; i < currSize; ++i) {
        buffer[(start + first + j) % currSize] = buffer[start - first + i + 1];
        ++j;
    }

    currSize -= last - first;
    end = (end >= last - first) ? end - (last - first) : end - (last - first) + currSize;
}

template<typename valueType>
void CircularBuffer<valueType>::clear() {
    currSize = 0;
    start = 0;
    end = 0;
}

template class CircularBuffer<int>;