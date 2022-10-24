#ifndef DelimiterStack_hpp
#define DelimiterStack_hpp

#include <stdio.h>
#include "DelimiterNode.hpp"
#include <string>
#include <iostream>

using namespace std;

class DelimiterStack {
private:
    DelimiterNode* top;
    int count = 0;
public:
    int getCount();
    string read();
    DelimiterNode* pop();
    void push(string s);
    
    
    void _debug_output() {
        DelimiterNode* n = top;
        while (n != nullptr) {
            cout << n->getDelimiter() << endl;
            n = n->getNext();
        }
    }
};

#endif /* DelimiterStack_hpp */
