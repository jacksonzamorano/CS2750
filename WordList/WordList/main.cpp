#include <iostream>
#include <fstream>
#include "BinaryNode.hpp"
#include "BinaryTree.hpp"

using namespace std;

bool is_num(string test) {
    bool valid = true;
    // If the string is empty, return false.
    if (test.length() == 0) { return false; }
    
    // Read in the test string char by char and check each
    // to see if it's a digit.
    for (int i = 0; i < test.length(); i++) {
        char t = test[i];
        if (t != '1' &&
            t != '2' &&
            t != '3' &&
            t != '4' &&
            t != '5' &&
            t != '6' &&
            t != '7' &&
            t != '8' &&
            t != '9' &&
            t != '0') {
            // Not a number
            valid = false;
        }
    }
    return valid;
}

int main(int argc, const char * argv[]) {
    BinaryTree* tree = new BinaryTree();
    
    string output_file_path = "";
    bool has_output_file = false;
    
    if (argc == 1) {
        // Input file not provided
        cout << "Error: Usage requires an input file." << endl;
        return -1;
    }
    if (argc > 2) {
        // Capture output file data
        has_output_file = true;
        output_file_path = argv[2];
    }
    
    // Read and open the file.
    ifstream file_input;
    file_input.open(argv[1]);
    
    int temp_verse = -1;
    string temp_word;
    char temp_char;
    while (!file_input.eof()) {
        // Read in the next character
        temp_char = file_input.get();
        
        // If it's not a space, keep working to get the full "word"
        // (pun intended)
        //
        // We will also filter out similar words, such as God and God's
        // This first if ignores the characters in its condition.
        if (temp_char == '\'' ||
            temp_char == '.' ||
            temp_char == '"' ||
            temp_char == ',' ||
            temp_char == '?' ||
            temp_char == '(' ||
            temp_char == ')' ||
            temp_char == '\t' ||
            temp_char == '\r' ||
            temp_char == '\'') {
            continue;
        } else if (
           temp_char != ' ' &&
           temp_char != '\n'
        ) {
           // This second block uses the space character
           // or new line to indicate a new word
           temp_word += toupper(temp_char);
           continue;
       } else if (temp_char == '\'') {
           // If we have God's, once we reach the ',
           // skip until the new word.
           while (file_input.get() != ' ') { }
       }
        
        // Ok so now we have a word, let's process it.
        if (is_num(temp_word)) {
            // This is a verse number.
            temp_verse = stoi(temp_word);
        } else {
            // This is a word.
            tree->node(temp_word)->verses()->push_back(temp_verse);
        }
        
        // Reset back to original state.
        temp_word = "";
    }
    
    if (has_output_file) {
        ofstream stream;
        stream.open(output_file_path);
        stream << tree->string_description();
        stream.close();
    } else {
        cout << tree->string_description();
    }
    
    return 0;
}
