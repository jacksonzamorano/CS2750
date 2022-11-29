#include "BinaryTree.hpp"
#include <iostream>
#include <vector>
#include <queue>

BinaryNode* BinaryTree::node(string key) {
    BinaryNode* last = nullptr;
    BinaryNode* ptr = this->root;
    while (ptr != nullptr) {
        if (key < ptr->word()) {
            last = ptr;
            ptr = ptr->left();
        } else if (key > ptr->word()) {
            last = ptr;
            ptr = ptr->right();
        } else if (key == ptr->word()) {
            break;
        }
    }
    if (ptr == nullptr && last == nullptr) {
        // Insert first node
        ptr = new BinaryNode(key);
        root = ptr;
    } else if (ptr == nullptr && last->word() > key) {
        // Insert new node as left child
        ptr = new BinaryNode(key);
        last->set_left(ptr);
    } else if (ptr == nullptr && last->word() < key) {
        // Insert new node as right child
        ptr = new BinaryNode(key);
        last->set_right(ptr);
    }
    return ptr;
}

vector<BinaryNode*>* BinaryTree::linearize() {
    vector<BinaryNode*>* data = new vector<BinaryNode*>();
    queue<BinaryNode*>* work_queue = new queue<BinaryNode*>();
    
    BinaryNode* current_worker = this->root;
    while (current_worker != nullptr) {
        data->push_back(current_worker);
        if (current_worker->left() != nullptr) { work_queue->push(current_worker->left()); }
        if (current_worker->right() != nullptr) { work_queue->push(current_worker->right()); }
        if (work_queue->empty()) {
            break;
        } else {
            current_worker = work_queue->front();
            work_queue->pop();
        }
    }
    
    return data;
}

string BinaryTree::string_description() {
    string output = "";
    vector<BinaryNode*>* linear = this->linearize();
    bool state_dirty = false;
    do {
        state_dirty = false;
        for (int i = 1; i < linear->size(); i++) {
            BinaryNode* prev = linear->at(i-1);
            BinaryNode* curr = linear->at(i);
            if (prev->verses()->size() < curr->verses()->size()) {
                swap(linear->at(i-1), linear->at(i));
                state_dirty = true;
            }
        }
    } while (state_dirty);
    
    for (int i = 0; i < linear->size(); i++) {
        BinaryNode* n = linear->at(i);
        output += n->word();
        output += ": ";
        for (int j = 0; j < n->verses()->size(); j++) {
            output += to_string(n->verses()->at(j));
            output += ", ";
        }
        output.pop_back();
        output.pop_back();
        output += '\n';
    }
    return output;
}
