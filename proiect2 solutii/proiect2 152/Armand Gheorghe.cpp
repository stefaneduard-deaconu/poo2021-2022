#include<bits/stdc++.h>
using namespace std;

class malware
{
protected:
    int rating;
public:
    malware()=default;
    friend istream &operator>>(istream &is,malware &m)
    {
        cout<<"introdu rating ";
        is>>m.rating;
    }
    virtual double calc_rating();
};

double malware::calc_rating() {
    return rating;
}

class rootkit: virtual public malware
{
private:
    string nume;
public:
    rootkit()=default;
    friend istream &operator>>(istream &is,rootkit &r)
    {
        cout<<"introdu rating ";
        is>>r.rating;
        cout<<"introdu nume ";
        is>>r.nume;
    }
    virtual double calc_rating();
};

double rootkit::calc_rating(){
    double sum = malware::calc_rating();
    if(nume.size()==1)
        sum+=100;
    return sum;
}

class computer
{
private:
    static int nr,infectati;
    int id;
    double rating;
    vector<shared_ptr<malware>>v;
public:
    computer()
    {
        nr++;
        id=nr;
        v={};
    }
    static double infectpercent()
    {
        return (double)infectati/nr*100;
    }
    friend istream &operator>>(istream &is,computer &c)
    {
        int x;
        cout<<"1. o varianta";
        while(1)
        {
            cout<<"alege o optiune";
            is>>x;
            if(x==1)
            {
                rootkit virus;
                is>>virus;
                c.v.push_back(make_shared<rootkit>(virus));
            }
            else
                break;
        }
    }
    bool operator < (const computer &other) const{return rating < other.rating;}
};

int computer::nr, computer::infectati;

class meniu_baza
{
public:
    virtual void list_options(){};
    virtual int alege(int first, int last){};
    virtual void mainloop(){};
};

class meniu_util:meniu_baza
{
private:
    vector<computer>computere;
public:
    void list_options() override
    {
        cout<<"1. Adauga nu stiu ce";
    }
    int alege(int first,int last) override
    {
        cout<<"Alegeti optiunea: ";
        int x;
        cin>>x;
        if(x>=first&&x<=last)
            return x;
        return -1;
    }
    void mainloop() override
    {
        while(1)
        {
            list_options();
            int x=alege(1,6);
            if(x==1)
            {
                computer c;
                cin>>c;
                computere.push_back(c);
            }
            else
            if(x==2)
            {
                cout<<computer::infectpercent();
            }
            else
            {
                break;
            }
        }
    }
};

int main()
{
    meniu_util menu;
    menu.mainloop();
    return 0;
}
