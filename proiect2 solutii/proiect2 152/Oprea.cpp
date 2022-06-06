#include <iostream>

#include <string>
#include <vector>

#include <algorithm>
#include <memory>

/* Utilitar pentru citire. Evitam problemele cu golirea bufferului. */
namespace Reader {
    std::string buffer;

    /* Aruncam exceptie. Nu ar trebui sa intram decat pe specializari. */
    template<class T>
    static T read(std::istream &is) {
        throw std::exception();
    }

    template<>
    int read(std::istream &is) {
        while (true) {
            try {
                getline(is, buffer);
                return std::stoi(buffer);
            } catch (...) {
                std::cout << "Input invalid. Introduceti un numar intreg!\n";
            }
        }
    }

    template<>
    double read(std::istream &is) {
        while (true) {
            try {
                getline(is, buffer);
                return std::stod(buffer);
            } catch (...) {
                std::cout << "Input invalid. Introduceti un numar real!\n";
            }
        }
    }

    template<>
    std::string read(std::istream &is) {
        while (true) {
            try {
                getline(is, buffer);
                return buffer;
            } catch (...) {
                std::cout << "Input invalid. Introduceti un sir de caractere!\n";
            }
        }
    }
}

class IoBase {
public:
    virtual std::istream &read(std::istream &is) {
        return is;
    }

    friend std::istream &operator>>(std::istream &is, IoBase &base) {
        return base.read(is);
    }

    virtual std::ostream &write(std::ostream &os) const {
        return os;
    }

    friend std::ostream &operator<<(std::ostream &os, IoBase &base) {
        return base.write(os);
    }

    virtual ~IoBase() = 0;
};

IoBase::~IoBase() = default;

class Date : public IoBase {
private:
    int zi, luna, an;

public:
    Date() : zi{0}, luna{0}, an{0} {};

    std::istream &read(std::istream &is) override {
        std::cout << "Zi infectare: \n";
        zi = Reader::read<int>(is);
        std::cout << "Luna infectare: \n";
        luna = Reader::read<int>(is);
        std::cout << "An infectare: \n";
        an = Reader::read<int>(is);

        return is;
    }

    std::ostream &write(std::ostream &os) const override {
        os << "Data infectare: " << zi << "/" << luna << "/" << an << '\n';
        return os;
    }
};

class Malware : public IoBase {
protected:
    double rating;
    Date data_infectare;
    std::string nume, metoda_infectare;
    std::vector<std::string> registri;

public:
    Malware() : rating{0.}, data_infectare{}, metoda_infectare{"unknown"} {};

    double get_rating() const {
        return rating;
    }

    virtual void read_specific(std::istream &is) = 0;

    virtual void write_specific(std::ostream &os) const = 0;

    void calc_rating() {
        for (const auto &registru: {"HKLM-run", "HKCU-run"}) {
            if (std::find(registri.begin(), registri.end(), registru) != registri.end()) {
                rating += 20.;
            }
        }
        rating += calc_rating_specific();
    };

    virtual double calc_rating_specific() = 0;

    std::istream &read(std::istream &is) override {
        is >> data_infectare;

        std::cout << "Nume: \n";
        nume = Reader::read<std::string>(is);

        std::cout << "Metoda infectare: \n";
        metoda_infectare = Reader::read<std::string>(is);

        std::cout << "Numar registri infectati: \n";
        int nr_reg = Reader::read<int>(is);
        for (int i = 1; i <= nr_reg; i++) {
            std::cout << "Nume registru infectat #" << i << ": \n";
            std::string nume_reg = Reader::read<std::string>(is);
            registri.push_back(nume_reg);
        }

        read_specific(is);

        calc_rating();

        return is;
    }

    std::ostream &write(std::ostream &os) const override {
        os << "Rating impact: " << rating << '\n';
        os << (IoBase &) data_infectare << '\n';
        os << "Nume: " << nume << '\n';
        os << "Metoda infectare: " << metoda_infectare << '\n';

        os << "Registrii infectati: ";
        for (const auto &registru: registri) {
            os << registru << ", ";
        }
        os << '\n';

        write_specific(os);

        return os;
    }

    ~Malware() override = 0;
};

Malware::~Malware() = default;

class Rootkit : virtual public Malware {
protected:
    std::vector<std::string> imports, strings;

public:
    Rootkit() = default;

    void read_specific(std::istream &is) override {
        std::cout << "Numar importuri: \n";
        int nr_imp = 0;
        while (nr_imp < 1) {
            nr_imp = Reader::read<int>(is);
            if (nr_imp < 1) {
                std::cout << "Rootkit are cel putin un import. Incercati din nou...\n";
            }
        }
        for (int i = 1; i <= nr_imp; i++) {
            std::cout << "Nume import #" << i << ": \n";
            std::string import = Reader::read<std::string>(is);
            imports.push_back(import);
        }

        std::cout << "Numar stringuri: \n";
        int nr_str = Reader::read<int>(is);
        for (int i = 1; i <= nr_str; i++) {
            std::cout << "Nume string #" << i << ": \n";
            std::string str = Reader::read<std::string>(is);
            strings.push_back(str);
        }
    }

    void write_specific(std::ostream &os) const override {
        os << "Importuri: ";
        for (const auto &import: imports) {
            os << import << ", ";
        }
        os << '\n';

        os << "Strings: ";
        for (const auto &str: strings) {
            os << str << ", ";
        }
        os << '\n';
    }

    double calc_rating_specific() override {
        double r = 0.;

        for (const auto &str: {"System Service Descriptor Table", "SSDT", "NtCreateFile"}) {
            if (std::find(strings.begin(), strings.end(), str) != strings.end()) {
                r += 100.;
                break;
            }
        }

        if (std::find(imports.begin(), imports.end(), "ntoskrnl.exe") != imports.end()) {
            r *= 2.;
        }

        return r;
    }

    std::ostream &write(std::ostream &os) const override {
        os << "Rootkit\n";
        Malware::write(os);

        return os;
    }
};

class Keylogger : virtual public Malware {
protected:
    std::vector<std::string> functii, taste_speciale;

public:
    Keylogger() = default;

    void read_specific(std::istream &is) override {
        std::cout << "Numar functii: \n";
        int nr_functii = Reader::read<int>(is);
        for (int i = 1; i <= nr_functii; i++) {
            std::cout << "Nume functie #" << i << ": \n";
            std::string functie = Reader::read<std::string>(is);
            functii.push_back(functie);
        }

        std::cout << "Numar taste speciale: \n";
        int nr_ts = Reader::read<int>(is);
        for (int i = 1; i <= nr_ts; i++) {
            std::cout << "Nume tasta speciala #" << i << ": \n";
            std::string tasta_speciala = Reader::read<std::string>(is);
            taste_speciale.push_back(tasta_speciala);
        }
    }

    void write_specific(std::ostream &os) const override {
        os << "Functii: ";
        for (const auto &functie: functii) {
            os << functie << ", ";
        }
        os << '\n';

        os << "Taste speciale: ";
        for (const auto &tasta_speciala: taste_speciale) {
            os << tasta_speciala << ", ";
        }
        os << '\n';
    }

    double calc_rating_specific() override {
        double r = 0.;

        for (const auto &str: {"[Up]", "[Num lock]", "[Down]", "[Right]", "[UP]", "[Left]", "[PageDown]"}) {
            if (std::find(taste_speciale.begin(), taste_speciale.end(), str) != taste_speciale.end()) {
                r += 10.;
            }
        }

        for (const auto &fct: {"CreateFileW", "OpenProcess", "ReadFile", "WriteFile", "RegisterHotKey",
                               "SetWindowsHookEx"}) {
            if (std::find(functii.begin(), functii.end(), fct) != taste_speciale.end()) {
                r += 30.;
            }
        }

        return r;
    }

    std::ostream &write(std::ostream &os) const override {
        os << "Keylogger\n";
        Malware::write(os);

        return os;
    }
};

class KernelKeylogger : public Rootkit, public Keylogger {
protected:
    bool ascunde_fisiere, ascunde_registrii;

public:
    KernelKeylogger() : ascunde_fisiere{false}, ascunde_registrii{} {};

    void read_specific(std::istream &is) override {
        std::cout << "Ascunde fisiere? 0=NU, 1=DA \n";
        ascunde_fisiere = Reader::read<int>(is) != 0;
        std::cout << "Ascunde registrii? 0=NU, 1=DA \n";
        ascunde_registrii = Reader::read<int>(is) != 0;
    }

    void write_specific(std::ostream &os) const override {
        os << "Ascunde fisiere: " << (ascunde_fisiere ? "DA\n" : "NU\n");
        os << "Ascunde registrii: " << (ascunde_registrii ? "DA\n" : "NU\n");
    }

    double calc_rating_specific() override {
        double r = Rootkit::calc_rating_specific() + Keylogger::calc_rating_specific();
        if (ascunde_fisiere) {
            r += 20.;
        }
        if (ascunde_registrii) {
            r += 30.;
        }
        return r;
    }

    std::istream &read(std::istream &is) override {
        Malware::read(is);
        Rootkit::read_specific(is);
        Keylogger::read_specific(is);

        return is;
    }

    std::ostream &write(std::ostream &os) const override {
        std::cout << "Kernel-keylogger\n";

        Malware::write(os);
        Rootkit::write_specific(os);
        Keylogger::write_specific(os);

        return os;
    }
};

class Ransomware : public Malware {
protected:
    double rating_criptare, rating_obfuscare;

public:
    Ransomware() : rating_criptare{0.}, rating_obfuscare{0.} {};

    void read_specific(std::istream &is) override {
        std::cout << "Rating criptare: \n";
        rating_criptare = Reader::read<double>(is);
        while (rating_criptare < 1 || rating_criptare > 10) {
            std::cout << "Rating criptare invalid (introduceti un numar intre 1 si 10). Incercati din nou...\n";
            rating_criptare = Reader::read<double>(is);
        }

        std::cout << "Rating obfuscare: \n";
        rating_obfuscare = Reader::read<double>(is);
        while (rating_obfuscare < 0 || rating_obfuscare > 100) {
            std::cout << "Rating obfuscare invalid (introduceti un numar intre 0 si 100). Incercati din nou...\n";
            rating_obfuscare = Reader::read<double>(is);
        }
    }

    void write_specific(std::ostream &os) const override {
        os << "Rating criptare: " << rating_criptare << '\n';
        os << "Rating obfuscare: " << rating_obfuscare << "%\n";
    }

    double calc_rating_specific() override {
        return rating_criptare + rating_obfuscare;
    }

    std::ostream &write(std::ostream &os) const override {
        os << "Ransomware\n";
        Malware::write(os);

        return os;
    }
};

class Computer : public IoBase {
private:
    static int counter;
    int id;

    std::vector<std::shared_ptr<Malware>> malwares;
    double rating_final;

public:
    Computer() {
        counter++;
        id = counter;
        rating_final = 0;
    }

    double get_rating() const {
        return rating_final;
    }

    std::istream &read(std::istream &is) override {
        std::cout << "Numar de malware: \n";
        int nr_malware = Reader::read<int>(is);

        for (int i = 1; i <= nr_malware; i++) {
            std::shared_ptr<Malware> malware;

            std::cout << "Tip malware #" << i << ": 1=Rootkit, 2=Keylogger, 3=KernelKeylogger, 4=Ransomware \n";
            int tip = Reader::read<int>(is);

            if (tip == 1) {
                malware = std::make_shared<Rootkit>();
            } else if (tip == 2) {
                malware = std::make_shared<Keylogger>();
            } else if (tip == 3) {
                malware = std::make_shared<KernelKeylogger>();
            } else {
                malware = std::make_shared<Ransomware>();
            }

            is >> *malware;
            malwares.push_back(malware);

            rating_final += malware->get_rating();
        }

        return is;
    }

    std::ostream &write(std::ostream &os) const override {
        std::cout << "\n\nComputerul " << id << " are " << (int) malwares.size() << " malwares:\n";
        for (const auto &malware: malwares) {
            std::cout << "==============================\n";
            std::cout << *malware << '\n';
        }
        std::cout << "Rating total: " << rating_final << '\n';
        return os;
    }
};

int Computer::counter;

class Menu {
private:
    std::vector<Computer> computers;
    std::vector<std::pair<std::string, std::function<void()>>> optiuni;

public:
    Menu() {
        optiuni = {
                std::make_pair("Adauga computer", std::bind(&Menu::adauga_computer, this)),
                std::make_pair("Afiseaza computere", std::bind(&Menu::afiseaza_computere, this)),
                std::make_pair("Afiseaza computere dupa rating", std::bind(&Menu::afiseaza_computere_rating, this)),
                std::make_pair("Afiseaza primele k computere dupa rating",
                               std::bind(&Menu::afiseaza_k_computere_rating, this)),
                std::make_pair("Procentaj computere infectate", std::bind(&Menu::procentaj_computere_infectate, this)),
        };
    }

    void adauga_computer() {
        Computer computer;
        std::cin >> computer;
        computers.push_back(computer);
    }

    void afiseaza_computere() {
        for (const auto &computer: computers) {
            std::cout << (IoBase &) computer << '\n';
        }
    }

    void sorteaza_computere_rating() {
        std::sort(computers.begin(), computers.end(), [&](const Computer &A, const Computer &B) -> bool {
            return A.get_rating() < B.get_rating();
        });
    }

    void afiseaza_computere_rating() {
        sorteaza_computere_rating();
        afiseaza_computere();
    }

    void afiseaza_k_computere_rating() {
        sorteaza_computere_rating();

        std::cout << "k = ";
        int k = Reader::read<int>(std::cin);

        for (int i = 0; i < std::min((size_t) k, computers.size()); i++) {
            std::cout << (IoBase &) computers[i] << '\n';
        }
    }

    void procentaj_computere_infectate() const {
        std::cout << "Total computere: " << computers.size() << '\n';

        int nr_infectate = 0;
        for (const auto &computer: computers) {
            if (computer.get_rating() > 0.) {
                nr_infectate++;
            }
        }

        std::cout << "Infectate: " << nr_infectate << '\n';
        std::cout << "Procentaj: " << 1.0 * nr_infectate / computers.size() * 100 << "%\n";
    }

    void print_options() const {
        for (int i = 0; i < (int) optiuni.size(); i++) {
            std::cout << i + 1 << ". " << optiuni[i].first << '\n';
        }
        std::cout << (int) optiuni.size() + 1 << ". Iesire\n";
    }

    int choose_option() const {
        while (true) {
            std::cout << "Alegeti comanda intre 1 si " << (int) optiuni.size() + 1 << "!\n";
            int command = Reader::read<int>(std::cin);
            if (command < 1 || command > (int) optiuni.size() + 1) {
                std::cout << "Invalid. Incercati din nou...";
            } else {
                return command;
            }
        }
    }

    void main_loop() const {
        while (true) {
            print_options();
            int opt = choose_option();
            if (opt <= (int) optiuni.size()) {
                optiuni[opt - 1].second();
            } else {
                break;
            }
        }
        std::cout << "Meniul a fost inchis!\n";
    }
};

int main() {
    Menu().main_loop();
    return 0;
}
