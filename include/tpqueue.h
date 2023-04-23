// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
    struct Item {
        T data;
        Item* next;
        Item* last;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);

 public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

struct SYM {
    char ch;
    int prior;
};

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
    Item* item = new Item;
    item->data = data;
    item->next = nullptr;
    item->last = nullptr;
    return item;
}

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("TPQueue is empty!");
    } else {
        Item* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
void TPQueue<T>::print() const {
    Item* uk = head;
    while (uk) {
        std::cout << uk->data << " ";
        uk = uk->next;
    }
    std::cout << std::endl;
}

template <typename T>
void TPQueue<T>::push(const T& value) {
    if (head == nullptr) {
        head = create(value);
        tail = head;
    } else if (tail->data.prior >= value.prior) {
        if (tail->data.ch == value.ch) {
            tail->data = value;
        } else {
            tail->next = create(value);
            tail->next->last = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->last = create(value);
        head = tail->last;
        head->next = tail;
    } else {
        Item* tmp = tail;
        while (tmp != head && tmp->data.prior < value.prior) {
            tmp = tmp->last;
        }
        if (tmp->data.prior > value.prior) {
            Item* cell = new Item;
            cell->next = tmp->next;
            cell->last = tmp;
            cell->data = value;
            tmp->next->last = cell;
            tmp->next = cell;
        }
        if (tmp == head && tmp->data.prior < value.prior) {
            head->last = create(value);
            head = head->last;
            head->next = tmp;
        }
    }
}
#endif  // INCLUDE_TPQUEUE_H_
