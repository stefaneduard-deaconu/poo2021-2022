//
// Created by Nabil Alhafez on 15.05.2022.
//

#ifndef PROIECTUL_2_COMPUTER_H
#define PROIECTUL_2_COMPUTER_H

#include "IoBase.h"
#include "virus_base.h"
#include "virus_rootkit.h"
#include "virus_keylogger.h"
#include "ransomware_virus.h"
#include "virus_kernel_keylogger.h"

class Computer : public IoBase {
protected:
    vector<shared_ptr<Malware> > malwares;
    int id;

public:

    Computer() = default;

    Computer(const Computer &p) = default;

    Computer(const vector<shared_ptr<Malware>> &malwares, int id) : malwares(malwares), id(id) {}

    istream &read(istream &is) override {
        IoBase::read(is);

        cout << "Scrie numarul de malwares: ";

        shared_ptr<Malware> m;
        int n;
        is >> n;

        for (int i = 0; i < n; ++i) {
            switch (getUserOption()) {

                case 1:
                    m = make_shared<Rootkit>();
                    break;

                case 2:
                    m = make_shared<Keylogger>();
                    break;

                case 3:
                    m = make_shared<KernelKeylogger>();
                    break;

                case 4:

                case 5:
                    return is;


                default:
                    m = make_shared<Ransomware>();
                    break;

            }
            is >> *m;
            malwares.push_back(m);
            cout << *m <<endl;
        }

        return is;

    }

    ostream &write(ostream &os) const override {

        IoBase::write(os);
        for (auto malware: malwares) {
            cout << "malware is " << *malware;
            cout << endl;
        }
        return os;

    }

public:

    void setId(int id) {
        this->id = id;
    }

    int getUserOption() {
        int optione;
        do {
            cout << endl;
            cout << "Ce malware avem, te rog frumos scrie o optine" << endl;
            cout << "1- Rootkit" << endl;
            cout << "2- Keylogger" << endl;
            cout << "3- Kernel Keylogger" << endl;
            cout << "4- Ransomware" << endl;
            cout << "5- Exit" << endl;
            cin >> optione;
        } while (optione > 4 || optione < 1 || optione == 5);
        return optione;

    }

    double afisatRatingFinal() {
        int count = 0;

        for (auto mal: malwares)
            count += (mal->getRating());

        cout << "Rating Final: " << endl;
        cout << count / malwares.size() << endl;
    }

};


#endif //PROIECTUL_2_COMPUTER_H
