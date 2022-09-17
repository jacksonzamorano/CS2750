//
//  FieldParticipant.hpp
//  TrackAndField
//
//  Created by Jackson Zamorano on 9/15/22.
//
#include "EventParticipant.hpp"

#ifndef FieldParticipant_hpp
#define FieldParticipant_hpp

class FieldParticipant: public EventParticipant {
    int distance;
    
public:
    void setDistance(int x) {
        this->distance = x;
    }
    static FieldParticipant* createFromInput();
    static FieldParticipant* createDriverData(int driverIndex);
    static void sortForScoring(FieldParticipant** array, int size);
    static void sortArrayInteractive(FieldParticipant** array, int size);
    string confirmationString() override;
    void output() override;
    void outputHeader() override;
};

#include <stdio.h>

#endif /* FieldParticipant_hpp */
