#include <iostream>
#include <string>
#include <fstream>
#include "DelimiterNode.hpp"
#include "DelimiterStack.hpp"

// Helper functions to determine whether character opens
// a block.
bool is_regular_delimiter(char currentc) {
    return currentc == '{' || currentc == '[' || currentc == '(';
}
bool is_char_string_delimiter(char currentc) {
    return currentc == '\'' || currentc == '"';
}
bool is_comment_delimiter(char lastc, char currentc) {
    return (lastc == '/' && currentc == '*');
}
bool is_inline_comment_delimiter(char lastc, char currentc) {
    return (lastc == '/' && currentc == '/');
}
bool is_ending_delimiter(char lastc, char currentc) {
    return currentc == '}'
        || currentc == ']'
        || currentc == ')';
}
bool delimiter_ends(char lastc, char currentc, string match) {
    // Maps each opening delimiter to it's end
    // This only applies for delimiters with different starts
    // and ends.
    if (currentc == '}') { return match == "{"; }
    else if (currentc == ')') { return match == "("; }
    else if (currentc == ']') { return match == "["; }
    else { return false; }
}

int main(int argc, const char * argv[]) {
    // Setup and verify commmand line params
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
    
    // Create a stack for delimiters.
    DelimiterStack* delimiters = new DelimiterStack;
    
    // Open the provided file
    ifstream filestream = ifstream(filepath);
    if (!filestream.is_open()) {
        cout << "! Could not open the file :(" << endl;
        return 1;
    }
    cout << "\"" << endl;
    // Variables to keep track of current data in the loop.
    // last_c and current_c allow us to double-buffer
    // read characters.
    int line_count = 1;
    int char_count = 0;
    char last_c = 0;
    char current_c = 0;
    while (!filestream.eof()) {
        char_count += 1;
        last_c = current_c;
        current_c = filestream.get();
        string c_value = delimiters->read();
        // These are special cases where we won't be in strict
        // checking mode (in a comment, string, etc.)
        bool is_in_char_string_zone = c_value == "\"" || c_value == "'";
        bool is_in_inline_comment_zone = c_value == "//";
        bool is_in_large_comment_zone = c_value == "/*";
        if (is_in_char_string_zone) {
            // If string closes opened string/char
            if (is_char_string_delimiter(current_c)) {
                string dlmtr;
                dlmtr += current_c;
                // Make sure that the quotes are the same i.e., ' and '
                // should match but " and ' should not.
                if (dlmtr == c_value && last_c != '\\') {
                    delete delimiters->pop();
                }
            }
        } else if (is_in_inline_comment_zone) {
            // Close the inline comment on a new line
            if (current_c == '\n') { delete delimiters->pop(); }
        } else if (is_in_large_comment_zone) {
            // Close these comments on the correct ending x
            if (last_c == '*' && current_c == '/') { delete delimiters->pop(); }
        } else {
            if (is_regular_delimiter(current_c)) {
                string dlmtr;
                dlmtr += current_c;
                cout << "Line " << line_count << ": ";
                delimiters->push(dlmtr);
            } else if (is_comment_delimiter(last_c, current_c)) {
                string dlmtr;
                dlmtr += last_c;
                dlmtr += current_c;
                delimiters->push(dlmtr);
            } else if (is_inline_comment_delimiter(last_c, current_c)) {
                string dlmtr;
                dlmtr += last_c;
                dlmtr += current_c;
                delimiters->push(dlmtr);
            } else if (is_char_string_delimiter(current_c)) {
                string dlmtr;
                dlmtr += current_c;
                delimiters->push(dlmtr);
            } else if (is_ending_delimiter(last_c, current_c)) {
                if (delimiter_ends(last_c, current_c, delimiters->read())) {
                    cout << "Line " << line_count << ": ";
                    delete delimiters->pop();
                } else {
                    string dlmtr;
//                    if (last_c == '*' && current_c == '/') { dlmtr += last_c; }
                    dlmtr += current_c;
                    if (has_output_file) {
                        output_data += "Error at ";
                        output_data += to_string(line_count);
                        output_data += ":";
                        output_data += to_string(char_count);
                        output_data += ". Tried to close ";
                        output_data += dlmtr;
                        output_data += ", but this is not the correct delimiter to close. ";
                        output_data += "You should be closing a ";
                        output_data += c_value;
                        output_data += ".\n\n";
                    } else {
                        cout << "Error at " << line_count << ":" << char_count << ". Tried to close " << dlmtr << ", but this is not the correct delimiter to close. You should be closing a " << c_value << "." << endl;
                        return 3;
                    }
                }
            }
        }
        if (current_c == '\n') { line_count++; char_count = 0; }
    }
    if (delimiters->read() == "\\") { delete delimiters->pop(); }
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
    } else {
        if (has_output_file) {
            output_data += "Delimiter check passed with no errors.";
        } else {
            cout << "Delimiter check passed with no errors." << endl;
        }
    }
    
    if (has_output_file) {
        ofstream output(output_path, ofstream::trunc);
        output << output_data;
        output.close();
    }
    
    return 0;
}
