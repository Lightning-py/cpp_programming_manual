#include <iostream>
#include <vector>

std::vector<int> BubbleSort (std::vector<int> arr) { // функция сортировки
    int n = arr.size (); // получим размер массива

    for (int i = n - 1; i >= 0; --i) { // цикл для уменьшения верхнего элемента
        for (int j = 0; j < i; ++j) { // цикл для прохода от 0 до верхнего элемента

            if (arr[j] > arr[j + 1]) { // замена если элементы стоят не в том порядке
                int swp    = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = swp;
            }
        }
    }

    return arr; // возвращаем отсортированный вектор
}


int main () { // функция для проверки
    int n;    // переменная для длины вектора
    std::cin >> n;

    std::vector<int> arr (n, 0); // создадим вектор нужной длины

    for (int i = 0; i < n; ++i) // считаем элементы вектора
        std::cin >> arr[i];


    arr = BubbleSort (arr); // отсортируем

    for (int i = 0; i < arr.size (); ++i) // выведем отсортированный вектор
        std::cout << arr[i] << " ";


    return 0;
}