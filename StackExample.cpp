#include <iostream>

/*
    я буду делать стек через список, поэтому оставлю его исходники тут, но уже без комметариев.
*/

struct ForwardListNode {
    int data;
    ForwardListNode* next;
};

class ForwardList {
    private:
    ForwardListNode* head;
    ForwardListNode* tail;
    size_t lenght;

    public:
    ForwardList () {
        this->head   = nullptr;
        this->tail   = nullptr;
        this->lenght = 0;
    }

    void ForwardListPushFront (int data_to_push);
    void ForwardListPopFront ();

    ForwardListNode* getHead ();
    ForwardListNode* getTail ();
};

//-----------------

class Stack { // класс для стека
    public:
    ForwardList storage; // список в котором будем хранить все элементы

    void push (int data_to_push); // функция для вставки элемента в конец
    int top (); // функция которая возвращает текущее значение последнего элемента стека
    void pop (); // функция для удаления последнего элемента стека
};

/*
    функции в принципе очевидны, труднее сделать стек на массиве
*/

void Stack::push (int data_to_push) {
    this->storage.ForwardListPushFront (data_to_push);
}

int Stack::top () {
    return this->storage.getTail ()->data;
}

void Stack::pop () {
    this->storage.ForwardListPopFront ();
}


int main () {    // функция для проверк  стека
    Stack stack; // создадим стек, запихнем пару элементов и проверим

    stack.push (1);

    std::cout << stack.top () << std::endl;

    stack.push (2);

    std::cout << stack.top () << std::endl;

    stack.pop ();
    stack.pop ();


    return 0;
}

//---------------
// еще исходники для списка


void ForwardList::ForwardListPushFront (int data_to_push) {
    if (this->head == nullptr) {
        ForwardListNode* new_node = new ForwardListNode{ data_to_push, nullptr };
        this->head   = new_node;
        this->tail   = new_node;
        this->lenght = 1;
    } else {
        ForwardListNode* new_node = new ForwardListNode{ data_to_push, nullptr };

        if (this->head == this->tail)
            this->head->next = new_node;

        this->tail = new_node;

        this->lenght++;
    }
}

void ForwardList::ForwardListPopFront () {
    if (this->lenght <= 0)
        return;

    if (this->lenght == 1) {
        delete this->head;
        this->head   = nullptr;
        this->tail   = nullptr;
        this->lenght = 0;
        return;
    }

    ForwardListNode* now  = this->head;
    ForwardListNode* next = this->head->next;

    while (next != this->tail) {
        now  = now->next;
        next = next->next;
    }

    now->next  = nullptr;
    this->tail = now;

    this->lenght--;

    delete next;
}

ForwardListNode* ForwardList::getHead () {
    return this->head;
}

ForwardListNode* ForwardList::getTail () {
    return this->tail;
}