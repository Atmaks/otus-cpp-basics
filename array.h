#pragma once

#include <cstring>
// чтобы не мучаться с выводом в main
#include <iostream>

template <typename T>
class MyArray
{
public:
    MyArray()
    {
        this->storage = new T[this->capacity];
    }

    void push_back(const T &value)
    {
        if (this->elementCount == this->capacity)
        {
            this->grow(10);
        }

        this->storage[this->elementCount] = value;
        this->elementCount++;
    }

    void insert(size_t position, const T &value)
    {
        // если это за пределами массива - нет!
        if (position >= this->capacity)
        {
            // TODO: как-то обработать ошибку
            return;
        }

        // готовимся к перемещению, доращивая при необходимости
        if (this->elementCount == capacity)
        {
            this->grow(10);
        }

        // перемещаем элементы вперед на единичку
        T *pointerAtPosition = this->storage + position;
        std::memmove(pointerAtPosition + 1, pointerAtPosition, (this->elementCount - position) * sizeof(T));
        this->storage[position] = value;
        this->elementCount++;
    }

    void erase(size_t position, size_t length = 1)
    {
        // проверяем, нужно ли что-то делать
        if (position >= this->elementCount || length == 0)
        {
            return;
        }

        // это конец, просто двигаем указатель на последний элемент
        if (length >= this->elementCount - position)
        {
            this->elementCount = position;
        }
        // это внутри, выполняем перемещение
        else
        {
            T *pointerAtPosition = this->storage + position;
            this->elementCount -= length;
            std::cerr << "values are " << this->elementCount << " " << position << std::endl;
            std::memmove(pointerAtPosition, pointerAtPosition + length, (this->elementCount - position) * sizeof(T));
        }
    }

    size_t size()
    {
        return this->elementCount;
    }

    T &operator[](size_t position)
    {
        // tbh я не знаю, как правильно обработать ошибку
        if (position >= this->elementCount)
        {
            return this->storage[this->elementCount - 1];
        }

        return this->storage[position];
    }

    void print()
    {
        std::cout << "elements:";

        for (size_t i = 0; i < this->elementCount; i++)
        {
            std::cout << " ";
            std::cout << this->storage[i];
        }
        std::cout << std::endl;

        std::cout << "size: " << this->size() << ", ";
        std::cout << "capacity: " << this->capacity << std::endl;
    }

    ~MyArray()
    {
        delete this->storage;
    }

private:
    void grow(size_t thisMuch)
    {
        this->capacity += thisMuch;

        T *newStorage = new T[this->capacity];
        std::memmove(newStorage, this->storage, this->elementCount * sizeof(T));
        delete this->storage;
        this->storage = newStorage;
    }

    size_t elementCount = 0;
    size_t capacity = 10;
    T *storage;
};
