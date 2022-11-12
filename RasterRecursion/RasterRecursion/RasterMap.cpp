#include "RasterMap.hpp"
#include <iostream>

using namespace std;

void RasterMap::create(int r_c, int c_c) {
    rows = r_c;
    columns = c_c;
    data = new vector<vector<RasterMapData*>*>;
    for (int i = 0; i < rows; i++) {
        data->push_back(new vector<RasterMapData*>());
        for (int j = 0; j < columns; j++) {
            RasterMapData* v = new RasterMapData;
            data->at(i)->push_back(v);
        }
    }
}

string RasterMap::output() {
    string output = "";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            output += data->at(i)->at(j)->output_value;
            output += " ";
        }
        output += "\n";
    }
    return output;
}

void RasterMap::each(function<void (const int &, const int &, const RasterMapData* )> h) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            h(i, j, get_ref(i, j));
        }
    }
}
