//
// Created by Nabil Alhafez on 15.05.2022.
//

#ifndef PROIECTUL_2_RANSOMWARE_VIRUS_H
#define PROIECTUL_2_RANSOMWARE_VIRUS_H

#include "virus_base.h"

class Ransomware : public Malware {


protected:

    int numarulDeCriptare;
    int ratingDeObfuscare;
public:
    Ransomware() = default;

    Ransomware(const Ransomware &p) = default;


    istream &read(istream &is) override {
        Malware::read(is);

        cout << "Scrie numarul de criptare: ";

        is >> numarulDeCriptare;

        cout << "Scrie numarul de obfuscare: ";

        is >> ratingDeObfuscare;

        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);
        os << ", numarul de criptare: " << numarulDeCriptare <<endl;
        printNewLine();

        os << "numarul de obfuscare: " << ratingDeObfuscare;
        printNewLine();
        return os;
    }
//    Pentru ransomware se adună ratingul de criptare cu
//    ratingul de obfuscare. Pentru orice tip de malware
//    se adună 20 dacă registrii afectați sunt “HKLM-run”
//    sau “HKCU-run”.

    int getRating() const override {
        int ratingDeBaza = Malware::getRating();
        int res = numarulDeCriptare + ratingDeObfuscare;
        res += ratingDeBaza;
        return res;
    }

};

#endif //PROIECTUL_2_RANSOMWARE_VIRUS_H
