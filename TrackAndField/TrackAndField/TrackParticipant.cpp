#include "TrackParticipant.hpp"
#include <iomanip>
TrackParticipant* TrackParticipant::createFromInput() {
    TrackParticipant* p = new TrackParticipant();
    p->collectFromInput();
    
    int time;
    cout << "Enter participant's time (in seconds): ";
    cin >> time;
    p->setSeconds(time);
    
    return p;
}

TrackParticipant* TrackParticipant::createDriverData(int driverIndex) {
    TrackParticipant* p = new TrackParticipant();
    switch (driverIndex) {
        case 0:
            p->name = "John Doe";
            p->team = "ABC";
            p->sex = "Male";
            p->age = 19;
            p->seconds = 8;
            break;
        case 1:
            p->name = "Spencer Smedley";
            p->team = "DEF";
            p->sex = "Male";
            p->age = 21;
            p->seconds = 39;
            break;
        case 2:
            p->name = "Rebecca Lacey";
            p->team = "GHI";
            p->sex = "Female";
            p->age = 20;
            p->seconds = 14;
            break;
        case 3:
            p->name = "Sophy Spooner";
            p->team = "JKL";
            p->sex = "Female";
            p->age = 23;
            p->seconds = 10;
            break;
        case 4:
            p->name = "Mitch Byrd";
            p->team = "MNO";
            p->sex = "Male";
            p->age = 18;
            p->seconds = 15;
            break;
        case 5:
            p->name = "Gareth Ashworth";
            p->team = "PQR";
            p->sex = "Male";
            p->age = 20;
            p->seconds = 12;
            break;
            
        default:
            break;
    }
    return p;
}
void TrackParticipant::sortForScoring(TrackParticipant **array, int size) {
    bool changesMade;
    do {
        changesMade = false;
        for (int i = 1; i < size; i++) {
            TrackParticipant* previous = *(array + i - 1);
            TrackParticipant* current = *(array + i);
            if (previous->seconds > current->seconds) {
                changesMade = true;
                TrackParticipant *temp;
                temp = current;
                array[i-1] = temp;
                array[i] = previous;
            }
        }
    } while (changesMade);
}
void TrackParticipant::sortArrayInteractive(TrackParticipant **array, int size) {
    char sortOption;
    cout << "Data can be sorted by participant name or time. Type n for name or t for time: ";
    cin >> sortOption;
    if (sortOption == 'n') {
        bool changesMade;
        do {
            changesMade = false;
            for (int i = 1; i < size; i++) {
                TrackParticipant* previous = *(array + i - 1);
                TrackParticipant* current = *(array + i);
                if (previous->name < current->name) {
                    changesMade = true;
                    TrackParticipant *temp;
                    temp = current;
                    array[i-1] = temp;
                    array[i] = previous;
                }
            }
        } while (changesMade);
    } else if (sortOption == 't') {
        sortForScoring(array, size);
    } else {
        cout << "Please type either n or t :(" << endl << endl;
        TrackParticipant::sortArrayInteractive(array, size);
    }
}

string TrackParticipant::confirmationString() {
    return "(" + name + ", " + team + ", " + sex + ", " + to_string(age) + ", " + to_string(seconds) + ")";
}

void TrackParticipant::output() {
    cout << setw(25) << name << setw(5) << team << setw(9) << sex << setw(5) << age << setw(12) << seconds << setw(5) << score << endl;
}
void TrackParticipant::outputHeader() {
    cout << setw(25) << "Name" << setw(5) << "Team" << setw(9) << "Gender" << setw(5) << "Age" << setw(12) << "Time (sec)" << setw(5) << "Score" << endl;
}
