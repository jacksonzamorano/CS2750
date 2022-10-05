#include "string"
#include "iostream"
using namespace std;

#ifndef EventParticipant_hpp
#define EventParticipant_hpp
    
class EventParticipant {
    
protected:
    string name = "";
    string team = "";
    string sex = "";
    int age = 0;
    int place = 0;
    int score = 0;
    
public:
    void collectFromInput();
    static void doScoring(EventParticipant** array, int size);
    virtual string confirmationString();
    virtual void output() = 0;
    virtual void outputHeader() = 0;

    string getName() { return this->name; }
    string getTeam() { return this->team; }
    string getSex() { return this->sex; }
    int getAge() { return this->age; }

    void setName(string x) {
        this->name = x;
    }
    void setTeam(string x) {
        this->team = x;
    }
    void setSex(string x) {
        this->sex = x;
    }
    
    void setAge(int x) {
        this->age = x;
    }
    void setPlace(int x) {
        this->place = x;
    }
    void setScore(int x) {
        this->score = x;
    }
};

#include <stdio.h>

#endif /* EventParticipant_hpp */
