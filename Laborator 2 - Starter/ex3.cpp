#include <iostream>
#include <string> // pentru tipul.. string    cine ar fi crezut?

using namespace std;

// Tablouri decorative

// Exemplu de citire, pentru cand se strang mai multe date:

class Tablou {
private:
    string mesaj;
    // ...
public:
    void citeste() {
        cout << "Mesaj motivational: ";
        getline(cin, mesaj); // echivalentul a cin.getline() pt tipul string
        // ...
    }
};

