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
        CircularBuffer();
        ~CircularBuffer();
        CircularBuffer(const CircularBuffer<valueType>& cb);
        CircularBuffer(std::initializer_list<valueType> list);

        //Конструирует буфер заданной ёмкости.
        explicit CircularBuffer(int capacity);
        //Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
        CircularBuffer(int capacity, const valueType& elem);

        //Доступ по индексу. Не проверяют правильность индекса.
        valueType& operator [] (int i);
        const valueType& operator [] (int i) const;
        
        //Доступ по индексу. Методы бросают исключение в случае неверного индекса.
        valueType& at(int i);
        const valueType& at(int i) const;

        valueType& front(); //Ссылка на первый элемент.
        valueType& back();  //Ссылка на последний элемент.
        const valueType& front() const;
        const valueType& back() const;

        //Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
        //переместится в начало аллоцированной памяти. Возвращает указатель 
        //на первый элемент.
        valueType* linearize();
        //Проверяет, является ли буфер линеаризованным.
        bool isLinearized() const;
        //Сдвигает буфер так, что по нулевому индексу окажется элемент 
        //с индексом newBegin.
        void rotate(int newBegin);
        //Количество элементов, хранящихся в буфере.
        int size() const;
        bool empty() const;
        //true, если size() == capacity().
        bool full() const;
        //Количество свободных ячеек в буфере.
        int reserve() const;
        //ёмкость буфера
        int capacity() const;

        void setCapacity(int newCapacity); // чо блять она делает?
        //Изменяет размер буфера.
        //В случае расширения, новые элементы заполняются элементом item.
        void resize(int newSize, const valueType& item = valueType());
        //Оператор присваивания.
        CircularBuffer& operator = (const CircularBuffer& cb);
        //Обменивает содержимое буфера с буфером cb.
        void swap(CircularBuffer& cb);

        //Добавляет элемент в конец буфера. 
        //Если текущий размер буфера равен его ёмкости, то переписывается
        //первый элемент буфера (т.е., буфер закольцован). 
        void pushBack(const valueType& item = valueType());
        //Добавляет новый элемент перед первым элементом буфера. 
        //Аналогично push_back, может переписать последний элемент буфера.
        void pushFront(const valueType& item = valueType());
        //удаляет последний элемент буфера.
        void popBack();
        //удаляет первый элемент буфера.
        void popFront();

        //Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
        void insert(int pos, const valueType& item = valueType());
        //Удаляет элементы из буфера в интервале [first, last).
        void erase(int first, int last);
        //Очищает буфер.
        void clear();

        void print(); // убрать!
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