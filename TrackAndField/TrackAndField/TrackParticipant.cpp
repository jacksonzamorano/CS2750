//
//  TrackParticipant.cpp
//  TrackAndField
//
//  Created by Jackson Zamorano on 9/15/22.
//

#include "TrackParticipant.hpp"
EventParticipant TrackParticipant::inputFromCIN() {
    EventParticipant parent = EventParticipant::inputFromCIN();
    TrackParticipant p = TrackParticipant();
    p.setName(parent.getName());
    p.setTeam(parent.getTeam());
    p.setSex(parent.getSex());
    p.setAge(parent.getAge());
    
    int time;
    cout << "Enter participant's time (in seconds): ";
    cin >> time;
    p.setSeconds(time);
    
    return p;
}
