#include "buffer.h"
#include <cstddef>
#include <initializer_list>
#include <new>
#include <sstream>
#include <stdexcept>
#include <iostream>

using std::out_of_range, std::invalid_argument, std::string, std::stringstream;

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
CircularBuffer<valueType>::~CircularBuffer() {
    delete [] buffer;
}

template<typename valueType>
CircularBuffer<valueType>::CircularBuffer(int capacity) {
    buffer = new valueType[capacity];
    cap = capacity;
}

template<typename valueType>
CircularBuffer<valueType>::CircularBuffer(int capacity, const valueType& elem) : CircularBuffer(capacity) {
    for(size_t i = 0; i < capacity; ++i) {
        buffer[i] = elem;
    }
    end = capacity - 1;
    currSize = capacity;
}

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
CircularBuffer<valueType>::CircularBuffer(std::initializer_list<valueType> list) : CircularBuffer(list.size()) {
    size_t i = 0;
    for (valueType val : list) {
        buffer[i++] = val;
    }
    currSize = list.size();
    end = cap - 1;
}

template<typename valueType>
valueType& CircularBuffer<valueType>::operator [] (int i) {
    return buffer[(start + i) % cap];
}

template<typename valueType>
const valueType& CircularBuffer<valueType>::operator [] (int i) const {
    return buffer[(start + i) % cap];
}

template<typename valueType>
valueType& CircularBuffer<valueType>::at(int i) {
    if (i >= currSize) {
        stringstream strStream;
        strStream << "Index: " << i << " >= " << currSize << " there " << currSize << " is count elements in buffer!";
        throw out_of_range(strStream.str());
    }
    return buffer[(start + i) % cap];
}

template<typename valueType>
const valueType& CircularBuffer<valueType>::at(int i) const {
    if (i >= currSize) {
        stringstream strStream;
        strStream << "Index: " << i << " >= " << currSize << " there " << currSize << " is count elements in buffer!";
        throw out_of_range(strStream.str());
    }
    return buffer[(start + i) % cap];
}

template<typename valueType>
valueType& CircularBuffer<valueType>::front() {
    if (currSize == 0) {
        throw out_of_range("Circular buffer is empty!");
    }
    return buffer[start];
}

template<typename valueType>
const valueType& CircularBuffer<valueType>::front() const {
    if (currSize == 0) {
        throw out_of_range("Circular buffer is empty!");
    }
    return buffer[start];
}

template<typename valueType>
valueType& CircularBuffer<valueType>::back() {
    if (currSize == 0) {
        throw out_of_range("Circular buffer is empty!");
    }
    return buffer[end];
}

template<typename valueType>
const valueType& CircularBuffer<valueType>::back() const {
    if (currSize == 0) {
        throw out_of_range("Circular buffer is empty!");
    }
    return buffer[end];
}

template<typename valueType>
valueType* CircularBuffer<valueType>::linearize() {
    if (currSize == 0) {
        return nullptr;
    }

    for(size_t i = 0; i < start; ++i) {
        for(size_t j = 0; j < cap - 1; ++j) {
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
    if (currSize == 0) {
        return;
    } else if (newBegin >= currSize) {
        stringstream strStream;
        strStream << "Index: " << newBegin << " >= " << currSize << " there " << currSize << " is count elements in buffer!";
        throw out_of_range(strStream.str());
    }

    for(size_t i = 0; i < newBegin; ++i) {
        for(size_t j = 0; j < currSize - 1; ++j) {
            swapElements(&buffer[j], &buffer[j + 1]);
        }
    }

    start = (newBegin > start) ? ((start + currSize - 1) - newBegin) : (start - newBegin);
    end = (newBegin > end) ? ((end + currSize - 1) - newBegin) : (end - newBegin);
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
    if (newCapacity == cap) {
        return;
    }

    valueType* newBuffer = new valueType[newCapacity];
    if (!isLinearized()) {
        linearize();
    }

    for(size_t i = 0; i < newCapacity; ++i) {
        if (i <= currSize - 1) {
            newBuffer[i] = buffer[i];
        }
    }

    delete [] buffer;
    buffer = newBuffer;
    cap = newCapacity;

    if (newCapacity < currSize) {
        currSize = newCapacity;
        end = newCapacity - 1;
    }
}

template<typename valueType>
void CircularBuffer<valueType>::resize(int newSize, const valueType& item) {
    if (newSize < 0) {
        throw invalid_argument("Cricular buffer size can not be less than zero!");
    } else if (newSize == cap) {
        return;
    }

    valueType* newBuffer = new valueType[newSize];
    if (!isLinearized()) {
        linearize();
    }

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
        delete [] buffer;
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
    CircularBuffer<valueType> a = cb;
    cb = *this;
    *this = a;
}

template<typename valueType>
void CircularBuffer<valueType>::pushBack(const valueType& item) {
    if (cap == 0) {
        return;
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
        return;
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
        throw out_of_range("Circular buffer is empty!");
    }
    end = (end == 0) ? cap - 1 : end - 1;
    --currSize;
}

template<typename valueType>
void CircularBuffer<valueType>::popFront() {
    if (currSize == 0) {
        throw out_of_range("Circular buffer is empty!");
    }
    start = (start + 1) % cap;
    --currSize;
}

template<typename valueType>
void CircularBuffer<valueType>::insert(int pos, const valueType& item) {
    if (pos >= cap) {
        stringstream strStream;
        strStream << "Index: " << pos << " >= " << cap << " there " << cap << " is circular buffer limit!";
        throw out_of_range(strStream.str());
    }
    buffer[(start + pos) % cap] = item;
}

template<typename valueType>
void CircularBuffer<valueType>::erase(int first, int last) {
    if (first >= currSize) {
        stringstream strStream;
        strStream << "Index: " << first << " >= " << currSize << " there " << currSize << " is count elements in buffer!";
        throw out_of_range(strStream.str());
    } else if (last - 1 >= currSize) {
        stringstream strStream;
        strStream << "Index: " << last - 1 << " (last - 1) >= " << currSize << " there " << currSize << " is count elements in buffer!";
        throw out_of_range(strStream.str());
    } else if (first < 0) {
        stringstream strStream;
        strStream << "Index: " << first << " can not be less than zero!";
        throw invalid_argument(strStream.str());
    } else if (last - 1 < 0) {
        stringstream strStream;
        strStream << "Index: " << last - 1 << " (last - 1) can not be less than zero!";
        throw invalid_argument(strStream.str());
    } else if (first > last - 1) {
        stringstream strStream;
        strStream << "Index " << first << " (first) can not be less than " << last - 1 << " (last - 1)!";
        throw invalid_argument(strStream.str());
    }

    for (size_t i = first; i < currSize; ++i) {
        buffer[(start + i) % currSize] = buffer[(start + i + (last - first)) % currSize];
    }

    end = (end <= last - first - 1) ? end - (last - first - 1) + cap - 1 : end - (last - first - 1);
    currSize -= last - first;
}

template<typename valueType>
void CircularBuffer<valueType>::clear() {
    currSize = 0;
    start = 0;
    end = 0;
}

// end

template class CircularBuffer<int>;
template class CircularBuffer<string>;
template class CircularBuffer<char>;