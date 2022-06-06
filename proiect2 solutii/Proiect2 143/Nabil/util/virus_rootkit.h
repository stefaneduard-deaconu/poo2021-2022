//
// Created by Nabil Alhafez on 15.05.2022.
//

#ifndef PROIECTUL_2_VIRUS_ROOTKIT_H
#define PROIECTUL_2_VIRUS_ROOTKIT_H

#include "virus_base.h"

class Rootkit : virtual public Malware {


protected:

    vector<string> importurilor, semnificative;

public:

    Rootkit() = default;

    Rootkit(const Rootkit &p) = default;

    Rootkit(
            const vector<string> &importurilor,
            const vector<string> &semnificative
    ) :
            importurilor(importurilor), semnificative(semnificative) {}

    istream &read(istream &is) override {
        Malware::read(is);

        cout << "Scrie numarul de importurilor: ";
        int n;
        string x;


        is >> n;
        if (n > 0) {
            cout << "Scrie numele de importurul: " ;
            for (int i = 0; i < n; ++i)
                is.get(), is >> x, importurilor.push_back(x);
        }


        cout << "Scrie numarul de semnificative: ";

        is >> n;
        if (n > 0) {
            cout << "Scrie numele de semnificative: " ;
            for (int i = 0; i < n; ++i)
                is.get(), is >> x, semnificative.push_back(x);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);

        cout << ", numarul de importurilor: " << importurilor.size() << endl;

        printNewLine();
        for (int i = 0; i < importurilor.size(); ++i) {
            os << "importurul " << i + 1 << ": " << importurilor[i];
            if (i < importurilor.size() - 1) {
                os << endl;
            }
        }

        cout <<endl << "numarul de semnificative: " << semnificative.size() << endl;
        printNewLine();

        for (int i = 0; i < semnificative.size(); ++i) {
            os << "semnificative " << i + 1 << ":" << semnificative[i];
            if (i < semnificative.size() - 1) {
                os << endl;
            }
        }
        printNewLine();
        return os;
    }

//    dacă se întâlnește unul din stringurile “System Service Descriptor Table”, “SSDT”, “NtCreateFile”
    int getRating() const override {

        int ratingDeBaza = Malware::getRating();
        int regula = 100;
        int res = 0;

        string import = "ntoskrnl.exe";
        vector<string> registrii = {
                "System Service Descriptor Table",
                "SSDT",
                "NtCreateFile",
        };

        vector<string> temp = this->getRegistrii();
        for (auto & reg : temp) {
            /// mai intai verific importul
            if (reg == import) {
                res += (ratingDeBaza * 2);
                continue;
            }
            /// atunci verific registrii
            for (const auto& registeru: registrii) {
                if (registeru == reg) {
                    res += regula;
                    break;
                }
            }
        }
        return res;

    }
};

#endif //PROIECTUL_2_VIRUS_ROOTKIT_H
