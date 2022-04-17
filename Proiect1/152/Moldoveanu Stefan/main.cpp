#include <bits/stdc++.h>

class HangMan{
    std::string phrase;
    int tries;
    int guesses;
    bool done;

public:
    HangMan(): tries(0), guesses(6), done(false) {}
    explicit HangMan(std::string &phrase): phrase(std::move(phrase)), tries(0), guesses(6), done(false) {}

    void initialize()
    {
        std::cout << "Input phrase:\n";
        std::cin.get();
        std::string new_phrase;
        std::getline(std::cin, new_phrase);
        (*this) = HangMan(new_phrase);
    }

    void printUnknownWord()
    {
        std::for_each(phrase.begin(), phrase.end(), [](const char letter){
            if (letter == ' ') {
                std::cout << ' ';
            } else if (int(letter) < 0) {
                std::cout << char(-letter);
            } else {
                std::cout << '_';
            }
        });

        std::cout << "\n";
    }

    void printStats()
    {
        std::cout << "Guess: ";
        printUnknownWord();

        std::cout << "Tried letters: ";
        for (int i = 'a'; i <= 'z'; ++i) {
            if (tries & (1 << (int(i) - 'a'))) {
                std::cout << char(i) << " ";
            }
        }
        std::cout << "\n";
        std::cout << "You have " << guesses << " guesses left.\n";
    }

    bool isDone() const{
        return done;
    }

    bool noGuessesLeft() const{
        return (!guesses);
    }

    void guess(const char x)
    {
        auto letter = (signed char)(tolower(x));

        if (tries & (1 << (int(letter) - 'a'))) {
            std::cout << "You have guessed this letter already.\n";
            return;
        }

        tries |= (1 << (int(letter) - 'a'));

        int found = 0, needed = int(phrase.length());
        std::for_each(phrase.begin(), phrase.end(), [&](char& c){
            if (int(c) >= 0) {
                if (tolower(c) == letter) {
                    c *= -1;
                    ++found;
                    --needed;
                } else if (c == ' ') {
                    --needed;
                }
            } else {
                --needed;
            }
        });

        if (!found) {
            --guesses;
            if (guesses) {
                std::cout << "Unlucky! That was not it, but you still have " << guesses << " guesses left.\n";
            }
            return;
        }

        if (!needed) {
            done = true;
        } else {
            printUnknownWord();
        }
    }
};

int main() {

    while (true) {
        std::cout << "Input \'q\' to end the game or any other key to start another one...\n";
        char start;
        std::cin >> start;

        if (start == 'q') {
            break;
        }

        HangMan game;
        game.initialize();
        while (true) {
            std::cout << "---------------------------\n";
            std::cout << "Instructions:\n";
            std::cout << "Press 1 for guess;\n";
            std::cout << "Press 2 for stats;\n";
            std::cout << "Press 3 for unknown word;\n";
            std::cout << "Press \'q\' to quit.\n";

            char input;
            std::cin >> input;
            if (input == 'q') {
                break;
            }

            switch (input) {
                case '1': {
                    std::cout << "Print guessed letter:\n";
                    char letter;
                    std::cin >> letter;
                    game.guess(letter);

                    break;
                }
                case '2': {
                    game.printStats();
                    break;
                }
                case '3': {
                    game.printUnknownWord();
                    break;
                }
                default: {
                    std::cout << "Command unknown.\n";
                }
            }

            if (game.isDone()) {
                std::cout << "Congratulations! You've guessed the WORD won the GAME.\n";
                game.printUnknownWord();
                break;
            } else if (game.noGuessesLeft()) {
                std::cout << "Sorry! You have used up all your guesses.\n";
                game.printUnknownWord();
                break;
            }
        }

    }

    return 0;
}
