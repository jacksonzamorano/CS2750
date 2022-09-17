//
//  FieldParticipant.cpp
//  TrackAndField
//
//  Created by Jackson Zamorano on 9/15/22.
//

#include "FieldParticipant.hpp"

EventParticipant FieldParticipant::inputFromCIN() {
    EventParticipant parent = EventParticipant::inputFromCIN();
    FieldParticipant p = FieldParticipant();
    p.setName(parent.getName());
    p.setTeam(parent.getTeam());
    p.setSex(parent.getSex());
    p.setAge(parent.getAge());
    
    int distance;
    cout << "Enter participant's distance: ";
    cin >> distance;
    p.setDistance(distance);
    
    return p;
}
