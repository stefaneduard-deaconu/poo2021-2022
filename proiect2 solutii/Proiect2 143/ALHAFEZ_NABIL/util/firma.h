//
// Created by Nabil Alhafez on 15.05.2022.
//

#ifndef PROIECTUL_2_FIRMA_H
#define PROIECTUL_2_FIRMA_H

#include "IoBase.h"
#include "computer.h"
#include "enumerable.h"

class Firma : public IoBase {
protected:
    vector<Computer> computers;

public:

    Firma() = default;

    Firma(const Firma &p) = default;


    istream &read(istream &is) override {
        IoBase::read(is);

        string numele;

        cout << "Scrie numele de Firma: " << endl;

        cin >> numele;

        cout << "Scrie numarul de computers: " << endl;


        int n;
        is >> n;
        Computer computer;
        for (int i = 0; i < n; ++i) {
            computer.setId(Enumerable().getId());
            cin >> computer;
            computers.push_back(computer);
            cout << endl;
        }
        return is;

    }

    ostream &write(ostream &os) const override {

        IoBase::write(os);

        cout << "numarul de computers: " << computers.size() << endl;


        os << "Computer estes : " << endl;
        for (int i = 0; i < computers.size(); ++i)
            os << computers[i] << endl;
        return os;

    }


};

#endif //PROIECTUL_2_FIRMA_H
