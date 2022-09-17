#include "EventParticipant.hpp"
EventParticipant EventParticipant::inputFromCIN() {
    EventParticipant p = EventParticipant();
    string name;
    cout << "Enter participant's name: ";
    cin >> name;
    string team;
    cout << "Enter participant's team: ";
    cin >> team;
    string sex;
    cout << "Enter participant's sex: ";
    cin >> sex;
    int age;
    cout << "Enter participant's age: ";
    cin >> age;
    
    p.setName(name);
    p.setTeam(team);
    p.setSex(sex);
    p.setAge(age);
    
    return p;
}
