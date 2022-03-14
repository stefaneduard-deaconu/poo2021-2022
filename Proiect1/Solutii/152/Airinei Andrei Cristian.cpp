#include <bits/stdc++.h>


class HangMan {
private:
    std :: string Word;
    std :: set < char > Guessed;
    std :: set < char > NotGuessed;
    int Left;
public:
    HangMan(std :: string starter)
    {
        Word = starter;
        Guessed.clear(); // nu este necesar
        for(auto it : starter)
            if(std::isalpha(it))
                NotGuessed.insert(tolower(it));
        Left = 6;
    }
    void printUnknownWord()
    {
        for(auto it : Word)
        {
            if(it == ' ') {
                std::cout << it;
                continue;
            }
            if(Guessed.find(tolower(it)) == Guessed.end())
                std :: cout << '_';
            else
                std :: cout << it;
        }
        std :: cout << '\n';
    }
    void printStats()
    {
        std :: cout << "Guess ";
        printUnknownWord();
        std :: cout << "Tried letters: ";
        for(auto it : Guessed)
            std :: cout<<it<<' ';
        std :: cout << '\n';
        std :: cout << "You have " << Left << " guessed left.\n";
    };
    void guess(char letter)
    {
        if(NotGuessed.empty())
        {
            std :: cout << "You already won\n";
            return;
        }
        if(Left == 0)
        {
            std :: cout << "You ran out of guesses\n";
            return;
        }
        letter = tolower(letter);
        if(Guessed.find(letter) != Guessed.end())
        {
            std :: cout << "You have already guessed this letter, try another\n";
            return;
        }
        if(NotGuessed.find(letter) == NotGuessed.end())
        {
            std :: cout << "Unlucky! That was not it, but you still have " << --Left << " guesses left\n";
            return;
        }
        NotGuessed.erase(letter);
        Guessed.insert(letter);

        if(NotGuessed.empty()) {
            std::cout << "Congratulations! You've guessed the WORD won the GAME\n";
            return;
        }
        std :: cout << "You hit the spot! Now you only have to guess";
        printUnknownWord();
    };
    bool playerHasWon()
    {
        return NotGuessed.empty();
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

    // si mai puteti implementa o functie care verifica daca jocul s-a terminat:
    std :: cout << game.playerHasWon() << std :: endl; // va afisa 1, deoarece jucatorul a castigat
    return 0;
}
