#ifndef DelimiterNode_hpp
#define DelimiterNode_hpp

#include <stdio.h>
#include <string>

using namespace std;

class DelimiterNode {
private:
    string delimiter;
    DelimiterNode* next;
public:
    string getDelimiter() { return delimiter; }
    void setDelimiter(string d) { delimiter = d; }
    DelimiterNode* getNext() { return next; }
    void setNext(DelimiterNode* n) { next = n; }
};

#endif
