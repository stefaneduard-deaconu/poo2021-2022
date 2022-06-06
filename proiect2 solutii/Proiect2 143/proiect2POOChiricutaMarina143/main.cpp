#include <iostream>
#include <vector>

using namespace std;

class Malware {
protected:
    string nume;
    string tipInfectare;
    float ratingImpact;
    struct Data{
        int zi;
        int luna;
        int an;
    }dataInfectare;
    vector<string> registriiModificati;
public:
    Malware(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati);
    virtual void calculeazaRatingImpact();
    virtual ostream& afisare(ostream& out) const;
    friend ostream& operator<<(ostream& out, const Malware& malware);
};
Malware::Malware(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati) {
    this->nume = nume;
    this->tipInfectare = tipInfectare;
    this->dataInfectare.zi = zi;
    this->dataInfectare.luna = luna;
    this->dataInfectare.an = an;
    this->registriiModificati = registriiModificati;
    this->ratingImpact = 0;
}
//Pentru orice tip de malware se adună 20 dacă registrii afectați sunt “HKLM-run” sau “HKCU-run”.
void Malware::calculeazaRatingImpact() {
    for(int i = 0; i<this->registriiModificati.size(); i++) {
        if (this->registriiModificati[i] == "HKLM-run" || this->registriiModificati[i] == "HKCU-run") {
            this->ratingImpact += 20;
            break;
        }
    }
}
ostream& Malware::afisare(ostream& out) const{
    out << "Nume: " << this->nume << endl;
    out << "Tip infectare" << this->tipInfectare << endl;
    out << "Rating impact: " << this->ratingImpact << endl;
    out << "Data infectare: " << this->dataInfectare.zi << "/" << this->dataInfectare.luna << "/" << this->dataInfectare.an << endl;
    out << "Registrii modificati: ";
    for (int i = 0; i <= this->registriiModificati.size(); i++) {
        out << this->registriiModificati[i] << " ";
    }
    out << endl;
    return out;
}
ostream& operator<<(ostream& out, const Malware& malware) {
    return malware.afisare(out);
}

class Rootkit: public virtual Malware {
protected:
    vector<string> listaImporturi;
    vector<string> stringuriSemnificative;
public:
    Rootkit(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati, vector<string> listaImporturi, vector<string> stringuriSemnificative);
    void calculeazaRatingImpact();
    virtual ostream& afisare(ostream& out) const;
};
Rootkit::Rootkit(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati, vector<string> listaImporturi, vector<string> stringuriSemnificative):Malware(nume, tipInfectare,zi,luna,an,registriiModificati) {
    this->listaImporturi = listaImporturi;
    this->stringuriSemnificative = stringuriSemnificative;
}

void Rootkit::calculeazaRatingImpact() {
    Malware::calculeazaRatingImpact();
    for (int i=0; i<this->listaImporturi.size(); i++) {
        if (this->listaImporturi[i] == "System Service Descriptor Table" ||
            this->listaImporturi[i] == "SSDT" ||
            this->listaImporturi[i] == "NtCreateFile") {
            this->ratingImpact += 100;
        }
    }
    for (int i=0; i<this->stringuriSemnificative.size(); i++) {
        if (this->stringuriSemnificative[i] == "ntoskrnl.exe")
            this->ratingImpact *= 2;
    }
}
ostream& Rootkit::afisare(ostream& out) const{
    Malware::afisare(out);
    out << "Lista importuri: " << endl;
    for(int i = 0; i < this->listaImporturi.size(); i++)
        out << " - " << this->listaImporturi[i] << endl;
    out << "Lista stringuri semnificative: " << endl;
    for (int i = 0; i < this->stringuriSemnificative.size(); i++)
        out << " - " << this->stringuriSemnificative[i] << endl;
    return out;
}

class Keylogger: public virtual Malware {
protected:
    vector<string> functiiFolosite;
    vector<string> tasteSpecialeDefinite;
public:
    Keylogger(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati, vector<string> functiiFolosite, vector<string> tasteSpecialeDefinite);
    void calculeazaRatingImpact();
    virtual ostream& afisare(ostream& out) const;
};
Keylogger::Keylogger(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati, vector<string> functiiFolosite, vector<string> tasteSpecialeDefinite):Malware(nume, tipInfectare,zi,luna,an,registriiModificati) {
    this->functiiFolosite = functiiFolosite;
    this->tasteSpecialeDefinite = tasteSpecialeDefinite;
}

void Keylogger::calculeazaRatingImpact() {
    Malware::calculeazaRatingImpact();
    for (int i=0; i<this->tasteSpecialeDefinite.size(); i++) {
        //“[Up]”, “[Num Lock]”, “[Down]”, “[Right]”, “[UP]”, “[Left]”, “[PageDown]”
        if (this->tasteSpecialeDefinite[i] == "[Up]" ||
            this->tasteSpecialeDefinite[i] == "[Num Lock]" ||
            this->tasteSpecialeDefinite[i] == "[Down]" ||
            this->tasteSpecialeDefinite[i] == "[Right]" ||
            this->tasteSpecialeDefinite[i] == "[UP]" ||
            this->tasteSpecialeDefinite[i] == "[Left]" ||
            this->tasteSpecialeDefinite[i] == "[PageDown]") {
            this->ratingImpact += 10;
        }
    }
    for (int i=0; i<this->functiiFolosite.size(); i++) {
        if (this->functiiFolosite[i] == "CreateFileW" ||
            this->functiiFolosite[i] == "OpenProcess" ||
            this->functiiFolosite[i] == "ReadFile" ||
            this->functiiFolosite[i] == "WriteFile" ||
            this->functiiFolosite[i] == "RegisterHotKey" ||
            this->functiiFolosite[i] == "SetWindowsHookEx") {
            this->ratingImpact += 30;
        }
    }
}
ostream& Keylogger::afisare(ostream& out) const{
    Malware::afisare(out);
    out << "Functii folosite: " << endl;
    for (int i = 0; i < this->functiiFolosite.size(); i++)
        out << " - " << this->functiiFolosite[i] << endl;
    out << "Taste speciale definite: " << endl;
    for (int i = 0; i < this->tasteSpecialeDefinite.size(); i++)
        out << " - " << this->tasteSpecialeDefinite[i] << endl;
    return out;
}

class KernelKeylogger: public virtual Keylogger, public virtual Rootkit {
private:
    bool ascundeRegistrii;
    bool ascundeFisiere;
public:
    KernelKeylogger(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati, vector<string> listaImporturi, vector<string> stringuriSemnificative, vector<string> functiiFolosite, vector<string> tasteSpecialeDefinite, bool ascundeRegistrii, bool ascundeFisiere);

    void calculeazaRatingImpact();
    ostream& afisare(ostream& out) const;
};
KernelKeylogger::KernelKeylogger(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati, vector<string> listaImporturi, vector<string> stringuriSemnificative, vector<string> functiiFolosite, vector<string> tasteSpecialeDefinite, bool ascundeRegistrii, bool ascundeFisiere):
        Keylogger(nume,tipInfectare,zi,luna,an,registriiModificati, functiiFolosite, tasteSpecialeDefinite),
        Rootkit(nume, tipInfectare, zi, luna, an, registriiModificati, listaImporturi, stringuriSemnificative),
        Malware(nume, tipInfectare, zi, luna, an, registriiModificati){
    this->ascundeRegistrii = ascundeRegistrii;
    this->ascundeFisiere = ascundeFisiere;
}

void KernelKeylogger::calculeazaRatingImpact() {
    Rootkit::calculeazaRatingImpact();
    Keylogger::calculeazaRatingImpact();
    if (this->ascundeRegistrii) {
        this->ratingImpact += 30;
    }
    if (this->ascundeFisiere += 20);
}
ostream& KernelKeylogger::afisare(ostream& out) const{
    Rootkit::afisare(out);
    Keylogger::afisare(out);
    if (this->ascundeRegistrii)
        cout << "Ascunde registrii" << endl;
    else
        cout << "Nu ascunde registrii" << endl;

    if (this->ascundeFisiere)
        cout << "Ascunde fisiere" << endl;
    else
        cout << "Nu ascunde fisiere" << endl;
    return out;
}

class Ransomware: public Malware {
    int ratingCriptare;
    float ratingObfuscare;
public:
    Ransomware(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati, int ratingCriptare, float ratingObfuscare);
    void calculeazaRatingImpact();
    ostream& afisare(ostream& out);
};
Ransomware::Ransomware(string nume, string tipInfectare, int zi, int luna, int an, vector<string> registriiModificati, int ratingCriptare, float ratingObfuscare):Malware(nume, tipInfectare, zi, luna, an, registriiModificati) {
    this->ratingCriptare = ratingCriptare;
    this->ratingObfuscare = ratingObfuscare;
}

void Ransomware::calculeazaRatingImpact() {
    this->ratingImpact += this->ratingCriptare;
    this->ratingImpact += this->ratingObfuscare;
}
ostream& Ransomware::afisare(ostream& out) {
    Malware::afisare(out);
    out << "Rating criptare: " << this->ratingCriptare << endl;
    out << "Rating obfuscare: " << this->ratingObfuscare << endl;
    return out;
}


class Computer {
private:
    const int id;
    static int lastId;
    vector<Malware*> listaMalware;
    float ratingFinal;
public:
    Computer(vector<Malware*> listaMalware);
    void calculeazaRatingFinal();
    friend ostream& operator<<(ostream& out, const Computer& computer);
};
int Computer::lastId = 0;
Computer::Computer(vector<Malware*> listaMalware):id(++lastId) {
    this->listaMalware = listaMalware;
}

ostream& operator<<(ostream& out, const Computer& computer) {
    out << "Id: " << computer.id << endl;
    out << "Rating: " << computer.ratingFinal << endl;
    out << "Malwares:" << endl;
    return out;
}


int main() {
    return 0;
}