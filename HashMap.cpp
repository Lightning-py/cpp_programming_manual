#include <iostream>
#include <list>
#include <string>
#include <vector>

/*
    Понадобятся функции для хеширования, скопирую исходники
*/

// скопировал функцию для хеширования
unsigned long long
moduled_hash (std::string s, unsigned int k, unsigned long long module = __UINT64_MAX__) {
    unsigned long long sum = 0;

    unsigned long long power_now = 1;

    for (unsigned int i = 0; i < s.size (); ++i) {
        sum       = (sum + ((s[i] - 'a' + 1) * power_now) % module) % module;
        power_now = (power_now * k) % module;
    }


    return sum;
}

#define START_ELEMENS_COUNT 500 // задаем переменную

typedef unsigned long long ull; // делаем обозначение ull для типа unsigned long long
typedef std::pair<std::string, std::string> node; // делаем обозначение node для пары значений из двух строк

class HashTable {
    private:
    std::vector<std::list<node>> arr; // сам массив, в котором будем хранить списки

    size_t size; // размер
    size_t used; // сколько ячеек использовано


    ull getHash (std::string key); // функция для получения хеша
    ull getIndex (std::string key); // функция для получения индекса в массиве
    void rebuild (size_t new_size); // функция для увеличения длины массива
    void check_size (); // функция для проверки нужно ли увеличивать массив

    ull K; // число k для полиномиального хеша

    public:
    HashTable () { // конструктор по умолчанию
        this->size = START_ELEMENS_COUNT; // задаем изначальный размер
        this->used = 0;  // ипользовано 0 элементов
        this->K    = 33; // задаем K

        this->arr.assign (this->size, std::list<node> ()); // создаем вектор нужной длины
    }

    void push (std::string key, std::string val); // функция для вставки в таблицу
    void del (std::string key); // функция для удалени элемента по ключу
    std::string get (std::string key); // функция для нахождения элемента по ключу

    size_t getSize (); // функция для получения размера массива
};


size_t HashTable::getSize () { // тут все просто
    return this->size;
}


ull HashTable::getHash (std::string key) { // получаем хеш через функцию
    return moduled_hash (key, this->K);
}


ull HashTable::getIndex (std::string key) {
    // индекс по которому должны хранить элемент это остаток от деления хеша на длину массива
    return this->getHash (key) % this->size;
}


void HashTable::check_size () {
    // если больше 75 процентов ячеек использовано, делаем массив больше
    if (this->used >= (this->size * 0.75))
        this->rebuild (this->size * 10);
}


void HashTable::rebuild (size_t new_size) {
    size_t old_size = this->size; // сохраняем старый размер

    this->size = new_size; // обновляем размер массива

    std::vector<std::list<node>> new_arr (
    new_size, std::list<node> ()); // создаем новый массив нужной длины

    for (int i = 0; i < old_size; ++i) { // проходимся по всем ячейкам массива
        std::list<node> element_now =
        this->arr[i]; // получаем список, который лежит в нужной ячейке

        std::list<node>::iterator it = element_now.begin (); // получаем итератор на начало списка

        while (it != element_now.end ()) { // проходимся до конца списка
            ull new_index = getIndex (it->first); // получаем новый индекс текущего элемента в списке

            new_arr[new_index].push_back (std::make_pair (it->first, it->second)); // записываем по индексу в новый массив

            it++; // продвигаемся на элемент вперед по списку
        }
    }

    this->arr = new_arr; // подменяем старый массив на обновленный
}

void HashTable::push (std::string key, std::string value) {
    this->check_size (); // проверяем не нужно ли обновить длину массива

    ull index = getIndex (key); // получаем индекс элемента

    std::list<node>* list =
    &(this->arr[index]); // получаем список, в который нужно положить элемент

    if (list->size () == 0) // если длина списка равна нулю, то есть список до этого не использовался
        this->used++; // теперь этот список будет использоваться, поэтому прибавим 1 к количеству использованных ячеек

    list->push_back (std::make_pair (key, value)); // добавляем в список новое значение
}

std::string HashTable::get (std::string key) {
    ull index = getIndex (key); // получаем индекс элемента

    std::list<node>::iterator it =
    this->arr[index].begin (); // получаем итератор на нужный список

    while ((it->first != key) && (it != this->arr[index].end ())) // пока итератор не найдет нужный элемент или список не закончится - мы идем дальше
        it++; // двигаем итератор на следующий элемент

    if (it != this->arr[index].end ()) // если итератор таки нашел нужный элемент - возвращаем его
        return it->second;

    return std::string (""); // если нужного элемента не было - вернем пустую строку
}

void HashTable::del (std::string key) {
    ull index = getIndex (key); // получим индекс элемента

    std::list<node>::iterator it = this->arr[index].begin (); // получим итератор на нужный список

    // как и в предыдущей функции попытаемся найти элемент
    while ((it->first != key) && (it != this->arr[index].end ()))
        it++;

    if (it == this->arr[index].end ()) // если элемента не было то удалять ничего не нужно, выходим
        return;

    this->arr[index].erase (it); // если элемент был - удаляем его из списка
}


int main () {        // функция для тестирования
    HashTable table; // создаем хеш-таблицу

    table.push ("no", "yes"); // пушим два значения
    table.push ("yes", "no");

    std::cout << table.get ("kek")
              << std::endl; // пытаемся получить несколько значений, в том числе то которого не должно быть
    std::cout << table.get ("yes") << std::endl;
    std::cout << table.get ("no") << std::endl;

    table.del ("no"); // удаляем один элемент

    std::cout << table.get ("kek") << std::endl; // снова пытаемся получить те же значения
    std::cout << table.get ("yes") << std::endl;
    std::cout << table.get ("no") << std::endl;

    return 0;
}