#include <iostream>


void Karatsuba (int* a, int* b, int* c, int n) {
    if (n <= 10) { // если длина числа меньше 10 будем использовать наивный алгоритм
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                c[i + j] += a[i] * b[j];
        }
    } else {
        int k  = n / 2; // поделим массив на две части
        int* l = new int[k]; // левая часть
        int* r = new int[k]; // правая часть
        int* t = new int[n]; // массив для t

        for (int i = 0; i < k; ++i) { // заполняем l и r числами a1 + a2 и b1 + b2 соответственно
            l[i] = a[i] + a[k + i];
            r[i] = b[i] + b[k + i];
        }

        Karatsuba (l, r, t, k); // посчитаем t
        Karatsuba (a, b, c, k); // посчитаем произведение первых k разрядов a и b, получится p1
        Karatsuba (a + k, b + k, c + k, k); // посчитаем произведение вторых k разрядов a и b, получится p2

        // разделим массив на 4 части, s1, s2, s3, s4
        // где конкатенация s1 и s2 это p1
        // конкатенация s3 и s4 это p2
        // и нужно прибавить часть (t - p1 - p2) к конкатенации частей s2 и s3

        int* s1 = c;
        int* s2 = c + k;
        int* s3 = c + 2 * k;
        int* s4 = c + 3 * k;

        // разделим t на две части, t1 и t2
        // t1 будет лежать там же где и s2, t2 будет лежать там же где и s3

        int* t1 = t;
        int* t2 = t + k;

        // часть s1 и часть s4 определены и готовы, осталось прибавить вычесть из t p1 и p2, после чего прибавить его к позициям s2 и s3
        // будем последовательно считать коэфициенты, друг за другом, но одноврменно для частей s2 и s3

        for (int i = 0; i < 2 * k; ++i) {
            int c1 = s2[i] + (t1[i] - s1[i] - s3[i]);
            int c2 = s3[i] + (t2[i] - s2[i] - s4[i]);

            c[k + i] = c1;
            c[n + i] = c2;
        }

        // удалим использованные массивы
        delete[] l;
        delete[] r;
        delete[] t;
    }
}

int ToNearestPowerOfTwo (int number) { // функция для приведения числа к ближайшей степени двойки
    int i = 1;

    while (number > i)
        i *= 2;

    return i;
}


int main () { // функция для проверки
    int n;    // введем длину чисел
    std::cin >> n;

    int NearestPowerOfTwo = ToNearestPowerOfTwo (n); // приведем к ближайшей степени двойки

    int* a = new int[NearestPowerOfTwo]; // создадим массивы a и b
    int* b = new int[NearestPowerOfTwo];

    for (int i = 0; i < n; ++i) // введем коэфициенты для a и b
        std::cin >> a[i];

    for (int i = 0; i < n; ++i)
        std::cin >> b[i];

    int* c = new int[2 * NearestPowerOfTwo]; // создадим массив для записи результата

    Karatsuba (a, b, c, n); // переменожим

    for (int i = 0; i < 2 * NearestPowerOfTwo; ++i) // выведем результат
        std::cout << c[i] << " ";

    std::cout << std::endl;

    // удалим массивы
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}