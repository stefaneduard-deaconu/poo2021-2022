#include <bits/stdc++.h>

using namespace std;

class HangMan {
private:
    string word;
    string currGuess;
    vector<char> triedLetters;
    int guessLeft;

public:
    HangMan(const string &word, const int &guessLeft) : word(word), guessLeft(guessLeft){
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == ' ') {
                HangMan::currGuess += "  ";
            }
            else {
                HangMan::currGuess += "_ ";
            }
        }
        HangMan::triedLetters.clear();
    }

    void printStats() {
        cout << "Guess: " << HangMan::currGuess << "\n";
        cout << "Tried letters: ";
        for (char c: HangMan::triedLetters) {
            cout << c << " ";
        }
        cout << "\n";
        cout << "You have " << HangMan::guessLeft << " guess";
        if (HangMan::guessLeft > 1) {
            cout << "es";
        }
        cout << " left.\n";
    };

    void printUnknownWord() {
        cout << HangMan::currGuess << "\n";
    }

    bool playerHasWon() {
        for (char c: HangMan::currGuess) {
            if (c == '_') {
                return false;
            }
        }
        return true;
    }

    void guess(char c) {
        HangMan::triedLetters.push_back(toupper(c));
        bool isCorrect = false;
        for (int i = 0; i < HangMan::word.size(); i++) {
            if (HangMan::currGuess[2 * i] == '_' && tolower(HangMan::word[i]) == tolower(c)) {
                isCorrect = true;
                HangMan::currGuess[2 * i] = HangMan::word[i];
            }
        }
        if (isCorrect) {
            if (HangMan::playerHasWon()) {
                cout << "Congratulations! You've guessed the WORD and won the GAME!\n";
            }
            else {
                cout << "You hit the spot! Now you only have to guess: " << HangMan::currGuess << "\n";
            }
        }
        else {
            HangMan::guessLeft--;
            if (HangMan::guessLeft > 0) {
                cout << "Unlucky! That was not it, but you still have " << HangMan::guessLeft << " guess";
                if (HangMan::guessLeft > 1) {
                    cout << "es";
                }
                cout << " left.\n";
            }
            else {
                cout << "You lose -_-\n";
            }
        }
    }
};

int main() {
    HangMan game{"Thug POO", 6};
    game.printStats();
    game.printUnknownWord();
    game.guess('P');
    game.guess('o');
    game.printStats();
    game.guess('z');
    game.guess('t');
    game.guess('h');
    game.guess('u');
    game.guess('g');
    return 0;
}
