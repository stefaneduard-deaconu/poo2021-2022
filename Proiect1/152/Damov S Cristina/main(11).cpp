//5. HANGMAN
#include <iostream>
#include <cstring>
using namespace std;

class HangMan {
private:
    char word[30], tried[30] = " ";     //word este cuvantul secret, tried contine literele incercate
    int guessed[30] = {0}, chances;     //guess memoreaza pozitiile ghicite, chances cate incercari mai are
public:
    HangMan(char sir[30])
    {
        strcpy(word,sir);
        strupr(word);
        chances = 5;
    }
    void printUnknownWord()             //printeaza ce s-a ghicit momentan
    {
        for(int i=0; i<strlen(word); i++)
        {
            if(guessed[i] || word[i]==' ') cout<<word[i];
            else cout<<"_";
            cout<<" ";
        }
    }
    void wordUpdate()                   //adauga literele ghicite
    {
        for(int i=0; i<strlen(word); i++)
            if(strchr(tried,word[i])) guessed[i] = 1;
    }
    void printStats()                   //starea actuala
    {
        cout<<"Guess ";
        printUnknownWord();
        cout<<endl<<"Tried letters: ";
        for(int i=0; i<strlen(tried); i++)
            cout<<tried[i]<<" ";
        cout<<endl<<"You have "<<chances<<" guesses left"<<endl;
    }
    bool playerHasWon()                 //verifica daca ai castigat
    {
        for(int i=0; i<strlen(word); i++)
            if(guessed[i]==0) return 0;
        return 1;
    }
    void guess(char c)                  //incearca o litera noua
    {
        if(c>='a') c = char(c-32);         //majuscule ca sa nu diferentize literele mari de mici
        if(!strchr(tried,c))
        {
            tried[strlen(tried)+1]=NULL;
            tried[strlen(tried)]=c;
        }
        else
        {
            cout<<"you tried this letter before but ok"<<endl;
        }
        if(strchr(word,c))              //daca litera incercata este in cuvant
        {
            wordUpdate();
            if(playerHasWon()) cout<<"Congratulations! You've guessed the WORD won the GAME"<<endl;
            else cout<<"You hit the spot! Now you only have to guess "<<endl;
            printUnknownWord();
            cout<<endl<<endl;
        }
        else
        {
            cout<<"Unlucky! That was not it, but you still have "<<--chances<<" guesses left"<<endl;
        }
    }
    int getChances()
    {
        return chances;
    }
};

int main()
{
    HangMan game("Thug POO");

	game.printStats();
	game.printUnknownWord(); // Va afisa: "_ _ _ _   _ _ _"

	cout<<endl;
	game.guess('P'); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _    P _ _"
	game.guess('o'); // Va afisa: "You hit the spot! Now you only have to guess _ _ _ _   P O O"
	game.printStats();
	game.guess('z'); // "Unlucky! That was not it, but you still have 4 guesses left"


	game.guess('h');
	game.guess('u');
	game.guess('t');
	game.guess('g');
	game.guess('a');
	game.guess('a');
    cout<<game.playerHasWon(); //am pus verificarea de castigat si in functia 'guess' si apare automat si un anunt


/*
    char let;
    while(game.getChances() && !game.playerHasWon())
    {
        cout<<"introduceti o litera: ";
        cin>>let;
        cout<<let<<":"<<endl;
        game.guess(let);
    }
    if(game.getChances()==0) cout<<"you lost try again next time";
*/
	return 0;
}
