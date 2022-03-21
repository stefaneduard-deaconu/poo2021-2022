#include <bits/stdc++.h>
using namespace std;
class HangMan{
private:
    string cuvant;
    vector<char> litere_incercate;
    unsigned int incercari;
    bool ok_tot,ok_incercari;
public:
    explicit HangMan(string cuv);
    void guess(char c);
    void printStats();
    void printUnknownWord();
    int playerHasWon() const;
    bool verificare_cuv_complet();
    bool verificare_litera_lista(char &c);
    bool verif_joc_inchiat() const;
    void litera_corecta(char &c);
    void litera_gresita(char &c);
};

HangMan::HangMan(string cuv){
    cuvant = move(cuv);
    incercari = 6;
    ok_tot = false;
    ok_incercari = true;
}
bool HangMan::verificare_cuv_complet() {
    bool oktot = true;
    for(auto&x :cuvant) {
        if (x != ' ') {
            bool ok = false;
            for (auto &it: litere_incercate)
                if (it == x or toupper(it) == x or tolower(it) == x) {
                    ok = true;
                }
            if (!ok)
                oktot = false;
        }
    }
    if(oktot) {
        ok_tot = true;
        return true;
    }
    return false;
}
bool HangMan::verif_joc_inchiat() const {
    if (ok_tot or incercari <= 0)
        return true;
    return false;
}
bool HangMan::verificare_litera_lista(char &c) {
    for (auto &x: litere_incercate) {
        if (c == x or toupper(c) == x or tolower(c) == x) {
            cout << "You already tried this letter.Try another one\n";
            return true;
        }
    }
    return false;
}
int HangMan :: playerHasWon() const {
    if (ok_tot and incercari > 0) {
        cout << "(the player won)";
        return 1;
    }
    else {
        cout << "(the player lose)";
        return 0;
    }
}
void HangMan::printUnknownWord(){
    if(!verif_joc_inchiat()) {
        for (auto &x: cuvant) {
            if (x == ' ')
                cout << ' ';
            else {
                bool ok = false;
                for (auto &it: litere_incercate)
                    if (it == x or toupper(it) == x or tolower(it) == x) {
                        cout << x;
                        ok = true;
                    }
                if (!ok)
                    cout << "_ ";
            }
        }
    }
    else
        cout << "Congratulations! You've guessed the WORD won the GAME";
    cout<<'\n';
}
void HangMan::printStats(){
    cout<<"Guess ";
    printUnknownWord();
    cout<<"Tried letters: ";
    if(!litere_incercate.empty()){
        for(auto &it:litere_incercate)
            cout<<it<<' ';
    }
    cout<<'\n';
    cout <<	"You have " << incercari << " guesses left.";
    cout<<'\n';
}
void HangMan::litera_corecta(char &c) {
    if(!verificare_litera_lista(c)) {
        litere_incercate.push_back(c);
        if (!verificare_cuv_complet())
            cout << "You hit the spot! Now you only have to guess:";
        printUnknownWord();
    }
}
void HangMan::litera_gresita(char &c) {
    if (!verificare_cuv_complet()) {
        litere_incercate.push_back(c);
        if (incercari > 1) {
            incercari--;
            cout << "Unlucky! That was not it, but you still have " << incercari << " guesses left\n";
        } else {
            if (ok_incercari) {
                incercari--;
                cout << "Unlucky! That was not it. You don't have any guess left\n";
                ok_incercari = false;
            }
        }
    }
}
void HangMan::guess(char c){
    if(!verif_joc_inchiat()) {
        if (cuvant.find(c) != string::npos or cuvant.find(char(toupper(c))) != string::npos or cuvant.find(char(tolower(c))) != string::npos)
            litera_corecta(c);
        else
            litera_gresita(c);
    }
    else
        cout<<"Game Over.You can't make other operation\n";
}
int main() {

    HangMan game{"Thug pOO"};

    game.printStats();
    game.printUnknownWord();
    game.guess('P');
    game.guess('o');
    game.guess('p');
    game.printStats();
    game.guess('T');
    game.guess('h');
    game.guess('u');
    game.guess('g');

    game.guess('e');
    game.guess('y');
    game.guess('k');//game over .nu poti sa mai incerci
    game.guess('a');//game over .nu poti sa mai incerci
    game.guess('b');//game over .nu poti sa mai incerci
    game.guess('c');//game over .nu poti sa mai incerci
    game.guess('d');//game over .nu poti sa mai incerci


    cout << game.playerHasWon() << '\n';
    /*bool ok_menu = false;
    while(!game.verif_joc_inchiat()){
        int c;
        if(!ok_menu) {
            cout << "Alege nr. operatiei:\n";
            cout << "1.Printeaza cuvant necunorcut.\n";
            cout << "2.Printeaza stare(cuvant litere incercate si incercari ramase).\n";
            cout << "3.Incerca litera.\n";
            ok_menu = true;
        }
        else
            if(ok_menu)
                 cout<<"Introdu operatia:";
        cin >> c;
        switch (c) {
            case 1:
                game.printUnknownWord();
                break;
            case 2:
                game.printStats();
                break;
            case 3:
                char litera;
                cout<<"Introdu litera:";
                cin >> litera;
                game.guess(litera);
                break;
        }
        string cont;
        cout<<"Press any key to continue...\n";
        cin.get();
        getline(cin,cont);
    }
    game.playerHasWon();*/
    return 0;
}