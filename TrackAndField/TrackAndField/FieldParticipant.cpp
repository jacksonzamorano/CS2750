//
//  FieldParticipant.cpp
//  TrackAndField
//
//  Created by Jackson Zamorano on 9/15/22.
//
#include <iomanip>
#include "FieldParticipant.hpp"

FieldParticipant* FieldParticipant::createFromInput() {
    FieldParticipant* p = new FieldParticipant();
    p->collectFromInput();
    
    int distance;
    cout << "Enter participant's distance: ";
    cin >> distance;
    p->setDistance(distance);
    
    return p;
}

FieldParticipant* FieldParticipant::createDriverData(int driverIndex) {
    FieldParticipant* p = new FieldParticipant();
    switch (driverIndex) {
        case 0:
            p->name = "John Doe";
            p->team = "ABC";
            p->sex = "Male";
            p->age = 19;
            p->distance = 67;
            break;
        case 1:
            p->name = "Spencer Smedley";
            p->team = "DEF";
            p->sex = "Male";
            p->age = 21;
            p->distance = 45;
            break;
        case 2:
            p->name = "Rebecca Lacey";
            p->team = "GHI";
            p->sex = "Female";
            p->age = 20;
            p->distance = 56;
            break;
        case 3:
            p->name = "Sophy Spooner";
            p->team = "JKL";
            p->sex = "Female";
            p->age = 23;
            p->distance = 50;
            break;
        case 4:
            p->name = "Mitch Byrd";
            p->team = "MNO";
            p->sex = "Male";
            p->age = 18;
            p->distance = 68;
            break;
        case 5:
            p->name = "Gareth Ashworth";
            p->team = "PQR";
            p->sex = "Male";
            p->age = 20;
            p->distance = 72;
            break;
            
        default:
            break;
    }
    return p;
}

void FieldParticipant::sortForScoring(FieldParticipant **array, int size) {
    bool changesMade;
    do {
        changesMade = false;
        for (int i = 1; i < size; i++) {
            FieldParticipant* previous = *(array + i - 1);
            FieldParticipant* current = *(array + i);
            if (previous->distance < current->distance) {
                changesMade = true;
                FieldParticipant *temp;
                temp = current;
                array[i-1] = temp;
                array[i] = previous;
            }
        }
    } while (changesMade);
}

void FieldParticipant::sortArrayInteractive(FieldParticipant **array, int size) {
    char sortOption;
    cout << "Data can be sorted by participant name or distance. Type n for name or d for distance: ";
    cin >> sortOption;
    if (sortOption == 'n') {
        bool changesMade;
        do {
            changesMade = false;
            for (int i = 1; i < size; i++) {
                FieldParticipant* previous = *(array + i - 1);
                FieldParticipant* current = *(array + i);
                if (previous->name > current->name) {
                    changesMade = true;
                    FieldParticipant *temp;
                    temp = current;
                    array[i-1] = temp;
                    array[i] = previous;
                }
            }
        } while (changesMade);
    } else if (sortOption == 'd') {
        sortForScoring(array, size);
    } else {
        cout << "Please type either n or d :(" << endl << endl;
        FieldParticipant::sortArrayInteractive(array, size);
    }
}

string FieldParticipant::confirmationString() {
    return "(" + name + ", " + team + ", " + sex + ", " + to_string(age) + ", " + to_string(distance) + ")";
}

void FieldParticipant::output() {
    cout << setw(25) << name << setw(5) << team << setw(9) << sex << setw(5) << age << setw(10) << distance << setw(7) << score << endl;
}
void FieldParticipant::outputHeader() {
    cout << setw(25) << "Name" << setw(5) << "Team" << setw(9) << "Gender" << setw(5) << "Age" << setw(10) << "Distance" << setw(7) << "Score" << endl;
}
