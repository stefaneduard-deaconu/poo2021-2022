//
// Created by visan on 5/3/22.
//

#ifndef COLOCVIU_COMPUTER_H
#define COLOCVIU_COMPUTER_H

#include"IoBase.h"
#include"Malware.h"
#include<memory>

class Computer : public IoBase {
private:
    //The number of computers.
    static unsigned num_computers;

    unsigned id;

    vector<shared_ptr < Malware>> malware;

public:
    Computer() : id(num_computers) {
        num_computers++;
    }

    istream &read(istream &is) override {
        int num_malware, type;
        std::cout << "Enter the malware count: ";
        is >> num_malware;
        malware.resize(num_malware);
        for (int i = 0; i < num_malware; i++) {
            cout << "1. Rootkit" << endl;
            cout << "2. Keylogger" << endl;
            cout << "3. Kernel-Keylogger" << endl;
            cout << "4. Ransomware" << endl;
            is >> type;

            if (type == 1) {
                malware[i] = std::make_shared<RootKit>();
            } else if (type == 2) {
                malware[i] = std::make_shared<KeyLogger>();
            } else if (type == 3) {
                malware[i] = std::make_shared<KernelKeylogger>();
            } else if (type == 4) {
                malware[i] = std::make_shared<Ransomware>();
            }
            cin >> *malware[i];

        }
        return is;
    }

    ostream &write(ostream &os) const override {
        os << "Id: " << id << endl;
        os << "Malware: ";
        for (const std::shared_ptr<Malware> &x: malware) {
            std::cout << *x << endl;
        }
        os << endl;
        os << "Rating: " << final_rating() << endl;
        return os;
    }

    double final_rating() const {
        double result = 0;
        for (const std::shared_ptr<Malware> &x: malware) {
            result += x->impact();
        }
        return result;
    }

    bool infected() const {
        return !malware.empty();
    }
};

unsigned Computer::num_computers = 0;

#endif //COLOCVIU_COMPUTER_H
