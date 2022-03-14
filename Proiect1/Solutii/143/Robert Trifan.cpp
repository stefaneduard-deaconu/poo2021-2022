#include <iostream>
#include <string>
#include <map>

using namespace std;

class HangMan {
private:
    int guessesLeft;
    map<char, bool> triedLetters;
    string word;
    string revealedWord;
    bool endGame;
public:
    HangMan() {
        HangMan::endGame = false;
        HangMan::guessesLeft = 0;
        HangMan::word = "";
        HangMan::revealedWord = "";
    }

    HangMan(string _word) {
        endGame = false;
        word = _word;
        guessesLeft = 6;
        revealedWord = string(word.length(), '_');
        for (int i = 0; i < word.length(); ++i) {
            if (word[i] == ' ') {
                revealedWord[i] = ' ';
            }
        }
    }

    void printUnknownWord() {
        for (int i = 0; i < revealedWord.length(); ++i) {
            if (i > 0) {
                cout << " ";
            }
            cout << revealedWord[i];
        }
        cout << "\n";
    }

    void printStats() {
        cout << "Guess ";
        printUnknownWord();
        cout << "Tried letters: ";
        for (auto &i: triedLetters) {
            cout << i.first << " ";
        }
        cout << "\n";
        cout << "You have " << guessesLeft << " left.\n";
    }

    bool playerHasWon() {
        if (revealedWord == word && guessesLeft > 0) {
            return true;
        }
        return false;
    }

    void guess(char ch) {
        if (endGame == true) {
            cout << "No more guesses left! Restart the game!\n"; //am adaugat eu partea asta
            return;
        }
        char smallCh, bigCh;
        if ('a' <= ch && ch <= 'z') {
            smallCh = ch;
            bigCh = ch - 'a' + 'A';
        }
        if ('A' <= ch && ch <= 'Z') {
            smallCh = ch - 'A' + 'a';
            bigCh = ch;
        }
        triedLetters[bigCh] = true;
        bool ok = false;
        for (int i = 0; i < word.length(); ++i) {
            if (word[i] == smallCh || word[i] == bigCh) {
                revealedWord[i] = word[i];
                ok = true;
            }
        }
        if (ok) {
            cout << "You hit the spot! Now you only have to guess ";
            printUnknownWord();
            if (playerHasWon()) {
                cout << "Congratulations! You've guessed the WORD won the GAME\n";
            }
        } else {
            --guessesLeft;
            if (guessesLeft <= 0) {
                endGame = true;
                cout << "You lost!\n";
            } else {
                cout << "Unlucky! That was not it, but you still have " << guessesLeft << " guesses left\n";
            }
        }
    }
};

int main() {
    HangMan game{"Thug POO"};

    game.printStats(); /*
	functia membra va afisa:

	Guess  _ _ _ _   _ _ _
	Tried letters:
	You have 6 guesses left.

 */
    game.printUnknownWord(); // Va afisa: "_ _ _ _   _ _ _"
    game.guess('P'); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _ _ P _ _"
    game.guess('o'); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _ _ P O O"
    game.printStats(); /* va afisa:
    	Guess  _ _ _ _ _ P O O
    	Tried letters: PO
    	You have 6 guesses left.
 */

    game.guess('z'); // "Unlucky! That was not it, but you still have 5 guesses left"

    game.guess('t');
    game.guess('h');
    game.guess('u');
    game.guess('g');
    // dupa ultimul apel se va afisa: "Congratulations! You've guessed the WORD won the GAME"
    cout << game.playerHasWon() << "\n";
    return 0;
}