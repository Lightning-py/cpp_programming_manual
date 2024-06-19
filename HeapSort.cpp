#include <algorithm>
#include <iostream>
#include <vector>


void siftDown (std::vector<int>& arr, int n, int i) { // функция просеивания
    int largest = i; // обозначим наш начальный элемент за самый большой
    int lchild = 2 * i + 1; // найдем его левого и правого детей
    int rchild = 2 * i + 2;


    if (lchild < n) { // если левый ребенок есть
        if (arr[lchild] > arr[largest]) // если левый ребенок больше самого большого элемента
            largest = lchild; // обновляем значение индекса самого большого элемента
    }

    if (rchild < n) { // если правый ребенок есть
        if (arr[rchild] > arr[largest]) // если правый ребенок больше самого большого элемента
            largest = rchild;           // обновляем значение
    }

    if (largest != i) { // если индекс самого большого элемента изменился
        std::swap (arr[i], arr[largest]); // меняем местами верхний элемент и максимум

        siftDown (arr, n, largest); // просеиваем вниз замененный элемент
    }
}


void HeapSort (std::vector<int>& arr) { // функция сортировки кучей
    int n = arr.size (); // получаем размер массива

    for (int i = n / 2 - 1; i >= 0; i--) // просеиваем все элементы снизу вверх чтобы построить кучу максимума
        siftDown (arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap (arr[0], arr[i]); // меняем первый элемент (он же i-й максимальный) с элементом на позиции i

        siftDown (arr, i, 0); // просеиваем смененный элемент чтобы оставить кучу максимальной кучей
    }
}


int main () { // функция для проверки
    int n;    // введем длину массива
    std::cin >> n;

    std::vector<int> arr (n, 0); // создадим массив

    for (int i = 0; i < n; ++i) // введем элементы массива
        std::cin >> arr[i];

    HeapSort (arr); // отсортируем

    for (int i = 0; i < arr.size (); ++i) // выведем все элементы
        std::cout << arr[i] << " ";

    return 0;
}