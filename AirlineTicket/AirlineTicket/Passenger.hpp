//
//  Passenger.hpp
//  AirlineTicket
//
//  Created by Jackson Zamorano on 10/4/22.
//

#ifndef Passenger_hpp
#define Passenger_hpp

#include <stdio.h>
#include <string>
using namespace std;
class Passenger {
public:
    string name;
    
    Passenger(string n) {
        name = n;
    }
};
#endif /* Passenger_hpp */
