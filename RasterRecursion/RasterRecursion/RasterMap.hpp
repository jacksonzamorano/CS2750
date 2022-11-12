#ifndef RasterMap_hpp
#define RasterMap_hpp

#include <vector>
#include <stdio.h>
#include <string>
#include "RasterMapPoint.hpp"

using namespace std;

struct RasterMapData {
    char input_value = '0';
    string output_value = " 0 ";
    bool is_seen = false;
};

class RasterMap {
private:
    int rows;
    int columns;
    vector<vector<RasterMapData*>*>* data;
public:
    string output();
    int get_rows() { return rows; }
    int get_columns() { return columns; }
    void create(int rows, int columns);
    
    RasterMapData get(int r, int c) {
        return *(data->at(r)->at(c));
    }
    
    RasterMapData* get_ref(int r, int c) {
        return data->at(r)->at(c);
    }
    RasterMapData* get_ref(RasterMapPoint rp) { return get_ref(rp.x, rp.y); }
    RasterMapData get(RasterMapPoint rp) { return get(rp.x, rp.y); }
    void set_input_value(int r, int c, char d) {
        data->at(r)->at(c)->input_value = d;
    }
    void set_output_value(int r, int c, string d) {
        data->at(r)->at(c)->output_value = d;
    }
    void set_input_value(RasterMapPoint rp, char d) { return set_input_value(rp.x, rp.y, d); }
    void set_output_value(RasterMapPoint rp, string d) { return set_output_value(rp.x, rp.y, d); }
    void set_seen(RasterMapPoint rp) { data->at(rp.x)->at(rp.y)->is_seen = true; }
    
    void each(function<void (const int&, const int&, const RasterMapData*)> h);
};
#endif /* RasterMap_hpp */
