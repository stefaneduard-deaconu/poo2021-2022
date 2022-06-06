#include <iostream>
#include <vector>
using namespace std;

void printBinary(char c)
{
    for(int i = 7; i >= 0; -- i)
        cout<<(((1<<i)&c) != 0);
}
class Crypt
{
private:
    string key;
public:
    Crypt() {}
    Crypt(string key)
    {
        this->key = key;
    }

    string Encrypt(string original)
    {
        string encrypted = original;
        for(int i = 0; i < original.size(); ++ i)
            encrypted[i] = original[i] ^ key[i % key.length()];
        return encrypted;
    }

    void updateKey(string newKey)
    {
        key = newKey;
    }
};

class EncryptedConversation
{
private:
    vector<string> lines;
    Crypt crypt;
public:
    EncryptedConversation() {}
    EncryptedConversation(Crypt crypt)
    {
        this->crypt = crypt;
    }
    void addMessage(string message)
    {
        lines.push_back(crypt.Encrypt(message));
    }
    void show(int x)
    {
        cout<<crypt.Encrypt(lines[x])<<'\n';
    }
    void show(int st, int en)
    {
        for(int i = st; i < en; ++ i)
            cout<<crypt.Encrypt(lines[i])<<'\n';
    }
    void updateKey(string newKey)
    {
        for(int i = 0; i < lines.size(); ++ i)
            lines[i] = crypt.Encrypt(lines[i]);
        crypt.updateKey(newKey);
        for(int i = 0; i < lines.size(); ++ i)
            lines[i] = crypt.Encrypt(lines[i]);
    }
};
int main()
{
    EncryptedConversation conversation(Crypt("Ch3i3"));
    conversation.addMessage("Salutare! Cand urmeaza sa ne auzim?");
    conversation.addMessage("Cat de curand.. stai o clipa");

    conversation.addMessage("-Knock knock!");
    conversation.addMessage("-Who's there?");
    conversation.addMessage("-Daisy");
    conversation.addMessage("-Daisy who?");
    conversation.addMessage("-DAISY ME ROLLING!");

    conversation.show(0);
    conversation.show(2, 7);

    conversation.updateKey("Kee");

    conversation.show(0);
    conversation.show(2, 7);
    return 0;
}
