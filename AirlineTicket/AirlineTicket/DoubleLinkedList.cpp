#include "DoubleLinkedList.hpp"
#include <iostream>
using namespace std;

template <class T> void DoubleLinkedList<T>::insertHead(T* item) {
    DoubleLinkedNode<T>* node = new DoubleLinkedNode<T>;
    node->data = item;
    node->prev = nullptr;
    if (head != nullptr) {
        node->next = head;
        node->next->prev = node;
    } else {
        node->next = nullptr;
    }
    head = node;
}
template <class T> DoubleLinkedNode<T>* DoubleLinkedList<T>::getHead() { return head; }

template <class T> T* DoubleLinkedList<T>::valueWhere(function<bool (const T&)> fn) {
    DoubleLinkedNode<T>* current = head;
    while (current != nullptr) {
        if (fn(*current->data)) {
            break;
        }
        current = current->next;
    }
    if (current == nullptr) {
        return nullptr;
    } else {
        return current->data;
    }
}
template <class T> int DoubleLinkedList<T>::indexWhere(function<bool (const T&)> fn) {
    DoubleLinkedNode<T>* current = head;
    int index = 0;
    while (current != nullptr) {
        if (fn(*current->data)) {
            break;
        }
        current = current->next;
        index++;
    }
    if (current == nullptr) {
        return -1;
    } else {
        return index;
    }
}
template <class T> void DoubleLinkedList<T>::deleteWhere(function<bool (const T&)> fn) {
    DoubleLinkedNode<T>* current = head;
    int index = 0;
    while (current != nullptr) {
        if (fn(*current->data)) {
            break;
        }
        current = current->next;
        index++;
    }
    if (current != nullptr) {
        if (current->prev != nullptr && current->next != nullptr) {
            // This is easy, we just hook up the nodes together
            current->prev->next = current->next;
            current->next->prev = current->prev;
        } else if (current->prev == nullptr) {
            // Current is at head
            head = current->next;
            head->prev = nullptr;
        } else if (current->next == nullptr) {
            // Current is at tail; simply truncate the list
            current->prev->next = nullptr;
        } else if (current->prev == nullptr && current->next == nullptr) {
            // Node is only element
            head = nullptr;
        }
    
        delete current->data;
        delete current;
    }
}
template <class T> void DoubleLinkedList<T>::deleteIndex(int index) {
    DoubleLinkedNode<T>* current = head;
    int i = 0;
    while (current != nullptr) {
        if (index == 0) { break; }
        current = current->next;
        i++;
    }
    if (current != nullptr) {
        if (current->prev != nullptr && current->next != nullptr) {
            // This is easy, we just hook up the nodes together
            current->prev->next = current->next;
            current->next->prev = current->prev;
        } else if (current->prev == nullptr) {
            // Current is at head
            head = current->next;
            head->prev = nullptr;
        } else if (current->next == nullptr) {
            // Current is at tail; simply truncate the list
            current->prev->next = nullptr;
        } else if (current->prev == nullptr && current->next == nullptr) {
            // Node is only element
            head = nullptr;
        }
    
        delete current->data;
        delete current;
    }
}

template <class T> void DoubleLinkedList<T>::each(function<void (const T&)> fn) {
    DoubleLinkedNode<T>* current = head;
    while (current != nullptr) {
        fn(*current->data);
        current = current->next;
    }
}

template <class T> void DoubleLinkedList<T>::swapIndicies(DoubleLinkedNode<T>* a, DoubleLinkedNode<T>* b) {
    b->prev = a->prev;
    if (a->prev == nullptr) { head = b; }
    else { a->prev->next = b; }

    a->prev = b;
    a->next = b->next;
    b->next = a;
    if (a->next != nullptr) { a->next->prev = a; }
}

template <class T> void DoubleLinkedList<T>::sort(function<bool (const T&, const T&)> fn) {
    bool workDone = false;
    do {
        workDone = false;
        DoubleLinkedNode<T>* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (!fn(*current->data, *current->next->data)) {
                swapIndicies(current, current->next);
                workDone = true;
            }
            current = current->next;
        }
    } while (workDone);
    
}
