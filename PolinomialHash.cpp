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

unsigned long long moduled_hash (std::string s, unsigned int k, unsigned long long module) {
    /*
        Для больших строк хеш может быть очень большим, ведь мы используем степени k

        У этой проблемы есть решение - брать хеш по модулю большого числа (традиционно берут простое число 10e9 + 7)

        sum % mod = (a1 + a2 + a3 + ... + an) % mod = (((a1 % mod) + (a2 % mod)) % mod + (a3 % mod)) % mod + ...

        ^ свойста модульной арифметики
    */

    unsigned long long sum = 0;

    unsigned long long power_now = 1; // переменная для накопления степени числа

    for (unsigned int i = 0; i < s.size (); ++i) {
        sum = (sum + ((s[i] - 'a' + 1) * power_now) % module) % module; // 30-я строка момент
        power_now = (power_now * k) % module; // переменная со степенью k по модулю
    }


    return sum;
}


int main () {                 // проверка
    std::string s = "abcdef"; // создадим строку
    std::string s2 = "abcdefh"; // вторую стрку чуть от нее отличающуюся

    unsigned int k = 33; // создадим k больше чем размер английского алфавита


    std::cout << get_hash (s, k) << std::endl; // выведем два хеша от наших строк
    std::cout << get_hash (s2, k) << std::endl;

    std::cout << moduled_hash (s, k, 10e9 + 7) << std::endl; // возьмем два хеша по модулю
    std::cout << moduled_hash (s2, k, 10e9 + 7) << std::endl;


    /*
        Первый должен совпасть со вторым, потому что хеш не нестолько большой, чтобы модуль его порезал
        А вот второй уже будет обрезан, потому что он очевидно больше чем (10e9 + 7)
    */

    return 0;
}