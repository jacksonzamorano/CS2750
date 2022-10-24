#include <iostream>
#include <string>
#include <fstream>
#include "DelimiterNode.hpp"
#include "DelimiterStack.hpp"

bool is_regular_delimiter(char currentc) {
    return currentc == '{' || currentc == '[' || currentc == '(';
}
bool is_comment_delimiter(char lastc, char currentc) {
    return (lastc == '/' && currentc == '*');
}
bool is_ending_delimiter(char lastc, char currentc) {
    return currentc == '}' || currentc == ']' || currentc == ')' || (lastc == '*' && currentc == '/');
}
bool delimiter_ends(char lastc, char currentc, string match) {
    if (lastc == '*' && currentc == '/') {
        // ending a comment
        return match == "/*";
    } else if (currentc == '}') { return match == "{"; }
    else if (currentc == ')') { return match == "("; }
    else if (currentc == ']') { return match == "["; }
    else { return false; }
}

int main(int argc, const char * argv[]) {
    string output_data;
    string output_path;
    bool has_output_file = false;
    if (argc == 3) {
        has_output_file = true;
        output_path = argv[2];
    } else if (argc != 2) {
        cout << "Usage: ./DelimiterMatching {input_file} {output_file (optional)}" << endl;
        return -2;
    }
    string filepath = argv[1];
    cout << "Checking " << filepath << endl;
    DelimiterStack* delimiters = new DelimiterStack;
    
    ifstream filestream = ifstream(filepath);
    if (!filestream.is_open()) {
        cout << "! Could not open the file :(" << endl;
        return 1;
    }
    int line_count = 1;
    int char_count = 0;
    char last_c = 0;
    char current_c = 0;
    while (!filestream.eof()) {
        char_count += 1;
        last_c = current_c;
        current_c = filestream.get();
        if (is_regular_delimiter(current_c)) {
            string dlmtr;
            dlmtr += current_c;
            delimiters->push(dlmtr);
        } else if (is_comment_delimiter(last_c, current_c)) {
            string dlmtr;
            dlmtr += last_c;
            dlmtr += current_c;
            delimiters->push(dlmtr);
        } else if (is_ending_delimiter(last_c, current_c)) {
            if (delimiter_ends(last_c, current_c, delimiters->read())) {
                delete delimiters->pop();
            } else {
                string dlmtr;
                if (last_c == '*' && current_c == '/') { dlmtr += last_c; }
                dlmtr += current_c;
                if (has_output_file) {
                    output_data += "Error at ";
                    output_data += to_string(line_count);
                    output_data += ":";
                    output_data += to_string(char_count);
                    output_data += ". Tried to close ";
                    output_data += dlmtr;
                    output_data += ", but this is not the correct delimiter to close.\n\n";
                } else {
                    cout << "Error at " << line_count << ":" << char_count << ". Tried to close " << dlmtr << ", but this is not the correct delimiter to close." << endl;
                    return 3;
                }
            }
        }
        if (current_c == '\n') { line_count++; char_count = 0;}
    }
    if (delimiters->getCount() > 0) {
        if (has_output_file) {
            output_data += "Error: ";
            output_data += "The delimiter ";
            output_data += delimiters->pop()->getDelimiter();
            output_data += "was never closed.\n\n";
        } else {
            cout << "Error: The delimiter " << delimiters->pop()->getDelimiter() << " was never closed." << endl;
            return 4;
        }
    }
    
    if (has_output_file) {
        ofstream output(output_path, ofstream::trunc);
        output << output_data;
        output.close();
    }
    
    return 0;
}
