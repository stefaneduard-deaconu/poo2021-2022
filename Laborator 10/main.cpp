// 1. Singleton Menu

//
class SingletonSimplu {
    // O clasa din care putem avea un singur obiect la un moment dat.

    // 1. constructorii devin private
private:
    SingletonSimplu() {

    }
    // pai daca ctr. e private, avem nevoie de ceva care ne returneaza obiectul.
    // Cum este unic, poate fi statica functia

public:
    // 3. ca sa retinem obiectul, avem variabila statica
    static SingletonSimplu* instance;
    static SingletonSimplu* getInstance() {
        // daca deja exista obiectul, il returnam
        if (instance != nullptr) {
            return instance;
        }
        instance = new SingletonSimplu();
        return instance;
    }
};
SingletonSimplu* SingletonSimplu::instance = nullptr;


// Design pattern
// Cerinta: integrati regulile (ctr. private, var. statica si metoda pentru a lua instanta) in meniul interactiv de tip CRUD

//int main() {
//    SingletonSimplu* s = SingletonSimplu::getInstance();
//    s.mainloop();
//    delete SingletonSimplu::instance;
//}

// idUnic

class Enumerable {
private:
    static nextId;
    int id; // id-ul unic
public:
    Enumerable() : id(nextId++) {}
};
int Enumerable::nextId = 0;
