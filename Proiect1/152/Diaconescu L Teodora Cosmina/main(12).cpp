#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class HangMan
{
private:
    char cuv[255];
    char form[255];
    char let[100];
    int ctlet = 0;
    int nr = 8;
    int vieti = 6;
    char aleg[30][255]= {"Ana are mere", "De ce informatica", "Ne place info", "Echipa calusarii", "Minam Bitcoin", "Programare", "Baze de date", "De ce doamne"};

public:
    bool rez = 0;
    /// Constructori- cuvant random/cuvant preales
    HangMan()
    {
        srand(time(NULL));
        int x = rand()%nr;
        strcpy(cuv, aleg[x]);
        /*for(int i=0; i<strlen(cuv); i++)
            cout<<cuv[i];
        cout<<'\n';*/
        Init();
    }
    HangMan(char t[])
    {
        strcpy(cuv, t);
        Init();
    }

    void Init()
    {
        int n = strlen(cuv);
        for(int i = 0; i<n; i++)
        {
            if(cuv[i] == ' ' || cuv[i] == '.' || cuv[i] == '!' || cuv[i] == '?' || cuv[i] == ',' || cuv[i] == '-')
                form[i] = cuv[i];
            else form[i]='_';
        }
        form[n]='\0';
    }

    ///Functii pt joc
    void printStats()
    {
        cout<<"Guess ";
        for(int i = 0; i<strlen(cuv); i++)
        {
            cout<<form[i]<<' ';
        }
        cout<<"\nTried letters: ";
        for(int i = 0; i < ctlet; i++)
        {
            cout<<let[i]<<' ';
        }
        cout<<'\n';
        cout<<"You have "<<vieti<<" guesses left.\n";
    }
    void printUnknownWord()
    {
        for(int i = 0; i<strlen(cuv); i++)
        {
            cout<<form[i]<<' ';
        }
        cout<<'\n';
    }
    void guess(char p)
    {
        if(vieti == 0)
        {
            Ies();
            return;
        }
        bool ok = 0, o = 1;
        let[ctlet++] = p;
        for(int i = 0; i<strlen(cuv); i++)
        {
            if(tolower(p) == tolower(cuv[i]))
            {
                ok=1;
                form[i]=cuv[i];
            }
            if(form[i] == '_') o = 0;
        }
        if(ok == 0)
        {
            if(vieti == 1)
            {
                --vieti;
                cout<<"Unlucky! ";
                rez = 1;
                Ies();
                return;
            }
            cout<<"Unlucky! That was not it, but you still have ";
            cout<<--vieti;
            cout<<" guesses left\n";
        }
        else
        {
            if(o == 0)
            {
                cout<<"You hit the spot! Now you only have to guess ";
                for(int i = 0; i<strlen(cuv); i++)
                {
                    cout<<form[i]<<' ';
                }
                cout<<'\n';
            }
            else
            {
                vieti = 0;
                Ies();
                for(int i = 0; i<strlen(cuv); i++)
                {
                    cout<<form[i];
                }
                cout<<'\n';
            }
        }
    }
    void Ies()
    {
        if(rez==1) cout<<"You have no lives left!\n";
        else cout<<"Congratulations! You've guessed the WORD won the GAME\n";
        rez = 1;
    }
};

int main()
{
    HangMan I;
    I.printStats();
    bool ok = 1;
    char p;
    while(I.rez == 0)
    {
        cin>>p;
        I.guess(p);
        I.printStats();
    }
    return 0;
}
