#include <iostream>
#include <string>
#include "EventParticipant.hpp"
#include "FieldParticipant.hpp"
#include "TrackParticipant.hpp"
using namespace std;

const int K_DRIVER_LENGTH = 6;

int main(int argc, const char * argv[]) {
    EventParticipant** participants = new EventParticipant*[10];
    int length = 0;
    char type = '0';
    
    // Step 1: Generate or collect input
    cout << "Welcome! Type 1 for field event, 2 for track event, or d for driver." << endl;
    char input;
    cin >> input;
    if (input == '1' || input == '2') {
        char continueFlag = 'y';
        int iterationIndex = 0;
        do {
            if (input == '1') {
                participants[iterationIndex] = FieldParticipant::createFromInput();
            } else {
                participants[iterationIndex] = TrackParticipant::createFromInput();
            }
            EventParticipant* saved = *(participants + iterationIndex);
            cout << "Saved " + saved->confirmationString() << endl;
            cout << "Type y to continue, anything else to stop input: ";
            cin >> continueFlag;
            iterationIndex++;
        } while (continueFlag == 'y' && iterationIndex < 10);
        length = iterationIndex;
        if (input == '1') {
            type = 'f';
        } else {
            type = 't';
        }
    } else if (input == 'd') {
        char driverType;
        cout << "Type 1 for field driver, 2 for track driver" << endl;
        cin >> driverType;
        if (driverType == '1') {
            for (int i = 0; i < K_DRIVER_LENGTH; i++) {
                participants[i] = FieldParticipant::createDriverData(i);
                cout << "Created " + (*(participants + i))->confirmationString() << endl;
            }
            type = 'f';
            length = K_DRIVER_LENGTH;
        } else if (driverType == '2') {
            for (int i = 0; i < K_DRIVER_LENGTH; i++) {
                participants[i] = TrackParticipant::createDriverData(i);
                cout << "Created " + (*(participants + i))->confirmationString() << endl;
            }
            type = 't';
            length = K_DRIVER_LENGTH;
        } else {
            return -1;
        }
    }
    
    // Step 2: Sort & score
    if (type == 't') {
        TrackParticipant** tpCastArray = reinterpret_cast<TrackParticipant**>(participants);
        TrackParticipant::sortForScoring(tpCastArray, length);
        EventParticipant::doScoring(participants, length);
        TrackParticipant::sortArrayInteractive(tpCastArray, length);
    } else if (type == 'f') {
        FieldParticipant** fpCastArray = reinterpret_cast<FieldParticipant**>(participants);
        FieldParticipant::sortForScoring(fpCastArray, length);
        EventParticipant::doScoring(participants, length);
        FieldParticipant::sortArrayInteractive(fpCastArray, length);
    }
    
    cout << endl << endl;
    
    // Step 3: output
    (*(participants))->outputHeader();
    for (int i = 0; i < length; i++) {
        (*(participants + i))->output();
    }
    
    // Step 4: wait for return
    cout << endl << endl << "(program complete, type any character + enter to exit)" << endl;
    char kill = '`';
    do { cin >> kill; } while (kill == '`');
    
    return 0;
}
