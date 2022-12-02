#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        cout << "Usage: ./heap [INPUT_PATH]" << endl;
        return -1;
    }
    
    ifstream input;
    input.open(argv[1]);
    
    char current_char = '0';
    string current_string = "";
    vector<int> vec_nums = vector<int>();
    
    while (!input.eof()) {
        current_char = input.get();
        if (current_char != '\r' && current_char != '\n') {
            current_string += current_char;
        } else {
            vec_nums.push_back(stoi(current_string));
            current_string = "";
        }
    }
    vec_nums.push_back(stoi(current_string));
    current_string = "";
    
    int num_num = vec_nums.size();
    int* nums = new int[num_num];
    for (int i = 0; i < num_num; i++) {
        
    }
    
    return 0;
}
