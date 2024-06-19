#include <iostream>
#include <vector>

int partition (std::vector<int>& arr, int left, int right) { // функция разбиения на два массива
    // left и right это указатели на границы массива который нужно отсортировать

    int pivot = arr[(left + right) / 2]; // выберем опорный элемент

    while (left <= right) { // пока индексы не встретились, то есть пока еще есть элементы которые нужно менять между собой
        while (arr[left] < pivot) // найдем слева следующий элемент который нужно заменить
            left++;
        while (arr[right] > pivot) // найдем элемент который нужно заменить справа
            right--;


        if (left <= right) { // если индексы все еще не встретились то заменяем элементы между собой
            std::swap (arr[left], arr[right]);
            left++; // индексы прыгают через друг друга и теперь индекс left это новое новая граница разбиения
            right--;
        }
    }

    return left; // возвращаем новую границу
}

void quickSort (std::vector<int>& arr, int left, int right) {
    // если длина массива меньше двух (значит что левый индекс перескочил через
    // правый или они стоят на одной и том же элементе), то выйдем
    if (left >= right)
        return;

    int mid = partition (arr, left, right); // получим новое разбиение
    quickSort (arr, left, mid - 1); // отсортируем левее разбиения
    quickSort (arr, mid, right); // отсортируем правее разбиения
}


int main () { // функция для проверки
    int n;    // введем длину массива
    std::cin >> n;

    std::vector<int> arr (n, 0); // создадим массив

    for (int i = 0; i < n; ++i) // введем элементы массива
        std::cin >> arr[i];

    // отсортируем массив
    // передача индексов 0 и n - 1 означает что нужно отсортировать весь массив
    quickSort (arr, 0, n - 1);

    for (int i = 0; i < n; ++i) // выведем элементы массива
        std::cout << arr[i] << " ";


    return 0;
}