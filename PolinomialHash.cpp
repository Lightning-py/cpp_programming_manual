#include <cmath> // для функции pow
#include <iostream>
#include <string>


unsigned long long get_hash (std::string s, unsigned int k) { // функция для получения хеша
    unsigned long long sum = 0; // сумма изначально равна 0

    /*
        чтобы определить порядковый номер буквы в алфавите используем небольшую
       фишку типа char так как char представляется как int, то можно вычесть из
       буквы 'a' и получить порядковый номер в английском алфавите вот так:
       (symbol - 'a' + 1)
        + 1 для того чтобы первая буква была под номером 1
    */

    for (unsigned int i = 0; i < s.size (); ++i) // создадим счетчик i
        sum += (s[i] - 'a' + 1) *
        std::pow (k, i); // по формуле прибавляем произведение порядкового номера буквы на степень k

    return sum;
}


int main () {                 // функция для проверки
    std::string s = "abcdef"; // создадим строку
    std::string s2 = "abcdefh"; // вторую стрку чуть от нее отличающуюся

    unsigned int k = 33; // создадим k больше чем размер английского алфавита

    std::cout << get_hash (s, k) << std::endl; // выведем два хеша от наших строк
    std::cout << get_hash (s2, k) << std::endl;

    return 0;
}