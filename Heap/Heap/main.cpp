#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

void heapify_max(int* array, int len) {
    for (int i = 0; i < len; i++) {
        int j = i;
        while (j > 0 && array[j/2] < array[j]) {
            int j_c = array[j];
            int j_p = array[j/2];
            array[j] = j_p;
            array[j/2] = j_c;
            j = j/2;
        }
    }
}
void heapify_min(int* array, int len) {
    for (int i = 0; i < len; i++) {
        int j = i;
        while (j > 0 && array[j/2] > array[j]) {
            int j_c = array[j];
            int j_p = array[j/2];
            array[j] = j_p;
            array[j/2] = j_c;
            j = j/2;
        }
    }
}

void heap_sort(int* array, int len, int sort) {
    for (int i = len; i >= 2; i--) {
        int current_item = array[i - 1];
        int replaced_item = array[0];
        array[0] = current_item;
        array[i - 1] = replaced_item;
        if (sort == 0) {
            heapify_max(array, i - 1);
        } else {
            heapify_min(array, i - 1);
        }
    }
}

vector<int> get_input(ifstream &input) {
    char current_char = '0';
    string current_string = "";
    vector<int> input_vec = vector<int>();
    
    // Input char by char.
    while (!input.eof()) {
        current_char = input.get();
        if (current_char != '\r' && current_char != '\n') {
            // If not a new line, add current char to buffer.
            current_string += current_char;
        } else {
            // Add the new buffer as a number.
            if (current_string != "") {
                input_vec.push_back(stoi(current_string));
                current_string = "";
            }
        }
    }
    
    // In case the file does not end with a new line,
    // add the current buffer if it's not empty.
    if (current_string != "" && current_string != "\xff") {
        input_vec.push_back(stoi(current_string));
        current_string = "";
    }
    return input_vec;
}

int main(int argc, const char * argv[]) {
    // sort_direction 0 = desc, 1 = asc
    int sort_direction = 0;
    string output_path = "";
    
    // Error if no input path.
    if (argc < 2) {
        cout << "Usage: ./heap [INPUT_PATH] {OUTPUT_PATH} {sort: -a or -d} ({} is optional)" << endl;
        return -1;
    }
    // Parse any extra args.
    for (int i = 2; i < argc; i++) {
        string input_arg = argv[i];
        if (input_arg == "-d" || input_arg == "-a") {
            sort_direction = input_arg == "-d";
        } else {
            output_path = argv[i];
        }
    }
    
    // Open input file
    ifstream input;
    input.open(argv[1]);
    
    // Parse input
    vector<int> input_vec = get_input(input);
    int input_size = static_cast<int>(input_vec.size());
    
    // Convert input from vec to array
    int* data_arr = new int[input_size];
    for (int i = 0; i < input_size; i++) {
        data_arr[i] = input_vec[i];
    }
    
    // Start by converting to heap.
    if (sort_direction == 0) {
        heapify_max(data_arr, input_size);
    } else {
        heapify_min(data_arr, input_size);
    }
    // Continually sort.
    heap_sort(data_arr, input_size, sort_direction);
    
    // Build output.
    string output = "";
    for (int i = 0; i < input_size; i++) {
        output += to_string(data_arr[i]);
        output += ", ";
    }
    
    // Prepare output to write.
    output = output.substr(0, output.length() - 2);
    if (output_path != "") {
        ofstream o_f;
        o_f.open(output_path);
        o_f << output;
        o_f.close();
    } else {
        cout << output << endl;
    }
    
    return 0;
}
