#include <bits/stdc++.h>

using namespace std;
const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
const double  epsilon = 1.0e-5;

class Angle{
private:
    int grade, minute, secunde;
public:
    Angle(){
        grade=minute=secunde=0;
    }
    Angle(int g, int m, int s){
        grade=g;
        minute=m;
        secunde=s;
    }

    Angle(double x){
        grade = 57.30*x;
        minute=secunde=0;
    }

    void print(){
        cout<<grade<<" grade "<<minute<<" minute "<<secunde<<" secunde "<<endl;
    }

    void citesteAngle(){
        cin>>grade>>minute>>secunde;
    }
    int getGrade(){
        return grade;
    }
    int getMinute(){
        return minute;
    }
    int getSecunde(){
        return secunde;
    }
    double radians(){
        float x = grade + (float)minute/60 + (float)secunde/3600;
        x = x*PI/180;
        return x;
    }

    double cos();
    double sin();
};

double Angle::cos(){
    double  x = radians();
    if(abs(x - PI / 2) <= epsilon)
        return 0;
    else return std::cos(x);
}
double Angle::sin(){
    double  x = radians();
    if(abs(x - PI ) <= epsilon)
        return 0;
    else return std::sin(x);
}



Angle comparaUnghiuri(Angle a1, Angle a2, Angle a3){
    Angle a12MIN, a123MIN;
    if(a1.getGrade() < a2.getGrade())
        a12MIN = a1;
    else if (a1.getGrade() == a2.getGrade() && a1.getMinute() < a2.getMinute())
        a12MIN = a1;
    else if(a1.getGrade() == a2.getGrade() && a1.getMinute() == a2.getMinute() && a1.getSecunde() < a2.getSecunde())
        a12MIN = a1;
    else
        a12MIN = a2;
    if(a12MIN.getGrade() < a3.getGrade())
        a123MIN = a12MIN;
    else if (a12MIN.getGrade() == a3.getGrade() && a12MIN.getMinute() < a3.getMinute())
        a123MIN = a12MIN;
    else if(a12MIN.getGrade() == a3.getGrade() && a12MIN.getMinute() == a3.getMinute() && a12MIN.getSecunde() < a3.getSecunde())
        a123MIN = a12MIN;
    else
        a123MIN = a3;
    return a123MIN;
}

Angle aduna(Angle a1, Angle a2) {
    int g_a3, min_a3, sec_a3;
    g_a3 = a1.getGrade() + a2.getGrade();

    if(a1.getMinute() + a2.getMinute() >= 60){
        g_a3++;
        min_a3 = a1.getMinute() + a2.getMinute() - 60;
    }
    else
        min_a3 = a1.getMinute() + a2.getMinute();

    if(a1.getSecunde() + a2.getSecunde() >= 60){
        min_a3++;
        sec_a3 = a1.getSecunde() + a2.getSecunde() - 60;
    }
    else
        sec_a3 = a1.getSecunde() + a2.getSecunde();

    return Angle(g_a3, min_a3, sec_a3);
}

class Triunghi{
private:
    Angle u1, u2, u3;
public:
    Triunghi(){}

    Triunghi(Angle a1, Angle a2, Angle a3){
        u1 = a1;
        u2 = a2;
        u3 = a3;
    }

    void rezolva(int x){
        cout<<"1. Unghiul care se opune celei mai mici laturi este: ";
        comparaUnghiuri(u1, u2, u3).print();
        //2 cu teorema sinusurilor u1 e cel mai mic unghi si x cea mai mica latura
        double y,z;
        Angle minim=comparaUnghiuri(u1, u2, u3);
        if(minim.getGrade() == u1.getGrade() && minim.getMinute() == u1.getMinute() && minim.getSecunde()==u1.getSecunde()){
            y = u2.sin()*x/u1.sin();
            z = u3.sin()*x/u1.sin();
        }
        if(minim.getGrade() == u2.getGrade() && minim.getMinute() == u2.getMinute() && minim.getSecunde()==u2.getSecunde()){
            y = u1.sin()*x/u2.sin();
            z = u3.sin()*x/u2.sin();
        }
        if(minim.getGrade() == u3.getGrade() && minim.getMinute() == u3.getMinute() && minim.getSecunde()==u3.getSecunde()){
            y = u2.sin()*x/u3.sin();
            z = u1.sin()*x/u3.sin();
        }
        cout<<"2. Lungimile tuturor laturilor sunt: "<< x <<" "<<y<<" "<<z<<endl;
        cout<<"3. Aria triunghiului este: "<<minim.sin()*y*z/2<<endl;
        if (u1.getGrade() < 90 && u2.getGrade() < 90 && u3.getGrade() < 90)
            cout<<"4. Triunghiul este ascutit unghic.";
        else
            cout<<"4. Triunghiul NU este ascutitunghic.";
    }
};

int main(){
    Angle a1(23, 30, 10);
    Angle a2(PI/2);
    Angle a3 = aduna(a1, a2);
    a3.print();
    cout<<a3.radians()<<endl;
    cout<<a2.cos()<<endl;
    Triunghi T(Angle(30, 0, 0), Angle(60, 0, 0), Angle(90, 0, 0));
    T.rezolva(10);
}