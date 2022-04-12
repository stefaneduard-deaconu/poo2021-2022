#include<bits/stdc++.h>
using namespace std;

char mare(char c)
{
    if(c>='a'&&c<='z')
        c-=32;
    return c;
}

class HangMan
{
private:
    string s;
    bool fv[32];
    int g;
public:
    HangMan(string ss)
    {
        int i;
        s=ss;
        for(i=0;i<=25;i++)
            fv[i]=0;
        g=6;
    }
    void printStats()
    {
        int i;
        cout<<"Guess ";
        for(auto c:s)
        {
            if(c==' ')
                cout<<' ';
            else
            if(fv[mare(c)-'A']==0)
                cout<<'_';
            else
                cout<<mare(c);
        }
        cout<<'\n';
        cout<<"Tried letters: ";
        for(i=0;i<=25;i++)
        if(fv[i]!=0)
            cout<<(char)('A'+i);
        cout<<'\n';
        cout<<"You have "<<g<<" guesses left";
        cout<<'\n';
    }
    void printUnknownWord()
    {
        for(auto c:s)
        if(c==' ')
            cout<<' ';
        else
            cout<<'_';
        cout<<'\n';
    }
    bool playerHasWon()
    {
        for(auto c:s)
        if(c!=' '&&fv[mare(c)-'A']==0)
            return 0;
        return 1;
    }
    void guess(char l)
    {
        l=mare(l);
        if(fv[l-'A']!=0)
        {
            g--;
            cout<<"Unlucky! You already tried that letter, but you still have "<<g<<" guesses left"<<'\n';
        }
        else
        {
            for(auto c:s)
            if(mare(c)==l)
            {
                fv[l-'A']++;
                cout<<"You hit the spot! Now you only have to guess ";
                for(auto c:s)
                {
                    if(c==' ')
                        cout<<' ';
                    else
                    if(fv[mare(c)-'A']==0)
                        cout<<'_';
                    else
                        cout<<mare(c);
                }
                cout<<'\n';
                break;
            }
            if(fv[l-'A']==0)
            {
                g--;
                cout<<"Unlucky! That was not it, but you still have "<<g<<" guesses left"<<'\n';
            }
        }
        if(playerHasWon())
            cout<<"Congratulations! You've guessed the WORD and won the GAME"<<'\n';
        else
        if(g==0)
        {
            cout<<"You don't have any tries left. You lost! :(";
        }
    }
};

int main()
{

	HangMan game{"Thug POO"};

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

	game.guess('t');
	game.guess('h');
	game.guess('u');
	game.guess('g');
	// dupa ultimul apel se va afisa: "Congratulations! You've guessed the WORD won the GAME"

	// si mai puteti implementa o functie care verifica daca jocul s-a terminat:
	cout << game.playerHasWon() << endl; // va afisa 1, deoarece jucatorul a castigat

    return 0;
}
