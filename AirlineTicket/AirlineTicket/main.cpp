#include <iostream>
#include <string>
#include "Flight.hpp"
#include "DoubleLinkedList.hpp"
#include "DoubleLinkedList.cpp"

using namespace std;

int mainMenu();
void runLoop();
void manageFlightLoop();
void printAllManifests();
void fillDriverData();
DoubleLinkedList<Flight>* flights = new DoubleLinkedList<Flight>;

int main(int argc, const char * argv[]) {
    runLoop();
    return 0;
}

void runLoop() {
    int option = mainMenu();
    while (option < 4) {
        if (option == 1) {
            manageFlightLoop();
        } else if (option == 2) {
            printAllManifests();
        } else if (option == 3) {
            fillDriverData();
        }
        option = mainMenu();
    }
}
void manageFlightLoop() {
    int flightNumber;
    cout << "Type a flight number to manage: ";
    cin >> flightNumber;

    Flight* data = flights->valueWhere([flightNumber] (const Flight& f) { return f.flightNumber == flightNumber; });
    if (data == nullptr) {
        data = new Flight;
        data->flightNumber = flightNumber;
        flights->insertHead(data);
    }
    
    int flightManageOption;
    do {
        cout << " --- Manage passengers on flight " << flightNumber << " --- " << endl;
        cout << "1: Add passenger on flight " << flightNumber << endl;
        cout << "2: Remove passenger on flight " << flightNumber << endl;
        cout << "3: List passengers on flight " << flightNumber << endl;
        cout << "4: List passengers on flight " << flightNumber << " in reverse" << endl;
        cout << "5: Exit flight menu" << endl;
        cout << "Pick an option: ";
        cin >> flightManageOption;
        if (flightManageOption == 1) {
            string name;
            cout << "Type the name of the passenger to add to flight " << flightNumber << ": ";
            cin.ignore(1000, '\n');
            getline(cin, name);
            Passenger* p = new Passenger(name);
            data->passengers->insertHead(p);
            data->passengers->sort([] (const Passenger& a, const Passenger& b) {
                return a.name < b.name;
            });
            cout << "Created.";
            cout << endl << endl;
        } else if (flightManageOption == 2) {
            cout << "Type the corresponding number of the passsenger to delete:" << endl;
            int index = 1;
            DoubleLinkedNode<Passenger>* pdata = data->passengers->getHead();
            while (pdata != nullptr) {
                cout << index << ": " << pdata->data->name << endl;
                pdata = pdata->next;
                index++;
            }
            int selection;
            cout << "Which passenger: ";
            cin >> selection;
            cout << endl << "Deleted.";
            cout << endl << endl;
            data->passengers->deleteIndex(selection - 1);
        } else if (flightManageOption == 3) {
            cout << endl << endl << "=== Passengers on flight " << data->flightNumber << " ===" << endl;
            data->passengers->each([] (const Passenger& p) {
                cout << "- " << p.name << endl;
            });
            cout << endl << endl;
            cin.ignore(1000, '\n');
        } else if (flightManageOption == 4) {
            cout << endl << endl << "=== Passengers on flight " << data->flightNumber << " (reversed) ===" << endl;
            data->passengers->sort([] (const Passenger& a, const Passenger& b) {
                return a.name > b.name;
            });
            data->passengers->each([] (const Passenger& p) {
                cout << "- " << p.name << endl;
            });
            // Resort the data afterwards.
            data->passengers->sort([] (const Passenger& a, const Passenger& b) {
                return a.name < b.name;
            });
            cout << endl << endl;
            cin.ignore(1000, '\n');
        }
    } while (flightManageOption < 4);
    cout << endl << endl;
}

void printAllManifests() {
    cout << endl << endl;
    flights->each([] (const Flight& f) {
        cout << "Flight #" << f.flightNumber << ": " << endl;
        f.passengers->each([] (const Passenger& p) {
            cout << "Name: " << p.name << endl;
        });
        cout << endl;
    });
    cout << endl << endl;
}

void fillDriverData() {
    cout << endl << endl << "Adding flight driver data..." << endl;
    cout << "Created flight 2430" << endl;
    Flight* f2430 = new Flight;
    f2430->flightNumber = 2430;
    f2430->passengers->insertHead(new Passenger("Dale Hamilton"));
    f2430->passengers->insertHead(new Passenger("Leslie Hamilton"));
    f2430->passengers->insertHead(new Passenger("Jonathan Hamilton"));
    f2430->passengers->insertHead(new Passenger("Nicholas Hamilton"));
    f2430->passengers->insertHead(new Passenger("Annalisa Hamilton"));
    f2430->passengers->sort([] (const Passenger& a, const Passenger& b) {
        return a.name < b.name;
    });
    f2430->passengers->each([] (const Passenger& a) {
        cout << "Added " << a.name << "to flight " << 2430 << endl;
    });
    cout << "Created flight 2515" << endl;
    Flight* f2515 = new Flight;
    f2515->flightNumber = 2515;
    f2515->passengers->insertHead(new Passenger("Thor Absorka"));
    f2515->passengers->insertHead(new Passenger("Nora Snowwisper"));
    f2515->passengers->insertHead(new Passenger("Loki the Mutt"));
    f2515->passengers->sort([] (const Passenger& a, const Passenger& b) {
        return a.name < b.name;
    });
    f2515->passengers->each([] (const Passenger& a) {
        cout << "Added " << a.name << " to flight " << 2430 << endl;
    });
    flights->insertHead(f2430);
    flights->insertHead(f2515);
    cout << endl << endl;
    printAllManifests();
    cout << "Changing Loki's flight from 2515 -> 2750..." << endl;
    f2515->passengers->deleteWhere([] (const Passenger& a) { return a.name == "Loki the Mutt"; });
    Flight* f2750 = new Flight;
    f2750->flightNumber = 2750;
    f2750->passengers->insertHead(new Passenger("Loki the Mutt"));
    flights->insertHead(f2750);
    cout << "Flight changed, printing manifest..." << endl;
    printAllManifests();
    
    cin.ignore(1000, '\n');
}


int mainMenu() {
    cout << "            --- Main Menu ---            " << endl;
    cout << "1: Press to manage flights & passengers" << endl;
    cout << "2: Press to print out all manifests" << endl;
    cout << "3: Run driver" << endl;
    cout << "4: Exit program" << endl;
    cout << "What do you want to do: ";
    int value;
    cin >> value;
    
    if (value > 4 || value < 1) {
        cout << endl << " - Please type a valid option :| - " << endl << endl;
        value = mainMenu();
    }
    return value;
}
