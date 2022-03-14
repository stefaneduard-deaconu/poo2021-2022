#include <bits/stdc++.h>
#include <ostream>

using namespace std;

//int sum(int a, int b) {
//    return a + b;
//}
//
//int sum(int a, int b, int c) {
//    return a + b + c;
//}
//
//// RASPUNS:
//double sum(double a, double b) {
//    return a + b;
//}
//// apelul sum(2.3, 14) nu va functiona. Puteti rula ca sa vedeti. Care pare sa fie motivul?
//
//int main() {
//    // afiseaza 5
//    cout << "a) " << sum(2, 3) << '\n';
//    // afiseaza 14
//    cout << "b) " << sum(3, 5, 6) << '\n';
//
//    // TODO urmatorul cod afiseaza 16. Ce puteti adauga in program a.i. sa afiseze 16.3?
//    cout << "c) " << sum(2.3, 14.0) << '\n';
//
//    return 0;
//}

//class Fraction {
//
//};
//
//class LongNumber {
//
//};
//
//LongNumber add(LongNumber a, LongNumber b) {
//    // ...
//}
//
//LongNumber add(Fraction f1, Fraction f2) {
//    // ...
//}
//
//void afisare(LongNumber num){
//    // ...
//}
//
//void afisare(Fraction f){
//    // ...
//}
//
//int main() {
//    int cifreA[12] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1},
//            cifreB[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2}
//    LongNumber a(12, cifreA), b(12, cifreB), c;
//    Fraction f1(12, 5), f2(3, 5), f3;
//
//
//    c = add(a, b);
//    f3 = add(f1, f2);
//
//    afisare(c); // 121932631138190824432332
//    afisare(f3); // 3/1
//}


// exemplu operatori

//class Fraction {
//    // ...
//private:
//    int a, b;
//public:
//    Fraction();
//
//    Fraction(int a, int b);
//
//    Fraction operator+(const Fraction &f) {
//        // adunam this cu f2, adica a/b cu f.a/f.b
//        return Fraction(
//                a * f.b + b * f.a,
//                b * f.b
//        );
//    }
//
//    friend Fraction operator+(const Fraction &f1, const Fraction &f2);
//
//    friend ostream &operator<<(ostream &os, const Fraction &fraction);
//    friend istream &operator<<(istream &is, Fraction &fraction);
//
//
//
//};
//
//Fraction operator+(const Fraction &f1, const Fraction &f2) {
//    return Fraction(
//            f1.a * f2.b + f1.b * f2.a,
//            f1.b * f2.b
//    );
//}
//
//Fraction::Fraction(int a, int b) : a(a), b(b) {}
//
//Fraction::Fraction() : a(0), b(1) {}
//
//ostream &operator<<(ostream &os, const Fraction &fraction) {
//    os << "a: " << fraction.a << " b: " << fraction.b;
//    return os;
//}
//
//istream &operator<<(istream &is, Fraction &fraction) {
//    // în schimb, înainte de citire vom afișa numele datelor citite:
//    cout << "a: ";
//    is >> fraction.a;
//    cout << " b: ";
//    is >> fraction.b;
//    return is;
//}
//
//// operatori de citire și scriere
//
//
//int main() {
//    Fraction f1(2, 3), f2(3, 2), suma;
//
////    suma = add(f1, f2);
//    suma = f1 + f2;
//
//    return 0;
//}

// ex. 2
/*
Chitanta renovare:
1. Cuie (buc) x 10
   10 x 0.20 = 2.00 RON
2. Lavabila (galeata) x 3
   3 x 37.12 = 104.36 RON
3. PAL (buc) x 5
   5 x 12.00 = 60.00 RON
---
   Total: 162.36 RON
 */

