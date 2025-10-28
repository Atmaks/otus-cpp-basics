#include "array.h"

int main()
{
    auto myArray = MyArray<int>{};

    // добавление в контейнер десяти элементов (0, 1 … 9)
    // вывод содержимого контейнера на экран
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

    // удаление третьего (по счёту), пятого и седьмого элементов
    // Тут вывод отличается от задания, видимо, потому что в задании подразумевается, что я пересчитаю индексы после удаления.
    // Напишите, пожалуйста, если так.
    myArray.erase(3 - 1);
    myArray.erase(5 - 1);
    myArray.erase(7 - 1);
    myArray.print();

    // добавление элемента 10 в начало контейнера
    myArray.insert(0, 10);
    myArray.print();

    // добавление элемента 20 в середину контейнера
    myArray.insert(4, 20);
    myArray.print();

    // добавление элемента 30 в конец контейнера
    myArray.push_back(30);
    myArray.print();
}
