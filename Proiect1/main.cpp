#include <iostream>

using namespace std;

// 1. invatam ceva nou :
// Ne va spune in fiecare moment daca am scris ceva gresit.
class Nume {
private:
    // 2. Noi oricum vom genera cod pentru tot ce poate fi generat automat.
    string name;
    int varsta;
public:
    // TODO Alt+Insert,
    Nume(const string &name, int varsta) : name(name), varsta(varsta) {}
};

int main(){
    int a,b,c; // c nu e folosit

    cout << a + b << endl;// sublinieaza cu rosu, sau scrie cu rosu ceea ce nu este definit.
}