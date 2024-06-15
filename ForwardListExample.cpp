#include <iostream>

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

int main () {
    ForwardList list;

    list.ForwardListPushFront (1);
    list.ForwardListPushFront (2);

    for (ForwardListNode* i = list.getHead (); i != nullptr; i = i->next) {
        std::cout << i->data << std::endl;
    }

    list.ForwardListPopFront ();
    list.ForwardListPopFront ();


    return 0;
}