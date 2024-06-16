#include <iostream>

struct BidirectionalListNode { // структура узла
    int data; // данные, могут быть любого типа. в качестве примера выбран int
    BidirectionalListNode* prev; // указатель на предыдущую вершину
    BidirectionalListNode* next; // указатель на следующий узел
};

class BidirectionalList { // класс списка
    private:
    BidirectionalListNode* head; // голова списка
    BidirectionalListNode* tail; // хвост списка
    size_t lenght;               // длина списка

    public:
    BidirectionalList () { // конструктор по умолчанию
        this->head   = nullptr;
        this->tail   = nullptr;
        this->lenght = 0;
    }

    void push (int data_to_push); // функция для вставки в конец списка
    void pop (); // функция для удаления из конца списка
    void pop_front (); // функция для удаления из начал списка

    BidirectionalListNode* getHead (); // функция для получения головы списка
    BidirectionalListNode* getTail (); // функция для получения хвоста списка
};

void BidirectionalList::push (int data_to_push) {
    if (this->head == nullptr) { // если список был пустым
        BidirectionalListNode* new_node = new BidirectionalListNode{ data_to_push,
            nullptr, nullptr }; // создаем новый узел, коорый никуда не указывает
        this->head = new_node; // голова и хвост будут один и тем же элементом, ведь он всего один
        this->tail   = new_node;
        this->lenght = 1; // длина списка станет 1
    } else {
        BidirectionalListNode* new_node = new BidirectionalListNode{ data_to_push,
            this->tail, nullptr }; // создаем новый узел

        if (this->head == this->tail) // если до этого голова была равна хвосту
            this->head->next = new_node; // теперь голова укзывает на новую вершину

        this->tail->next = new_node; // теперь последняя вершина указывает на новую
        this->tail = new_node; // делаем новую вершину последней

        this->lenght++; // увеличиваем длину на 1
    }
}

void BidirectionalList::pop () {
    if (this->lenght <= 0) // если длина списка была меньше 1 то удалять нечего
        return;

    if (this->lenght == 1) { // если длина списка 1
        delete this->head; // удаляем голову, ставим голову и хвост нулями
        this->head   = nullptr;
        this->tail   = nullptr;
        this->lenght = 0; // длина тоже ноль
        return;           // выходим
    }


    BidirectionalListNode* new_tail =
    this->tail->prev; // определяем вершину которая будет новым хвостом
    new_tail->next = nullptr; // теперь предпоследняя вершина не связана с последней

    delete this->tail; // удаляем предыдущую хвостовую вершину
    this->tail = new_tail; // обновляем хвостовую вершину

    this->lenght--; // убавляем длину на 1
}

void BidirectionalList::pop_front () {
    if (this->lenght <= 0) // если длина меньше 1 то выходим
        return;

    if (this->lenght == 1) {  // если длина 1
        delete this->head;    // удаляем голову
        this->head = nullptr; // ставим голову и хвост в нули, потому что вершин больше нет
        this->tail   = nullptr;
        this->lenght = 0; // теперь длина 0
        return;           // выходим
    }

    BidirectionalListNode* new_head =
    this->head->next; // узнаем вершину которая будет новой головой
    new_head->prev = nullptr; // теперь новая и старая голова не связаны

    delete this->head;     // удаляем старую голову
    this->head = new_head; // обновляем значение головы

    this->lenght--; // уменьшаем длину на 1
}


BidirectionalListNode* BidirectionalList::getHead () { // ну тут я думаю все очевидно
    return this->head;
}

BidirectionalListNode* BidirectionalList::getTail () { // тут тоже
    return this->tail;
}


int main () {               // функция для проверки
    BidirectionalList list; // создаем список

    list.push (1); // пихаем элементы
    list.push (2);
    list.push (3);

    for (BidirectionalListNode* i = list.getHead (); i != nullptr; i = i->next) { // проходимся по всем жлементам и выводим
        std::cout << i->data << std::endl;
    }

    list.pop (); // удаляем последнй элемент

    // проделываем это все несколько раз для проверки

    for (BidirectionalListNode* i = list.getHead (); i != nullptr; i = i->next) {
        std::cout << i->data << std::endl;
    }

    list.pop ();

    for (BidirectionalListNode* i = list.getHead (); i != nullptr; i = i->next) {
        std::cout << i->data << std::endl;
    }

    list.pop ();

    for (BidirectionalListNode* i = list.getHead (); i != nullptr; i = i->next) {
        std::cout << i->data << std::endl;
    }

    return 0;
}