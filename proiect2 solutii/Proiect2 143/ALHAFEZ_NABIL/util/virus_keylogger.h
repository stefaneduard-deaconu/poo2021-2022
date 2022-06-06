//
// Created by Nabil Alhafez on 15.05.2022.
//

#ifndef PROIECTUL_2_VIRUS_KEYLOGGER_H
#define PROIECTUL_2_VIRUS_KEYLOGGER_H

#include "virus_rootkit.h"

class Keylogger : virtual public Malware {


protected:

    vector<string> tastele, funcțiileFolosite;

public:
    Keylogger() = default;

    Keylogger(const Keylogger &p) = default;

    Keylogger(
            const vector<string> &funcțiileFolosite,
            const vector<string> &tastele
    ) :
            funcțiileFolosite(funcțiileFolosite), tastele(tastele) {}

    istream &read(istream &is) override {
        Malware::read(is);

        cout << "Scrie numarul de tastele: ";
        int n;
        string x;

        is >> n;

        if (n) {
            cout << "Scrie numele de tastea: " << endl;
            for (int i = 0; i < n; ++i)
                is.get(), is >> x, tastele.push_back(x);

        }
        cout << "Scrie numarul de funcțiileFolosite: ";

        is >> n;
        if (n) {
            cout << "Scrie numele de funcția: " << endl;
            for (int i = 0; i < n; ++i)
                is.get(), is >> x, funcțiileFolosite.push_back(x);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Malware::write(os);

        cout << ", numarul de importurilor: " << tastele.size() << endl;

        printNewLine();
        for (int i = 0; i < tastele.size(); ++i) {
            os << "importurul " << i + 1 << ": " << tastele[i];
            if (i < tastele.size() - 1) {
                os << endl;
            }
        }

        cout << endl << "Numarul de funcțiileFolosite: " << funcțiileFolosite.size() << endl;
        printNewLine();

        for (int i = 0; i < funcțiileFolosite.size(); ++i) {
            os << "semnificative " << i + 1 << ":" << funcțiileFolosite[i];
            if (i < funcțiileFolosite.size() - 1) {
                os << endl;
            }
        }
        printNewLine();
        return os;
    }

//    dacă se întâlnește unul din stringurile “System Service Descriptor Table”, “SSDT”, “NtCreateFile”
    int getRating() const override {

        int ratingDeBaza = Malware::getRating();
        int regula_10 = 10;
        int regula_30 = 30;
        int res = ratingDeBaza;

        vector<string> registrii_10 = {
                "Up",
                "Num Lock",
                "Down",
                "Right",
                "Left",
                "PageDown",
        };

        vector<string> registrii_30 = {
                "CreateFileW",
                "OpenProcess",
                "ReadFile",
                "WriteFile",
                "RegisterHotKey",
                "SetWindowsHookEx",
        };

        vector<string> temp = this->getRegistrii();
        for (auto &reg: temp) {
            /// mai intai verific registrii_10
            for (const auto &registeru: registrii_10) {
                if (registeru == reg) {
                    res += regula_10;
                    break;
                }
            }
            /// atunci verific registrii_30
            for (const auto &registeru: registrii_30) {
                if (registeru == reg) {
                    res += regula_30;
                    break;
                }
            }
        }
        return res;

    }

};

#endif //PROIECTUL_2_VIRUS_KEYLOGGER_H
