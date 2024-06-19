#include <iostream>
#include <vector>


std::vector<int> Merge (std::vector<int> arr1, std::vector<int> arr2) { // функция слияния двух массивов
    std::vector<int> result (arr1.size () +
    arr2.size ()); // создадим массив длины как сумма двух которых будем сливать

    int first = 0; // индекс последнего не взятого элемента в первом массиве
    int second = 0; // индекс последнего не взятого элемента во втором массиве

    while ((first < arr1.size ()) && (second < arr2.size ())) { // пока не закончится один из массивов
        // если первый не взятый элемент из первого массива меньше,
        // чем первый не взятый элемент из второго, то берем из первого массива
        // если нет, то берем из второго массива
        if (arr1[first] <= arr2[second]) {
            result[first + second] = arr1[first]; // берем из первого массива
            first++; // мы взяли элемент, значит первый не взятый будет следующий элемент, сдвигаем индекс на 1 правее
        } else {
            result[first + second] = arr2[second]; // берем из второго массива
            second++; // мы взяли элемент, значит первый не взятый будет следующий элемент, сдвигаем индекс на 1 правее
        }
    }

    // если в первом массиве остались элементы, берем их все (значит второй закончился по условиям верхнего цикла)
    while (first < arr1.size ()) {
        result[first + second] = arr1[first];
        first++;
    }


    // если во втором массиве остались элементы, берем их все (значит закончился первый)
    while (second < arr2.size ()) {
        result[first + second] = arr2[second];
        second++;
    }

    return result; // возвращаем результат
}


std::vector<int> MergeSort (std::vector<int> arr) { // функция сортировки
    if (arr.size () < 2) // если размер массива меньше двух, то сортировать нечего. выходим
        return arr;

    int n = arr.size (); // получаем размер массива
    // поделим массив на две части
    int lsize = n / 2; // получаем размер первой части
    int rsize = n - lsize; // получаем размер второй части

    std::vector<int> arr1 (lsize, 0); // создали первую часть
    std::vector<int> arr2 (rsize, 0); // создали вторую часть

    for (int i = 0; i < lsize; ++i) // копируем элементы в первую часть
        arr1[i] = arr[i];

    for (int i = lsize; i < n; ++i) // копируем элементы во вторую часть
        arr2[i - lsize] = arr[i];

    arr1 = MergeSort (arr1); // сортируем первую часть
    arr2 = MergeSort (arr2); // вторую часть

    std::vector<int> result = Merge (arr1, arr2); // сливаем результаты

    return result; // возвращаем результат слияния
}


int main () { // функция для проверки
    int n;    // введем длину массива
    std::cin >> n;

    std::vector<int> arr (n, 0);

    for (int i = 0; i < n; ++i) // зададим элементы массива
        std::cin >> arr[i];

    arr = MergeSort (arr); // отсортируем

    for (int i = 0; i < n; ++i) // выведем отсортированный массив
        std::cout << arr[i] << " ";


    return 0;
}