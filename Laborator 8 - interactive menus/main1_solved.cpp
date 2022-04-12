#include <iostream>

using namespace std;

// Vom porni de la intrebarile:
// Ce ar trebui sa faca un meniu interactiv? Ce pasi sunt necesari pentru a-l folosi.

// Orice meniu va putea:
//  * lista optiunile
//  * alege corect una dintre optiuni
//  * va putea fi rulat la infinit (=interactiv din "meniu interactiv")

class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
public:
    void listOptions() override {
        cout << "1. Adaugă o nouă clădire." << '\n';
        cout << "2. Șterge o clădire existentă." << '\n';
        cout << "3. Modifică o clădire." << '\n';
        cout << "4. Ieșire." << '\n';
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeți un număr între "
                 << first << " și " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }

    void option1() {
        cout << "Aici vom adăuga o nouă clădire." << '\n';
    }

    void option2() {
        cout << "Aici vom șterge una dintre clădirile existente." << '\n';
    }

    void option3() {
        cout << "Aici vom modifica datele uneia dintre clădirile existente." << '\n';
    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 4);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            } else if (option == 4) {
                break;
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a încheiat cu success";
    }

};

int main() {
    SimpleMenu menu;
    menu.mainLoop(); // păstrăm simplu: funcția mainLoop „ruleaza” meniul la infinit.
}