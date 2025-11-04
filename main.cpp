#include <iostream>

#include "array.h"
#include "list.h"

void demonstrateMyArray()
{
    std::cout << "----------------- ARRAY -----------------\n";

    auto myArray = MyArray<int>{};

    std::cout << "----- add ten elements to the container (0, 1 … 9)\n";
    myArray.push_back(0);
    myArray.push_back(1);
    myArray.push_back(2);
    myArray.push_back(3);
    myArray.push_back(4);
    myArray.push_back(5);
    myArray.push_back(6);
    myArray.push_back(7);
    myArray.push_back(8);
    myArray.push_back(9);
    myArray.print();

    // Тут вывод отличается от задания, видимо, потому что в задании подразумевается, что я пересчитаю индексы после удаления.
    // Напишите, пожалуйста, если так.
    std::cout << "----- delete the third (by count, not index), fifth and seventh elements\n";
    myArray.erase(3 - 1);
    myArray.erase(5 - 1);
    myArray.erase(7 - 1);
    myArray.print();

    std::cout << "----- prepend 10\n";
    myArray.insert(0, 10);
    myArray.print();

    std::cout << "----- insert 20 in the middle\n";
    myArray.insert(4, 20);
    myArray.print();

    std::cout << "----- append 30 at the end\n";
    myArray.push_back(30);
    myArray.print();

    std::cout << "----- check that access at index actually compiles\n";
    std::cout << "element at 5: " << myArray[5] << "\n";

    std::cout << "\n";
}

void demonstrateMyLinkedList()
{
    std::cout << "----------------- LINKED LIST -----------------\n";

    auto myList = MyLinkedList<int>{};

    std::cout << "----- add ten elements to the container (0, 1 … 9)\n";
    myList.push_back(0);
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.push_back(4);
    myList.push_back(5);
    myList.push_back(6);
    myList.push_back(7);
    myList.push_back(8);
    myList.push_back(9);
    myList.print();

    // Тут вывод отличается от задания, видимо, потому что в задании подразумевается, что я пересчитаю индексы после удаления.
    // Напишите, пожалуйста, если так.
    std::cout << "----- delete the third (by count, not index), fifth and seventh elements\n";
    myList.erase(3 - 1);
    myList.erase(5 - 1);
    myList.erase(7 - 1);
    myList.print();

    // добавление элемента 10 в начало контейнера
    std::cout << "----- prepend 10\n";
    myList.insert(0, 10);
    myList.print();

    // добавление элемента 20 в середину контейнера
    std::cout << "----- insert 20 in the middle\n";
    myList.insert(4, 20);
    myList.print();

    // добавление элемента 30 в конец контейнера
    std::cout << "----- append 30 at the end\n";
    myList.push_back(30);
    myList.print();

    std::cout << "----- check that access at index actually compiles\n";
    std::cout << "element at 5: " << myList[5] << "\n";

    std::cout << "\n";
}

int main()
{
    demonstrateMyArray();
    demonstrateMyLinkedList();
}
