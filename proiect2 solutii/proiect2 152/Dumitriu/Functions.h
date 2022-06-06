//
// Created by Razvan Dumitriu on 20.05.2022.
//

#ifndef SIMULARECOLOCVIU_FUNCTIONS_H
#define SIMULARECOLOCVIU_FUNCTIONS_H

#include <vector>
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
istream &operator>>(istream &is, vector<T> &vec);

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec);

template<typename T>
ostream &operator<<(ostream &os, const vector<shared_ptr<T> > &vec);
//
//template<typename T>
//ostream &operator>>(ostream &os, vector<shared_ptr<T> > &vec);

#endif //SIMULARECOLOCVIU_FUNCTIONS_H
