//
// Created by victo on 19.05.2022.
//

#ifndef PROIECT2_IOBASE_H
#define PROIECT2_IOBASE_H
#include <iostream>

using namespace std;
class IOBase{
public:
    virtual istream &read(istream &is){
        return is;
    }
    virtual ostream &write (ostream &os) const {
        return os;
    }

    friend ostream &operator<<(ostream &os,const IOBase &base) {
        return base.write(os);
    }
    friend istream &operator>>(istream &is, IOBase &base) {
        return base.read(is);
    }


};

#endif //PROIECT2_IOBASE_H
