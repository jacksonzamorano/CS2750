#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "RasterMap.hpp"
#include "RasterMapPoint.hpp"

using namespace std;

const char K_MATCH_SQUARE = 't';

string format_number(int& i) {
    string output_string;
    if (i < 10) {
        // Number is a digit long, center it
        output_string += " ";
        output_string += to_string(i);
        output_string += " ";
    } else if (i < 100) {
        output_string += " ";
        output_string += to_string(i);
    } else {
        output_string += to_string(i);
    }
    return output_string;
}

void add_output_data(string& output, string lbl, string data) {
    output += lbl;
    output += ": ";
    output += data;
}

void get_size_data(ifstream& file_stream, int& rc, int& cc) {
    char current_c = file_stream.get();
    char seek_mode = 0;
    string current_data;
    while (current_c != '\n') {
        if (current_c == 'r' || current_c == 'c') {
            seek_mode = current_c;
        } else if (current_c == ',') {
            if (seek_mode == 'r') { rc = stoi(current_data); }
            else if (seek_mode == 'c') { cc = stoi(current_data); }
            current_data = "";
        } else if (current_c != '=') {
            current_data += current_c;
        }
        current_c = file_stream.get();
    }
    if (seek_mode == 'r') { rc = stoi(current_data); }
    else if (seek_mode == 'c') { cc = stoi(current_data); }
}

void spread_data(RasterMap* rm, RasterMapPoint& rp, vector<RasterMapPoint>* rmps) {
    int min_x = 0;
    int max_x = rm->get_rows() - 1;
    int min_y = 0;
    int max_y = rm->get_columns() - 1;
    
    RasterMapData* cr = rm->get_ref(rp);
    if (!cr->is_seen && cr->input_value == K_MATCH_SQUARE) {
        rm->set_seen(rp);
        rmps->push_back(rp);
    } else {
        rm->set_seen(rp);
        return;
    }
    
    if (min_x < rp.x) {
        RasterMapPoint spread_point;
        spread_point.x = rp.x - 1;
        spread_point.y = rp.y;
        spread_data(rm, spread_point, rmps);
    }
    if (rp.x < max_x) {
        RasterMapPoint spread_point;
        spread_point.x = rp.x + 1;
        spread_point.y = rp.y;
        spread_data(rm, spread_point, rmps);
    }
    if (min_y < rp.y) {
        RasterMapPoint spread_point;
        spread_point.x = rp.x;
        spread_point.y = rp.y - 1;
        spread_data(rm, spread_point, rmps);
    }
    if (rp.y < max_y) {
        RasterMapPoint spread_point;
        spread_point.x = rp.x;
        spread_point.y = rp.y + 1;
        spread_data(rm, spread_point, rmps);
    }
}

void create_area_graph(RasterMap* rm, RasterMapPoint& rp, int& map_value_count) {
    vector<RasterMapPoint>* matched_points = new vector<RasterMapPoint>();
    spread_data(rm, rp, matched_points);
    
    unsigned long output_size = matched_points->size();
    for (int i = 0; i < output_size; i++) {
        RasterMapPoint rpd = matched_points->at(i);
        rm->set_output_value(rpd, format_number(map_value_count));
    }
    
    delete matched_points;
}

int main(int argc, const char * argv[]) {
    string output_data;
    string input_path;
    string output_path;
    bool output_to_file = false;
    
    if (argc == 2) {
        // Binary + input path
        input_path = argv[1];
    } else if (argc == 3) {
        input_path = argv[1];
        output_path = argv[2];
        output_to_file = true;
    } else {
        cout << "Invalid usage!" << endl;
        cout << "./RasterRecursion {input_path} {output_path (optional)}" << endl;
        return -1;
    }
    
    ifstream input_stream = ifstream(input_path);
    if (!input_stream) {
        cout << "Cannot open the path " << input_path << endl;
        return -2;
    }
    
    string file_header;
    
    int row_count = 0;
    int column_count = 0;
    RasterMap* input_map = new RasterMap;
    get_size_data(input_stream, row_count, column_count);
    input_map->create(row_count, column_count);
    int ri = 0;
    int ci = 0;
    char current_data;
    cout << "Input:" << endl;
    while (!input_stream.eof()) {
        current_data = input_stream.get();
        cout << current_data;
        if (current_data == '\n') {
            ri++;
            ci = 0;
        } else if (current_data != ' ' && current_data != '\r' && current_data != '\xff') {
            input_map->set_input_value(ri, ci, current_data);
            ci++;
        }
    }
        
    cout << endl << endl;
    int map_count = 0;
    input_map->each([&input_map, &map_count](int x, int y, const RasterMapData* d) {
        RasterMapPoint rp;
        rp.x = x;
        rp.y = y;
        if (d->input_value == K_MATCH_SQUARE && !d->is_seen) {
            map_count++;
            create_area_graph(input_map, rp, map_count);
        }
    });
    
    string result_output = input_map->output();
    if (output_to_file) {
        ofstream output_file_stream  = ofstream(output_path);
        output_file_stream << result_output << endl;
        output_file_stream.close();
    } else {
        cout << "Output:" << endl;
        cout << result_output;
    }
    
    return 0;
}
