#include <iostream>
#include <string> // pentru tipul.. string    cine ar fi crezut?

using namespace std;

// Aici aveți un exemplu de clasă compusă:

class Data {
private:
    int an, luna, zi;
public:
    // Începem să folosim CLion
    //
    // Dacă dați Alt+Insert (sau click-dreapta->Generate)
    // când aveți cursorul în interiorul clasei
    //  descoperiți lista cu metode care pot fi generate, inclusiv Constructor
    Data(int an, int luna, int zi) : an(an), luna(luna), zi(zi) {}
};

class Event {
private:
    Data start, end;
    string name;
public:
    // TODO
};

// În acest mod am folosi compunere de clase dacă am vrea sa rezolvăm
//  exercițiul 5 din Laboratorul 1.
