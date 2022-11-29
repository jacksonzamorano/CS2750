#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <stdio.h>
#include <vector>
#include "BinaryNode.hpp"

class BinaryTree {
private:
    BinaryNode* root = nullptr;
    vector<BinaryNode*>* linearize();
public:
    BinaryNode* node(string key);
    string string_description();
};

#endif
