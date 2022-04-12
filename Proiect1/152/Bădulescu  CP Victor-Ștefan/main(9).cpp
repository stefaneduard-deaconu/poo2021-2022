#include <iostream>
using namespace std;
class HangMan {
private:
    string cuv_original, cuv_ghicit = "";
    int no_gusses = 6, fin = 0, nr_underscore = 0;
    string litere_incercate = "";
public:
    int is_letter(char c) {
        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) return 1;
        return 0;
    }

    HangMan(string cuv) {
        cuv_original = cuv;
        for (int i = 0; i < cuv.size(); i++) {
            if (is_letter(cuv[i])) {
                cuv_ghicit += '_';
                nr_underscore++;
            } else cuv_ghicit += cuv[i];
        }
    }

    void printUnknownWord() {
        cout << cuv_ghicit + '\n';
    }

    void printStats() {
        cout << "Guess " + cuv_ghicit + '\n' + "Tried letters: " + litere_incercate + '\n' + "You have " << no_gusses
             << " guesses left.\n";
    }

    int c_in_tried(char c) {
        for (int i = 0; i < litere_incercate.size(); i++) if (c == litere_incercate[i]) return 0;
        return 1;
    }

    int playerHasWon() {
        return fin;
    }

    void guess(char c) {
        if (no_gusses) {
            c = toupper(c);
            if (!c_in_tried(c)) cout << "You already tried \'" << c << "\'\n";
            else {
                if (is_letter(c)) {
                    litere_incercate += c;
                    int ok = 0;
                    for (int i = 0; i < cuv_original.size(); i++) {
                        if (cuv_original[i] == c || cuv_original[i] == tolower(c)) {
                            ok = 1;
                            cuv_ghicit[i] = cuv_original[i];
                            nr_underscore--;
                        }
                    }
                    if (ok) {
                        if (nr_underscore == 0) {
                            cout << "Congratulations! You've guessed the WORD " << "\'" << cuv_original << "\'" << " and won the GAME!\n";
                            fin = 1;
                        }
                        else{
                            cout << "You hit the spot! Now you only have to guess " + cuv_ghicit + '\n';
                        }
                    } else {
                        no_gusses--;
                        cout << "Unlucky! That was not it, but you still have " << no_gusses << " guesses left.\n";
                    }
                } else cout << "Please type a letter\n";
            }

        } else cout << "You have no more guesses. Game Over!\n";
    }
};
int main() {
    HangMan game("Thug POO");
    game.printStats(); /*
	functia membra va afisa:

	Guess  _ _ _ _   _ _ _
	Tried letters:
	You have 6 guesses left.

 */
    game.printUnknownWord(); // Va afisa: "_ _ _ _   _ _ _"
    game.guess('P'); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _    P _ _"
    game.guess('o'); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _   P O O"
    game.printStats(); /* va afisa:
    	Guess  _ _ _ _   P O O
    	Tried letters: PO
    	You have 6 guesses left.
 */

    game.guess('z'); // "Unlucky! That was not it, but you still have 5 guesses left"
    game.guess('z');
    game.guess('t');
    game.guess('h');
    game.guess('u');
    game.guess('t');
    game.guess('a');
    game.guess('b');
    game.guess('c');
    game.guess('d');
    game.guess(' ');
//    game.guess('e');
//    game.guess('f');
//    game.guess('i');
    game.guess('g');
    return 0;
}
