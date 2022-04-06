#include <iostream>

#include "util/IoBase.h"
#include "util/functions.h"


#include<functional>
#include<vector>
#include<string>
#include<map>

using namespace std;

class Building : public IoBase {
private:
    string color, owner;
    int height;
    // TODO constructori si getteri:
};

class CrudMenu : public BaseMenu {
private:
    string label;
    map<string, function<void(const vector<Building> &)> > options;
public:

};
// PUTEM folosi functii globale care sa acceseze sirul de elemente
void sorteaza(vector<Building>)
int main() {
    // PUTEM folosi lambda functions pentru a crea metodele
    function<void(const vector<Building> &)> afiseaza = [](const vector<Building> &v) -> void {
        for (auto building: v) {
            cout << building << '\n';
        }
    };

//    ASA cream un map
//    map<int,int> m = {
//            {2,3},
//            {3,4}
//    };

    CrudMenu menu(
            { // vectorul de cladiri
                    Building("red", "Gabriel", 7),
                    Building("blue", "Penelope", 4),
            },
            {  // map-ul care contine etichetele optiunilor si functiile rulata
                    {"Afiseaza", afiseaza},
                    {"Sorteaza", sorteaza}
            }
    );
    menu.mainLoop();
}