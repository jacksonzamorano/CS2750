#include <iostream>
#include <string>
#include "EventParticipant.hpp"
#include "FieldParticipant.hpp"
#include "TrackParticipant.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    cout << "Welcome! Type 1 for field event, 2 for track event, or 3 for driver." << endl;
    char input;
    cin >> input;
    if (input == '1' || input == '2') {
        EventParticipant* participants = new EventParticipant[10];
        
        
    } else if (input == '3') {
        // TODO: Driver function
    }
    
    return 0;
}
