#include  <bits/stdc++.h>
using namespace std;
ifstream f("simulare.in");
ofstream g("simulare.out");

class malware{
protected:
    int impact,zi,luna,an;
    string nume,metoda;
    vector <string> registrii;
public:
    malware(int z,int l,int a,string name,string method,vector <string> reg)
    {
        metoda="Unknown";
        zi=z;
        luna=l;
        an=a;
        nume=name;
        metoda=method;
        registrii=reg;
    }
    malware()
    {
        impact=0;
        zi=0;
        luna=0;
        an=0;
        metoda="Unknown";
    }
    void print()
    {
        g<<"Nume: "<<nume<<"\nMetoda infectare: "<<metoda<<'\n';
    }
    int af_impact()
    {
        return impact;
    }
};

class Rootkit: public malware
{
protected:
    vector <string> imprturi, stringuri;
public:
    Rootkit(int z, int l, int a, string name, string method, vector<string> reg, vector<string> imp, vector<string> stri)
    {
        zi=z;
        luna=l;
        an=a;
        nume=name;
        metoda=method;
        registrii=reg;
        impact=0;

        imprturi=imp;
        stringuri=stri;

        string test1,test2;
        test1="HKLM-run";
        test2="HKCU-run";
        int ok=0;
        for(int i=0; i<registrii.size(); i++)
        {
            if(registrii[i]==test1||registrii[i]==test2) ok=1;
        }
        if(ok) impact+=20;

        string test3;
        test1="System Service Descriptor Table";
        test2="SSDT";
        test3="NtCreateFile";

        ok=0;
        for(int i=0; i<stringuri.size(); i++)
        {
            if(stringuri[i]==test1||stringuri[i]==test2||stringuri[i]==test3) ok=1;
        }
        if(ok) impact+=100;



        test1="ntoskrnl.exe";
        ok=0;
        for(int i=0; i<imprturi.size(); i++)
        {
            if(imprturi[i]==test1) ok=1;
        }
        if(ok) impact*=2;
    }
    Rootkit()
    {
        zi=0;
        luna=0;
        an=0;
        impact=0;
    }
};

class Keylogger:public malware
{
protected:
    vector <string> functii, taste;
public:
    Keylogger(int z, int l, int a, string name, string method, vector<string> reg, vector<string> fun, vector<string> tst)
    {
        zi=z;
        luna=l;
        an=a;
        nume=name;
        metoda=method;
        registrii=reg;
        impact=0;

        functii=fun;
        taste=tst;


        string test1,test2;
        test1="HKLM-run";
        test2="HKCU-run";
        int ok=0;
        for(int i=0; i<registrii.size(); i++)
        {
            if(registrii[i]==test1||registrii[i]==test2) ok=1;
        }
        if(ok) impact+=20;

        string test3,test4,test5,test6,test7;
        test1="[Up]";
        test2="[Num Lock]";
        test3="[Down]";
        test4="[Right]";
        test5="[UP]";
        test6="[Left]";
        test7="[PageDown]";
        for(int i=0; i<taste.size(); i++)
        {
            if(taste[i]==test1||taste[i]==test2||taste[i]==test3||taste[i]==test4||taste[i]==test5||taste[i]==test6||taste[i]==test7)
                impact+=10;
        }

        test1="CreateFileW";
        test2="OpenProcess";
        test3="ReadFile";
        test4="WriteFile";
        test5="RegisterHotKey";
        test6="SetWindowsHookEx";
        for(int i=0; i<functii.size(); i++)
        {
            if(functii[i]==test1||functii[i]==test2||functii[i]==test3||functii[i]==test4||functii[i]==test5||functii[i]==test6)
                impact+=30;
        }
    }
    Keylogger()
    {
        zi=0;
        luna=0;
        an=0;
        impact=0;
    }
};

class Kernel_keylogger:public malware
{
protected:
    vector <string> imprturi, stringuri, functii, taste;
    bool ascunde_r, ascunde_f;
public:
    Kernel_keylogger(int z, int l, int a, string name, string method, vector<string> reg, vector<string> imp, vector<string> stri, vector<string> fun, vector<string> tst, bool ascr, bool ascf)
    {
        zi=z;
        luna=l;
        an=a;
        nume=name;
        metoda=method;
        registrii=reg;
        impact=0;

        functii=fun;
        taste=tst;
        imprturi=imp;
        stringuri=stri;
        ascunde_r=ascr;
        ascunde_f=ascf;


        string test1,test2;
        test1="HKLM-run";
        test2="HKCU-run";
        int ok=0;
        for(int i=0; i<registrii.size(); i++)
        {
            if(registrii[i]==test1||registrii[i]==test2) ok=1;
        }
        if(ok) impact+=20;

        string test3,test4,test5,test6,test7;
        test1="[Up]";
        test2="[Num Lock]";
        test3="[Down]";
        test4="[Right]";
        test5="[UP]";
        test6="[Left]";
        test7="[PageDown]";
        for(int i=0; i<taste.size(); i++)
        {
            if(taste[i]==test1||taste[i]==test2||taste[i]==test3||taste[i]==test4||taste[i]==test5||taste[i]==test6||taste[i]==test7)
                impact+=10;
        }

        test1="CreateFileW";
        test2="OpenProcess";
        test3="ReadFile";
        test4="WriteFile";
        test5="RegisterHotKey";
        test6="SetWindowsHookEx";
        for(int i=0; i<functii.size(); i++)
        {
            if(functii[i]==test1||functii[i]==test2||functii[i]==test3||functii[i]==test4||functii[i]==test5||functii[i]==test6)
                impact+=30;
        }

        test1="System Service Descriptor Table";
        test2="SSDT";
        test3="NtCreateFile";

        ok=0;
        for(int i=0; i<stringuri.size(); i++)
        {
            if(stringuri[i]==test1||stringuri[i]==test2||stringuri[i]==test3) ok=1;
        }
        if(ok) impact+=100;

        if(ascf) impact+=20;
        if(ascr) impact+=30;



        test1="ntoskrnl.exe";
        ok=0;
        for(int i=0; i<imprturi.size(); i++)
        {
            if(imprturi[i]==test1) ok=1;
        }
        if(ok) impact*=2;
    }
    Kernel_keylogger()
    {
        zi=0;
        luna=0;
        an=0;
        impact=0;
    }
};

class Ransomware: public malware
{
protected:
    int criptare, ofuscare;
public:
    Ransomware(int z, int l, int a, string name, string method, vector<string> reg, int crp, int ofu)
    {
        zi=z;
        luna=l;
        an=a;
        nume=name;
        metoda=method;
        registrii=reg;
        impact=0;

        criptare=crp;
        ofuscare=ofu;

        string test1,test2;
        test1="HKLM-run";
        test2="HKCU-run";
        int ok=0;
        for(int i=0; i<registrii.size(); i++)
        {
            if(registrii[i]==test1||registrii[i]==test2) ok=1;
        }
        if(ok) impact+=20;

        impact+=criptare;
        impact+=ofuscare;
    }
    Ransomware()
    {
        zi=0;
        luna=0;
        an=0;
        impact=0;
    }
};

int n,m,l1,l2,l3,l4;
Rootkit root[1005];
Keylogger key[1005];
Kernel_keylogger kkl[1005];
Ransomware ransom[1005];

class Computer{
protected:
    int id, impact;
    vector <int> malware,malware_type;
public:
    Computer(int ii, int imp, vector<int> mal, vector<int> mal_ty)
    {
        id=ii;
        impact=imp;
        malware=mal;
        malware_type=mal_ty;
    }
    Computer()
    {
        id=0;
        impact=0;
    }
    void set_id(int ii)
    {
        id=ii;
    }
    void update_impact(int imp)
    {
        impact+=imp;
    }
    void add_malware(int mal, int ty)
    {
        malware.push_back(mal);
        malware_type.push_back(ty);
    }
    int af_impact()
    {
        return impact;
    }
    int malware_count()
    {
        return malware.size();
    }
    void afisare()
    {
        g<<"Impactul total pentru computerul cu id "<<id<<" este: "<<impact;
        g<<"\nMalware-uri:\n";
        for(int i=0; i<malware.size(); i++)
        {
            if(malware_type[i]==1)
            {
                g<<i+1<<") Rootkit\n";
                root[malware[i]].print();
            }
            else if(malware_type[i]==2)
            {
                g<<i+1<<") Keylogger\n";
                key[malware[i]].print();
            }
            else if(malware_type[i]==3)
            {
                g<<i+1<<") Kernel-Keylogger\n";
                kkl[malware[i]].print();
            }
            else if(malware_type[i]==4)
            {
                g<<i+1<<") Ransomware\n";
                ransom[malware[i]].print();
            }

            g<<'\n';
        }
        g<<'\n';
    }
};


Computer computere[1005];

void Citire()
{
    f>>n>>m;
    vector <int> nul;
    for(int i=1; i<=n; i++)
    {
        computere[i]=Computer(i,0,nul,nul);
    }
    int computer_id,mal_id;
    int zz,ll,aa,rr;
    string num, met;
    string tst1, tst2, tst3, tst4;
    for(int i=1; i<=m; i++)
    {
        f>>computer_id>>mal_id;
        f>>zz>>ll>>aa;
        getline(f,num);
        getline(f,num);
        getline(f,met);
        f>>rr;
        vector<string> reg;
        for(int j=1; j<=rr; j++)
        {
            f>>tst1;
            reg.push_back(tst1);
        }
        if(mal_id==1)
        {
            vector<string> imprt,stri;
            int x,y;
            f>>x>>y;
            for(int i=1; i<=x; i++)
            {
                f>>tst1;
                imprt.push_back(tst1);
            }
            for(int i=1; i<=y; i++)
            {
                f>>tst1;
                stri.push_back(tst1);
            }

            l1++;
            root[l1]=Rootkit(zz,ll,aa,num,met,reg,imprt,stri);
            computere[computer_id].add_malware(l1,mal_id);
            computere[computer_id].update_impact(root[l1].af_impact());
        }
        else if(mal_id==2)
        {
            vector<string> func,tst;
            int x,y;
            f>>x>>y;
            for(int i=1; i<=x; i++)
            {
                f>>tst1;
                func.push_back(tst1);
            }
            for(int i=1; i<=y; i++)
            {
                f>>tst1;
                tst.push_back(tst1);
            }

            l2++;
            key[l2]=Keylogger(zz,ll,aa,num,met,reg,func,tst);
            computere[computer_id].add_malware(l2,mal_id);
            computere[computer_id].update_impact(key[l2].af_impact());
        }
        else if(mal_id==3)
        {
            vector<string> imprt,stri,func,tst;
            int x,y,z,t,asr,asf;
            f>>x>>y>>z>>t>>asr>>asf;
            for(int i=1; i<=x; i++)
            {
                f>>tst1;
                imprt.push_back(tst1);
            }
            for(int i=1; i<=y; i++)
            {
                f>>tst1;
                stri.push_back(tst1);
            }
            for(int i=1; i<=z; i++)
            {
                f>>tst1;
                func.push_back(tst1);
            }
            for(int i=1; i<=t; i++)
            {
                f>>tst1;
                tst.push_back(tst1);
            }

            l3++;
            kkl[l3]=Kernel_keylogger(zz,ll,aa,num,met,reg,imprt,stri,func,tst,asr,asf);
            computere[computer_id].add_malware(l3,mal_id);
            computere[computer_id].update_impact(kkl[l3].af_impact());
        }
        else if(mal_id==4)
        {
            int x,y;
            f>>x>>y;
            l4++;
            ransom[l4]=Ransomware(zz,ll,aa,num,met,reg,x,y);
            computere[computer_id].add_malware(l4,mal_id);
            computere[computer_id].update_impact(ransom[l4].af_impact());
        }
    }
}

void afisare()
{
    for(int i=1; i<=n; i++)
    {
        computere[i].afisare();
    }
}

bool comp(Computer x, Computer y)
{
    return x.af_impact()<y.af_impact();
}

void afis_sort()
{
    sort(computere+1, computere+n+1, comp);
    afisare();
}

void afis_sortk(int k)
{
    sort(computere+1, computere+n+1, comp);
    for(int i=n-k+1; i<=n; i++)
    {
        computere[i].afisare();
    }
}

void afis_procent()
{
    int s=0;
    for(int i=1; i<=n; i++)
    if(computere[i].malware_count())
        s++;
    g<<(s*100)/n<<"% din computere sunt infectate\n";
}

int main()
{
    Citire();
    afis_procent();
    return 0;
}
