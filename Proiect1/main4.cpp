#include <iostream>
#include <string>

using namespace std;

// helper functions:
void afisareBinara(char c) {
    for (int i = 7; i >= 0; --i) {
        if (((1 << i) & c) != 0) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
}

void testPrint(string original, string cheie, string criptat) {
    // deoarece nu stim sigur daca ^ a determinat sau nu valoarea 00000000 ('\0') in timpul operatiei,
    //  vom folosi strlen(original)
    cout << " cheie | ";
    for (int i = 0; i < original.size(); ++i) {
        afisareBinara(cheie[i % cheie.size()]);
        cout << " | ";
    }
    cout << '\n';
    cout << "ascuns | ";
    for (int i = 0; i < original.size(); ++i) {
        afisareBinara(criptat[i]);
        cout << " | ";
    }
    cout << '\n';
    cout << " mesaj | ";
    for (int i = 0; i < original.size(); ++i) {
        afisareBinara(original[i]);
        cout << " | ";
    }
    cout << '\n';
}

class Crypt {
private:
    string secretKey;
public:
    Crypt(const string &secretKey) : secretKey(secretKey) {}

    string encrypt(string mesaj) {
        string criptat = mesaj;

        int i = 0;
        for (char &c: criptat) {
            c = c ^ secretKey[i % secretKey.size()];
            i++;
        }

        return criptat;
    }
};

class EncryptedConversation {

};

int main() {
    Crypt crypt("POO justice");
    string mesaj = "Happy ";
    string criptat = crypt.encrypt(mesaj);
    testPrint(mesaj, "POO justice", criptat);
}


//int main() {
//    Crypt crypt("Ch3i3"); // cine s-ar gandi la parola asta?
//    CryptedConversation conversation(crypt);
//
//    conversation.addMessage("Salutare! Cand urmeaza sa ne auzim?");
//    conversation.addMessage("Cat de curand.. stai o clipa");
//
//    conversation.addMessage("-Knock knock!");
//    conversation.addMessage("-Who's there?");
//    conversation.addMessage("-Daisy");
//    conversation.addMessage("-Daisy who?");
//    conversation.addMessage("-DAISY ME ROLLING!");
//
//    conversation.show(0);
//    /*
//     * Afiseaza
//
//     "Salutare! Cand urmeaza sa ne auzim?"
//
//     */
//    conversation.show(2, 7);
//    /*
//     * Afiseaza
//
//    "-Knock knock!"
//    "-Who's there?"
//    "-Daisy"
//    "-Daisy who?"
//    "-DAISY ME ROLLING"
//     */
//
//    conversation.updateKey("Kee");
//
//
//}

//int main() {
//
//    HangMan game{"Thug POO"};
//
//    game.printStats(); /*
//    functia membra va afisa:
//
//    Guess  _ _ _ _   _ _ _
//    Tried letters:
//    You have 6 guesses left.
//
// */
//    game.printUnknownWord(); // Va afisa: "_ _ _ _   _ _ _"
//    game.quess('P'); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _ _ P _ _"
//    game.quess('o'); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _ _ P O O"
//    game.printStats(); /* va afisa:
//        Guess  _ _ _ _ _ P O O
//        Tried letters: PO
//        You have 6 guesses left.
// */
//
//    game.quess('z'); // "Unlucky! That was not it, but you still have 5 guesses left"
//
//    game.quess('t');
//    game.quess('h');
//    game.quess('u');
//    game.quess('g');
//    // dupa ultimul apel se va afisa: "Congratulations! You've guessed the WORD won the GAME"
//
//    // si mai puteti implementa o functie care verifica daca jocul s-a terminat:
//    cout << game.playerHasWon() << endl; // va afisa 1, deoarece jucatorul a castigat
//}
