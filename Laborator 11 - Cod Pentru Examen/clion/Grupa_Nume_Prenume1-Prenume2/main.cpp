/*
 * Compilator MinGW_64 8.1.0
 * Tutore Laborator: Deaconu Ștefan-Eduard
 *
 */

#include <iostream>
#include <memory> // pentru shared_ptr si make_shared
#include <vector>

// cod inspirat din laboratorul 6
#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

// Ierarhia de clase, de la

// Aplicatie creata poate fi similara cu CrudMenu pe care l-ati implementat
class ApplicationMenu {

};

// Sau puteti implementa totul in main. Ca este sau ca nu este Singleton, veti primi bonus daca folositi o clasa principala.

int main() {
    ApplicationMenu menu;
    menu.mainLoop(); // păstrăm simplu: funcția mainLoop „ruleaza” meniul la infinit.
}