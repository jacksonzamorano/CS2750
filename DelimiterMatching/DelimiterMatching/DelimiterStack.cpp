#include "DelimiterStack.hpp"
#include "DelimiterNode.hpp"
#include <string>
#include <iostream>

using namespace std;

string DelimiterStack::read()  {
    if (top != nullptr) {
        return top->getDelimiter();
    } else { return ""; }
}
int DelimiterStack::getCount() {
    return count;
}
DelimiterNode* DelimiterStack::pop()  {
    DelimiterNode* popped = top;
    top = top->getNext();
    count--;
    cout << "Popping " << popped->getDelimiter() << endl;
    return popped;
}
void DelimiterStack::push(string s)  {
    DelimiterNode* n = new DelimiterNode;
    n->setDelimiter(s);
    n->setNext(top);
    cout << "Pushing " << s << endl;
    top = n;
    count++;
}
