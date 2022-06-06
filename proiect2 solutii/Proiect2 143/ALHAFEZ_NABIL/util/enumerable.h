//
// Created by Nabil Alhafez on 16.05.2022.
//

#ifndef PROIECTUL_2_ENUMERABLE_H
#define PROIECTUL_2_ENUMERABLE_H
// idUnic

class Enumerable {
private:
    static int nextId;
    int id; // id-ul unic
public:
    Enumerable() : id(nextId++) {}
    int getId(){
        return id;
    }
};
int Enumerable::nextId = 0;

#endif //PROIECTUL_2_ENUMERABLE_H
