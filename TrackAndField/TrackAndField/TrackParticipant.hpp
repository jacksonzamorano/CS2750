//
//  TrackParticipant.hpp
//  TrackAndField
//
//  Created by Jackson Zamorano on 9/15/22.
//
#include "EventParticipant.hpp"
#ifndef TrackParticipant_hpp
#define TrackParticipant_hpp
class TrackParticipant: public EventParticipant {
    float seconds;
    
public:
    void setSeconds(float x) {
        this->seconds = x;
    }
    
    static TrackParticipant* createFromInput();
    static TrackParticipant* createDriverData(int driverIndex);
    static void sortForScoring(TrackParticipant** array, int size);
    static void sortArrayInteractive(TrackParticipant** array, int size);
    string confirmationString();
    void output();
    void outputHeader();
};
#include <stdio.h>

#endif /* TrackParticipant_hpp */
