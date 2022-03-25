#include <iostream>

using namespace std;

class Data {
private:
    // date membre (denumite si campuri)
    int an, luna, zi;
public:
    // datele publice, dar aici vom pune doar funcții
    void afiseaza() {
        cout << an << '.' << luna << '.' << zi << ' ';
    }
    // in partea public:  punem si metode speciale precum constuctori
    Data() {
        cout << "Constructor gol!" << endl;
        an = luna = zi = 0; // ca sa stim ca am folosit constructorul gol, punem valori goale aici
    }
    Data(int _an, int _luna, int _zi) {
        an = _an;
        luna = _luna;
        zi = _zi;
    }
    // și getteri/setteri
    int getLuna() {
        return luna;
    }

    void setLuna(int luna) {
        Data::luna = luna;
    }
};

// cum folosim clasa Data:
int main() {
    Data d1; // ruleaza codul din constructorul fără parametrii
    Data d2(2022,2,22); // !! ruleaza codul din constructorul fără parametrii
    Data d3(2022,2,23); // !! ruleaza codul din constructorul fără parametrii

    // ! putem scrie si    Data d1, d2(2022,2,22);  etc  dar era mai clar pentru exemplu nostru
    //   sa scriem pe cate un rand

    d1.afiseaza();
    d2.afiseaza();
    d3.afiseaza();
    cout << '\n' << '\n';

    // Putem folosi constructorul și în acest mod:
    d3 = Data(30, 4, 2022);
    cout << "Lucrăm în fiecare săptămână, ca nici măcar să nu știm cum ajungem în ";
    d3.afiseaza();
    cout << "..și codăm programe POO la un nivel avansat!" << '\n' << '\n';

    // Dacă în schimb vrem să modificăm un singur câmp, folosim un setter:
    d3.setLuna(5); // până atunci deja devenim maeștrii
    cout << "După apelul d3.setLuna(5), avem d3 = ";
    d3.afiseaza();
    cout << '\n';

    // Și similar, dacă ne dorim valoarea unui singur câmp, folosim un getter:
    int valoareLuna = d2.getLuna();
    cout << "Data d2 conține luna " << valoareLuna << '\n';

    return 0;
}