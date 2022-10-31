#ifndef RasterMap_hpp
#define RasterMap_hpp

#include <vector>
#include <stdio.h>
#include "RasterMapPoint.hpp"

using namespace std;

struct RasterMapData {
    char value = '0';
    bool is_seen = false;
};

class RasterMap {
private:
    int rows;
    int columns;
    vector<vector<RasterMapData>*>* data;
  
public:
    void output();
    int get_rows() { return rows; }
    int get_columns() { return columns; }
    void create(int rows, int columns);
    
    RasterMapData get(int r, int c) {
        return data->at(r)->at(c);
    }
    RasterMapData get(RasterMapPoint rp) { return get(rp.x, rp.y); }
    void set_value(int r, int c, char d) {
        data->at(r)->at(c).value = d;
    }
    void set_value(RasterMapPoint rp, char d) { return set_value(rp.x, rp.y, d); }
    void set_seen(RasterMapPoint rp) { data->at(rp.x)->at(rp.y).is_seen = true; }
    
    void each(function<void (const int&, const int&, const RasterMapData&)> h);
};
#endif /* RasterMap_hpp */
