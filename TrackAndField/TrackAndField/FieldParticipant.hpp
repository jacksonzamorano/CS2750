//
//  FieldParticipant.hpp
//  TrackAndField
//
//  Created by Jackson Zamorano on 9/15/22.
//
#include "EventParticipant.hpp"

#ifndef FieldParticipant_hpp
#define FieldParticipant_hpp

class FieldParticipant: EventParticipant {
    int distance;
    
    void setDistance(int x) {
        this->distance = x;
    }
    
    EventParticipant inputFromCIN() override;
};

#include <stdio.h>

#endif /* FieldParticipant_hpp */
