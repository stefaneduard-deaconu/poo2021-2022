//
// Created by Nabil Alhafez on 16.05.2022.
//

#ifndef PROIECTUL_2_VIRUS_KERNEL_KEYLOGGER_H
#define PROIECTUL_2_VIRUS_KERNEL_KEYLOGGER_H


#include "virus_base.h"
#include "virus_rootkit.h"
#include "virus_keylogger.h"

class KernelKeylogger : public Rootkit, public Keylogger {


protected:

    bool isHidingFiles;
    bool isHidingRegisters;

public:

    KernelKeylogger() = default;

    KernelKeylogger(const KernelKeylogger &p) = default;

    KernelKeylogger(bool isHidingFiles, bool isHidingRegisters) : isHidingFiles(isHidingFiles),
                                                                  isHidingRegisters(isHidingRegisters) {}

    KernelKeylogger(const vector<string> &importurilor, const vector<string> &semnificative,
                    const vector<string> &funcțiileFolosite, const vector<string> &tastele, bool isHidingFiles,
                    bool isHidingRegisters) : Rootkit(importurilor, semnificative),
                                              Keylogger(funcțiileFolosite, tastele), isHidingFiles(isHidingFiles),
                                              isHidingRegisters(isHidingRegisters) {}

    istream &read(istream &is) override {
        Rootkit::read(is);
        Keylogger::read(is);

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
        Rootkit::write(os);
        Keylogger::write(os);

        cout << ", numarul de tastele: " << tastele.size() << endl;

        printNewLine();
        for (int i = 0; i < tastele.size(); ++i) {
            os << "importurul " << i + 1 << ":" << tastele[i];
            if (i < tastele.size() - 1) {
                os << endl;
            }
        }

        cout  << endl  <<"numarul de funcțiileFolosite: " << funcțiileFolosite.size() << endl;
        printNewLine();

        for (int i = 0; i < funcțiileFolosite.size(); ++i) {
            os << "Functia " << i + 1 << ":" << funcțiileFolosite[i];
            if (i < funcțiileFolosite.size() - 1) {
                os << endl;
            }
        }
        printNewLine();
        return os;
    }

    int getRating() const override {
        int ratingRootKit = Rootkit::getRating();
        int keyloggerRootKit = Keylogger::getRating();
        int res = ratingRootKit + keyloggerRootKit;
        if (isHidingFiles)
            res += 20;
        if (isHidingRegisters)
            res += 30;
        return res;
    }


};


#endif //PROIECTUL_2_VIRUS_KERNEL_KEYLOGGER_H
