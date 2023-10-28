#include <cstddef>
#include <initializer_list>
#pragma once

template<typename valueType>
class CircularBuffer {
    private:
        valueType* buffer = nullptr;
        size_t cap = 0;
        size_t start = 0;
        size_t end = 0;
        size_t currSize = 0;

        void swapElements(valueType* a, valueType* b);
    public:
        ~CircularBuffer();
        CircularBuffer(const CircularBuffer<valueType>& cb);
        CircularBuffer(std::initializer_list<valueType> list);

        /**
            @brief Create buffer with set capacity.
            @param capacity Buffer capacity
        */
        explicit CircularBuffer(int capacity);

        /**
            @brief Create buffer with set capacity and fills it with an element
            @param capacity Buffer capacity
            @param elem The element that fills the buffer
        */
        CircularBuffer(int capacity, const valueType& elem);

        /**
            @brief Access to circular buffer element by index.
            The correctness of the index is not checked.
            @param i - Index for access to circular buffer element.
        */
        valueType& operator [] (int i);
        const valueType& operator [] (int i) const;
        
        /**
            @brief Access to circular buffer element by index.
            The correctness of the index is checked.
            @param i - Index for access to circular buffer element.
            @throw std::out_of_range If index exceed count element in circular buffer.
        */
        valueType& at(int i);
        const valueType& at(int i) const;

        /**
            @brief Return link on first element in circular buffer.
            @throw std::out_of_range If buffer is empty.
        */
        valueType& front();
        const valueType& front() const;

        /**
            @brief Return link on last element in circular buffer.
            @throw std::out_of_range If buffer is empty.
        */
        valueType& back();
        const valueType& back() const;

        /**
            @brief Shifts circular buffer so that its first element
            moves to the beginning of the allocated memory.
            @return Return poiner on first circular buffer element.
        */
        valueType* linearize();

        /**
            @brief Checks whether the circular buffer is linearized.
            @return True - if buffer is linearized, false if buffer is not linearized.
        */
        bool isLinearized() const;
        
        /**
            @brief Shifts circular buffer so that the index is zero is an index newBegin.
            @param newBegin Index for shift.
            @throw std::out_of_range If index exceed count element in circular buffer.
        */
        void rotate(int newBegin);

        /**
            @brief Return count elements in buffer.
            @return Count element in buffer.
        */
        int size() const;

        /**
            @brief Checks if circular buffer is empty
            @return True if count elements in buffer is equally zero, false if not.
        */
        bool empty() const;

        /**
            @brief Checks if circular count elements in buffer is equally capacity.
            @return True if count elements in buffer equally capacity, false if not.
        */
        bool full() const;

        /**
            @brief Checks count free cells in circular buffer.
            @return Count free cells in circular buffer.
        */
        int reserve() const;
        
        /**
            @brief Return buffer capacity.
        */
        int capacity() const;

        /**
            @brief Reduces buffer capacity if new capacity is less than the current one.
            Otherwise does not candge in.
            @param newCapacity New circular buffer capacity. 
        */
        void setCapacity(int newCapacity);

        /**
            @brief Change buffer capacity. if new capacity is more than current capacity
            fill new buffer cells with an item.
            @param newSize New buffer capacity.
            @param item Item for fill new buffer cells.
            @throw std::invalid_argument if new size less than zero.
        */
        void resize(int newSize, const valueType& item = valueType());

        CircularBuffer& operator = (const CircularBuffer& cb);

        /**
            @brief Swap two buffer contents.
            @param cb Buffer to swap.
        */
        void swap(CircularBuffer& cb);
        
        /**
            @brief Add new element to buffer end. If count elements in buffer is equally
            buffer capacity than change first buffer element.
            @param item Item to push.
        */
        void pushBack(const valueType& item = valueType());
        
        /**
            @brief Add new element to buffer start. If count elements in buffer is equally
            buffer capacity than change last buffer element.
            @param item Item to push.
        */
        void pushFront(const valueType& item = valueType());

        /**
            @brief Delete last element in buffer.
            @throw std::out_of_range if count elements in buffer is equally zero.
        */
        void popBack();

        /**
            @brief Delete first element in buffer.
            @throw std::out_of_range if count elements in buffer is equally zero.
        */
        void popFront();

        /**
            @brief Inserts the element by index. Buffer capacity remains unchanged.
            @param pos Index to insert.
            @param item Element for insert.
            @throw std::out_of_range if index is more or equally buffer capacity.
        */
        void insert(int pos, const valueType& item = valueType());

        /**
            @brief Delete elements in inerval [first, last).
            @param first First index in interval.
            @param last Last index in interval.
            @throw std::out_of_range, std::invalid_argument
        */
        void erase(int first, int last);
        
        /**
            @brief Clear buffer without resize.
        */
        void clear();
};

template<typename valueType>
bool operator == (const CircularBuffer<valueType> & a, const CircularBuffer<valueType> & b) {
    if (a.size() != b.size()) {
        return false;
    }
    
    for (size_t i = 0; i < a.size(); ++i) {
        if (a.at(i) != b.at(i)) {
            return false;
        }
    }

    return true;
}

template<typename valueType>
bool operator != (const CircularBuffer<valueType> & a, const CircularBuffer<valueType> & b) {
    return !(a == b);
}