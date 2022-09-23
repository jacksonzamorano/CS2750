#include <iostream>
#include <limits>
#include <ios>
#include "EventParticipant.hpp"
using namespace std;
void EventParticipant::collectFromInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    string name_upper;
    cout << "Enter participant's name: ";
    getline(cin, name);
    name_upper = name;
    for (int i = 0; i < name.length(); i++) {
        name_upper[i] = toupper(name[i]);
    }
    string team;
    cout << "Enter participant's team: ";
    getline(cin, team);
    string sex;
    cout << "Enter participant's sex: ";
    cin >> sex;
    int age;
    cout << "Enter participant's age: ";
    cin >> age;
    
    setName(name_upper);
    setTeam(team);
    setSex(sex);
    setAge(age);
}

void EventParticipant::doScoring(EventParticipant **array, int size) {
    for (int i = 0; i < size; i++) {
        switch (i) {
            case 0:
                array[i]->score = 10;
                break;
            case 1:
                array[i]->score = 8;
                break;
            case 2:
                array[i]->score = 6;
                break;
            case 3:
                array[i]->score = 4;
                break;
            case 4:
                array[i]->score = 2;
                break;
            case 5:
                array[i]->score = 1;
                break;
            default:
                array[i]->score = 0;
                break;
        }
    }
}

string EventParticipant::confirmationString() {
    return "(" + name + ", " + team + ", " + sex + ", " + to_string(age) + ")";
}
