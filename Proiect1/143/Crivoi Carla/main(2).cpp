#include <iostream>
#include <string>

using namespace std;

class Crypt{
private:
    string parola;
public:
    Crypt(){
    parola="";
    }
    Crypt(string _parola){
    parola=_parola;
    }
    void CitireParola(){
        getline(cin,parola);
        setParola(parola);
    }
    void setParola(string _parola){
    parola=_parola;
    }
    string getParola(){
    return parola;
    }
    int getDimesiune(){
    return parola.size();
    }

    string encrypt(string mesaj)
    {
        int j=0;
        for(int i=0;i<(int) mesaj.size();i++)
        {
            mesaj[i]=mesaj[i]^parola[j];
            j++;
            if(j==(int) parola.size()) j=0;
        }
        return mesaj;
    }

};

class CryptedConversation{
private:
    string conversatie[100001];
    Crypt key;
    int n;
public:
    CryptedConversation(){
        key.setParola("");
        n=0;
    }
    CryptedConversation(Crypt _key){
        key=_key;
        n=0;
    }
    void addMessage(string mesaj){
        conversatie[n]=key.encrypt(mesaj);
        n++;
    }
    void show(int i, int j=-1){
        if(i>n) cout<<"Exista doar "<<n<<", mesaje salvate."<<endl;
        else {
            if(j==-1) j=i+1;
            else if(j>n)
            {
                j=n;
                cout<<"Exista mesaje doar pana la "<<n<<'.'<<endl;
            }
            while(i<j)
            {
                cout<<key.encrypt(conversatie[i])<<endl;
                i++;
            }
        }

    }
    void updateKey(string _key){
        for(int i=0;i<n;i++)
        {
            conversatie[i]=key.encrypt(conversatie[i]);
        }
        key.setParola(_key);
        for(int i=0;i<n;i++)
        {
            conversatie[i]=key.encrypt(conversatie[i]);
        }
    }
    string getMessCrypt(int i){
        return conversatie[i];
    }

};

int main()
{
   Crypt crypt("POO justice");
   string mesaj="Happy";
   string criptat=crypt.encrypt(mesaj);
   cout<<mesaj<<" POO justice "<<criptat<<endl;
   CryptedConversation conversation(crypt);
   conversation.addMessage("Salutare! Cand urmeaza sa ne auzim?");
   conversation.addMessage("Cat de curand... stai o clipa");

    conversation.addMessage("-Knock knock!");
    conversation.addMessage("-Who's there?");
    conversation.addMessage("-Daisy");
    conversation.addMessage("-Daisy who?");
    conversation.addMessage("-DAISY ME ROLLING!");
    conversation.show(0);
    conversation.show(9);
    conversation.show(2,7);
    conversation.show(2,10);
    cout<<conversation.getMessCrypt(0)<<endl;
    conversation.updateKey("Kee");
     cout<<conversation.getMessCrypt(0)<<endl;
    conversation.show(0,7);


    return 0;
}
