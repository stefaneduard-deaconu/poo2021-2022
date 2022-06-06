//
// Created by Nabil Alhafez on 15.05.2022.
//

#ifndef PROIECTUL_2_VIRUS_BASE_H
#define PROIECTUL_2_VIRUS_BASE_H

#include <vector>
#include "IoBase.h"

class Malware : public IoBase {


protected:
    int ratingul;
    int zi, luna, an;
    string numele, infectare;
    vector<string> registrii;

public:
    Malware(const string &infectare = "Unknown") : infectare(infectare) {}

    Malware(const Malware &p) = default;


    Malware(int ratingul, int zi, int luna, int an, const string &numele,
            const vector<string> &registrii, const string &infectare = "Unknown") : ratingul(ratingul), zi(zi),
                                                                                    luna(luna), an(an), numele(numele),
                                                                                    infectare(infectare),
                                                                                    registrii(registrii) {}

    istream &read(istream &is) override {
        IoBase::read(is);

        cout << "Scrie ratingul virsului: ";
        is >> ratingul;

        printNewLine();

        cout << "Scrie an: ";
        is >> an;

        printNewLine();


        cout << "Scrie luna: ";
        is >> luna;

        printNewLine();


        cout << "Scrie zi: ";
        is >> zi;

        printNewLine();

        cout << "Scrie numele virsului: ";
        is.get();
        is >> numele;

        printNewLine();


        cout << "Scrie infectare daca stii, daca nu scrie n: ";
        string x;
        is >> x;
        if (x != "n" && x != "N")
            is.get(), infectare = x;


        printNewLine();

        int n;
        cout << "Scrie numarul registrii : ";
        is >> n;


//        fill(registrii.begin(), registrii.begin() + n, "");
        for (int i = 0; i < n; ++i) {
            string placeholder;
            cout << "Scrie numele de registru : ";
            is.get();
            is >> placeholder;
            registrii.push_back(placeholder);
            printNewLine();

        }
//        printNewLine();


        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        os << "ratingul: " << ratingul;
        os << ", date: " << an << "-" << luna << "-" << zi;
        os << ", numele: " << numele;
        os << ", infectare: " << infectare;
        os << ", numarul de registrii: " << registrii.size() << ", ";

//        printNewLine();
        for (int i = 0; i < registrii.size(); ++i) {
            os << "Registru " << i + 1 << ":" << registrii[i];
            if (i < registrii.size() - 1) {
                os << endl;
            }
        }
        return os;
    }

    virtual inline int getRating() const {
        int ratingDeBaza = ratingul;
        int res = ratingDeBaza;
        vector<string> tempRegistrii = {
                "HKLM-run",
                "HKCU-run"
        };
        for (auto registeru: registrii) {
            for (auto item: tempRegistrii) {
                if (registeru == item) {
                    res += 20;
                }
            }
        }
        return res;
    };

    inline vector<string> getRegistrii() const {
        return registrii;
    };

    virtual void printNewLine() const {
//        cout << endl;
    }

};

#endif //PROIECTUL_2_VIRUS_BASE_H
