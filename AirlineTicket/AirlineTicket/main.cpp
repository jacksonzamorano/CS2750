#include <iostream>
#include <string>
#include "Ticket.hpp"
#include "DoubleLinkedList.hpp"
#include "DoubleLinkedList.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    DoubleLinkedList<string>* list = new DoubleLinkedList<string>;
    
    list->insertHead(new string("Test 6"));
    list->insertHead(new string("Test 5"));
    list->insertHead(new string("Txest 4"));
    list->insertHead(new string("Test 3"));
    list->insertHead(new string("Test 2"));
    list->insertHead(new string("Test 1"));

    list->each([] (const string& s) {
        cout << s << endl;
    });
    list->valueWhere([] (const string& s) {
        return s == "Test 5";
    });
    cout << "---" << endl;
    return 0;
}
