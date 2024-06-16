#include <iostream>

/*
    я сделаю модификацию списка, добавлять элементы можно будет только с конца а забирать только с начала
*/

struct ListNode { // структура узла
    int data; // данные, могут быть любого типа. в качестве примера выбран int
    ListNode* next; // указатель на следующий узел
};

class List { // класс списка
    private:
    ListNode* head; // голова списка
    ListNode* tail; // хвост списка
    size_t lenght;  // длина списка

    public:
    List () { // конструктор по умолчанию
        this->head   = nullptr;
        this->tail   = nullptr;
        this->lenght = 0;
    }

    void push (int data_to_push); // функция для вставки в конец списка
    void pop (); // функция для удаления из начала списка
    int top (); // функция для получения первого элеента списка

    ListNode* getHead (); // функция для получения головы списка
    ListNode* getTail (); // функция для получения хвоста списка
};

void List::push (int data_to_push) {
    if (this->head == nullptr) { // если список был пустым
        ListNode* new_node = new ListNode{ data_to_push,
            nullptr }; // создаем новый узел, коорый никуда не указывает
        this->head = new_node; // голова и хвост будут один и тем же элементом, ведь он всего один
        this->tail   = new_node;
        this->lenght = 1; // длина списка станет 1
    } else {
        ListNode* new_node = new ListNode{ data_to_push, nullptr }; // создаем новый узел

        if (this->head == this->tail) // если до этого голова была равна хвосту
            this->head->next = new_node; // теперь голова укзывает на новую вершину

        this->tail->next = new_node;
        this->tail = new_node; // обновляем значение хвоста

        this->lenght++; // увеличиваем длину на 1
    }
}

void List::pop () {
    if (this->lenght <= 0) // если длина списка была меньше 1 то удалять нечего
        return;

    if (this->lenght == 1) { // если длина списка 1
        delete this->head; // удаляем голову, ставим голову и хвост нулями
        this->head   = nullptr;
        this->tail   = nullptr;
        this->lenght = 0; // длина тоже ноль
        return;           // выходим
    }

    ListNode* now = this->head; // создаем указатель на головную вершину
    ListNode* next = this->head->next; // создаем указатель на следующую вершину

    this->head = next; // делаем голову на вершину дальше

    this->lenght--; // убавляем длину на 1

    delete now; // удаляем начальную вершину
}

ListNode* List::getHead () { // ну тут я думаю все очевидно
    return this->head;
}

ListNode* List::getTail () { // тут тоже
    return this->tail;
}

int List::top () {
    return this->getHead ()->data;
}

// а теперь перейдем к самой очереди

class Queue {
    // private:
    public:
    List storage; // хранилище элементов

    // public:
    void push_back (int data_to_push); // функция для добавления элементов в конец
    int get_top (); // функция дл получения первого элемента
    void pop_first (); // функция для того чтобы стереть первый элемент
};

void Queue::push_back (int data_to_push) {
    this->storage.push (data_to_push);
}

int Queue::get_top () {
    return this->storage.top ();
}

void Queue::pop_first () {
    this->storage.pop ();
}


int main () { // функция для проверки
    Queue q;  // создадим очередь

    q.push_back (1); // запихнем туда несколько элементов
    q.push_back (2);
    q.push_back (3);
    q.push_back (4);


    std::cout << q.get_top () << std::endl; // посмотрим какой элемент первый

    q.pop_first (); // выкинем один элемент
    std::cout << q.get_top () << std::endl; // снова посмотрим какой элемент первый

    // и так несколько раз, пока элементы в очереди не закончатся

    q.pop_first ();
    std::cout << q.get_top () << std::endl;

    q.pop_first ();
    std::cout << q.get_top () << std::endl;

    q.pop_first ();


    return 0;
}