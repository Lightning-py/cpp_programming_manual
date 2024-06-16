#include <iostream>

struct ForwardListNode { // структура узла
    int data; // данные, могут быть любого типа. в качестве примера выбран int
    ForwardListNode* next; // указатель на следующий узел
};

class ForwardList { // класс списка
    private:
    ForwardListNode* head; // голова списка
    ForwardListNode* tail; // хвост списка
    size_t lenght;         // длина списка

    public:
    ForwardList () { // конструктор по умолчанию
        this->head   = nullptr;
        this->tail   = nullptr;
        this->lenght = 0;
    }

    void push (int data_to_push); // функция для вставки в конец списка
    void pop (); // функция для удаления из конца списка

    ForwardListNode* getHead (); // функция для получения головы списка
    ForwardListNode* getTail (); // функция для получения хвоста списка
};

void ForwardList::push (int data_to_push) {
    if (this->head == nullptr) { // если список был пустым
        ForwardListNode* new_node = new ForwardListNode{ data_to_push, nullptr }; // создаем новый узел, коорый никуда не указывает
        this->head = new_node; // голова и хвост будут один и тем же элементом, ведь он всего один
        this->tail   = new_node;
        this->lenght = 1; // длина списка станет 1
    } else {
        ForwardListNode* new_node = new ForwardListNode{ data_to_push, nullptr }; // создаем новый узел

        if (this->head == this->tail) // если до этого голова была равна хвосту
            this->head->next = new_node; // теперь голова укзывает на новую вершину

        this->tail->next = new_node; // теперь последняя вершина указывает на новую
        this->tail = new_node; // делаем новую вершину последней

        this->lenght++; // увеличиваем длину на 1
    }
}

void ForwardList::pop () {
    if (this->lenght <= 0) // если длина списка была меньше 1 то удалять нечего
        return;

    if (this->lenght == 1) { // если длина списка 1
        delete this->head; // удаляем голову, ставим голову и хвост нулями
        this->head   = nullptr;
        this->tail   = nullptr;
        this->lenght = 0; // длина тоже ноль
        return;           // выходим
    }

    ForwardListNode* now = this->head; // создаем указатель на головную вершину
    ForwardListNode* next = this->head->next; // создаем указатель на следующую вершину

    // замысел в том, чтобы найти предпоследний элемент и положить его в now
    while (next != this->tail) { // до тех пор пока next не станет хвостом передвигаем обе переменные на одну вершину вперед
        now  = now->next;
        next = next->next;
    }

    now->next = nullptr; // теперь now последний элемент, а значит хвостовой
    this->tail = now;

    this->lenght--; // убавляем длину на 1

    delete next; // удаляем предыдущую хвостовую вершину
}

ForwardListNode* ForwardList::getHead () { // ну тут я думаю все очевидно
    return this->head;
}

ForwardListNode* ForwardList::getTail () { // тут тоже
    return this->tail;
}

int main () { // функция для проверки работы списка
    ForwardList list; // создаем список

    list.push (1); // пихаем два элемента
    list.push (2);
    list.push (3);

    for (ForwardListNode* i = list.getHead (); i != nullptr; i = i->next) { // проходимся по списку и выводим элементы
        std::cout << i->data << std::endl;
    }

    list.pop (); // удаляем два элемента
    list.pop ();
    list.pop ();

    return 0;
}