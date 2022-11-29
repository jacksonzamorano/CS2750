#ifndef BinaryNode_hpp
#define BinaryNode_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class BinaryNode {
private:
    string key;
    vector<int>* verse_numbers = new vector<int>();
    BinaryNode* left_child = nullptr;
    BinaryNode* right_child = nullptr;
public:
    BinaryNode(string key) { this->key = key; };
    string word() { return key; }
    BinaryNode* left() { return left_child; }
    BinaryNode* right() { return right_child; }
    void set_left(BinaryNode* n) { left_child = n; }
    void set_right(BinaryNode* n) { right_child = n; }
    vector<int>* verses() { return verse_numbers; }
};

#endif
