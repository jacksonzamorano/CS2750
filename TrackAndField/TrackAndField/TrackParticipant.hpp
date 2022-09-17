//
//  TrackParticipant.hpp
//  TrackAndField
//
//  Created by Jackson Zamorano on 9/15/22.
//
#include "EventParticipant.hpp"
#ifndef TrackParticipant_hpp
#define TrackParticipant_hpp
class TrackParticipant: EventParticipant {
    int seconds;
    
    void setSeconds(int x) {
        this->seconds = x;
    }
    
    EventParticipant inputFromCIN() override;
};
#include <stdio.h>

#endif /* TrackParticipant_hpp */
