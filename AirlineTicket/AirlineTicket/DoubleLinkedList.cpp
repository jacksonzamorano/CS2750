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
            if (current->prev != nullptr) {
                DoubleLinkedNode<T>* back = current->prev;
                // Swap the 2 main node's pointers
                current->prev = back->prev;
                if (back->prev == nullptr) { head = current; }
                else { back->prev->next = current; }
                
                back->prev = current;
                back->next = current->next;
                current->next = back;
                if (back->next != nullptr) { back->next->prev = back; }
            }
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

template <class T> void DoubleLinkedList<T>::each(function<void (const T&)> fn) {
    DoubleLinkedNode<T>* current = head;
    while (current != nullptr) {
        fn(*current->data);
        current = current->next;
    }
}
