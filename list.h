#pragma once

#include <cstring>
// чтобы не мучаться с выводом в main
#include <iostream>

template <typename T>
struct ListNode
{
    T value;
    ListNode *next = nullptr;
};

template <typename T>
class MyLinkedList
{
public:
    MyLinkedList()
    {
    }

    // copy constructor
    MyLinkedList(const MyLinkedList<T>& other)
    {
        this->copyFrom(other);
    }

    // copy assignment
    MyLinkedList<T>& operator=(const MyLinkedList<T>& other)
    {
        this->copyFrom(other);
    }

    // move constructor
    MyLinkedList(MyLinkedList<T>&& other) noexcept
    {
        if (this != &other) {
            this->moveFrom(std::move(other));
        }
    }

    // move assignment
    MyLinkedList<T>& operator=(MyLinkedList<T>&& other) noexcept
    {
        if (this != &other) {
            this->moveFrom(std::move(other));
        }
        return this;
    }

    void push_back(const T &value)
    {
        if (this->head == nullptr)
        {
            this->head = new ListNode<T>{value, nullptr};
            this->elementCount += 1;
            return;
        }

        auto tail = this->head;
        while (tail->next != nullptr)
        {
            tail = tail->next;
        }

        tail->next = new ListNode<T>{value, nullptr};
        this->elementCount += 1;
    }

    void insert(size_t position, const T &value)
    {
        // list is empty and we want to init
        if (position == 0 && this->elementCount == 0)
        {
            this->head = new ListNode<T>{value, nullptr};
            return;
        }
        // position is outside our list, fuck 'em
        else if (position >= this->elementCount)
        {
            std::cerr << "Attempt to reference a position outside container";
            std::exit(1);
        }

        auto parentNode = position == 0 ? nullptr : this->walkTo(position - 1);

        // list is not empty but we want to insert at the start
        if (parentNode == nullptr)
        {
            this->head = new ListNode<T>{value, this->head};
        }
        // list is not empty, and we're not inserting at the start
        else
        {
            auto tmp = parentNode->next;
            parentNode->next = new ListNode<T>{value, tmp};
        }

        this->elementCount += 1;
    }

    void erase(size_t position, size_t length = 1)
    {
        // стираем в начале списка, надо заменить head
        if (position == 0)
        {
            auto currentNode = this->head;
            size_t counter = 0;
            while (length > 0)
            {
                auto tmp = currentNode->next;
                delete (currentNode);
                currentNode = tmp;

                counter++;
                length--;

                if (tmp == nullptr)
                {
                    break;
                }
            }

            this->head = currentNode;
            this->elementCount -= counter;

            return;
        }

        // Мы не в начале и position за пределами списка, делать нечего
        if (position >= this->elementCount || length == 0)
        {
            return;
        }

        // стираем не в начале
        auto parentNode = this->walkTo(position - 1);
        auto currentNode = parentNode->next;
        size_t counter = 0;
        while (length > 0)
        {
            auto tmp = currentNode->next;
            delete (currentNode);
            currentNode = tmp;

            counter++;
            length--;

            if (tmp == nullptr)
            {
                break;
            }
        }

        parentNode->next = currentNode;
        this->elementCount -= counter;
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
            std::cerr << "Attempt to reference a position outside container";
            std::exit(1);
        }

        return this->walkTo(position)->value;
    }

    void print()
    {
        std::cout << "elements: ";

        if (this->head == nullptr) {
            std::cout << "none";
        }
        else {
            auto tmp = this->head;
            while (tmp != nullptr)
            {
                std::cout << tmp->value << " ";
                tmp = tmp->next;
            }
        }

      
        std::cout << std::endl;

        std::cout << "size: " << this->elementCount << std::endl;
    }

    ~MyLinkedList()
    {
        this->deleteData();
    }

private:
    // подразумеваем, что position < elementCount
    ListNode<T> *walkTo(size_t position)
    {
        auto theNode = this->head;

        while (theNode != nullptr && theNode->next != nullptr && position > 0)
        {
            position--;
            theNode = theNode->next;
        }

        return theNode;
    }

    void copyFrom(const MyLinkedList<T>& other)
    {
        this->deleteData();

        this->elementCount = other.elementCount;

        ListNode<T>* otherCursor = other.head;
        ListNode<T>** thisCursor = &this->head;

        while (otherCursor != nullptr) {
            *thisCursor = new ListNode<T>{ otherCursor->value, nullptr };
            this->head = this->head == nullptr ? *thisCursor : this->head;
            thisCursor = &((*thisCursor)->next);
            otherCursor = otherCursor->next;
        }
    }

    void moveFrom(MyLinkedList<T>&& other)
    {
        if (this == &other) {
            return;
        }

        this->head = other.head;
        this->elementCount = other.elementCount;

        other.head = nullptr;
        other.elementCount = 0;
    }

    void deleteData()
    {
        while (this->head != nullptr)
        {
            auto tmp = this->head->next;
            delete this->head;
            this->head = tmp;
        }
        this->head = nullptr;
    }

    size_t elementCount = 0;
    ListNode<T> *head = nullptr;
};
