#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
int id = 0;

template<class A> std::istream& operator>>(std::istream& is, std::vector<A>& vec){
    int n; is>>n;
    for(int i=0; i<n; ++i)
    {
        A a;
        std::cin>>a;
        vec.push_back(a);
    }
    return is;
}

template<class A>std::ostream& operator<<(std::ostream& os, const std::vector<A>& vec){
    for(const auto& elem: vec)
        std::cout<<elem<<" ";
    return os;
}

class ioBase{
    virtual std::istream& read(std::istream&);
    virtual std::ostream& write(std::ostream&) const;
    friend std::istream& operator>>(std::istream&, ioBase& b);
    friend std::ostream& operator<<(std::ostream&, const ioBase&);
};

std::istream& ioBase::read(std::istream &is) {
    return is;
}

std::ostream& ioBase::write(std::ostream& os) const{
    return os;
}

std::istream& operator>>(std::istream& is, ioBase& b){
    return b.read(is);
}

std::ostream& operator<<(std::ostream& os,const ioBase& b){
    return b.write(os);
}

class data: public ioBase{
    int day, month, year;
public:
    data() = default;
    data(const int& day, const int& month, const int& year):day(day),month(month),year(year){}
    std::istream& read(std::istream&) override;
    std::ostream& write(std::ostream&) const override;
};

std::istream& data::read(std::istream &is) {
    std::cout<<"\nDay, month, year: ";
    is >> day >> month >> year;
    return is;
}

std::ostream& data::write(std::ostream &os) const {
    std::cout<<"\nDay, month, year: "<<day<<"."<<month<<"."<<year;
    return os;
}

class malware: public ioBase{
protected:
    double impact;
    data d;
    std::string name;
    std::string method;
    std::vector<std::string> registers;
public:
    malware() = default;
    malware(const double& impact, const data& d, const std::string& name, std::vector<std::string>& registers, const std::string& method="unknown"):
    impact(impact),d(d),name(name),registers(registers),method(method){}
    std::istream& read(std::istream&) override;
    std::ostream& write(std::ostream&) const override;
    double getImpact() const;
};

std::istream& malware::read(std::istream &is) {
    std::cout<<"\nImpact: ";
    is>> impact;
    std::cout<<"Date: ";
    is >> d;
    std::cout<<"Name: ";
    is>>name;
    std::cout<<"Is the infection method known? (1)yes, (0)no.\nChoice: ";
    int check;
    is>>check;
    switch (check) {
        case 1: {std::cout<<"Method: ";
            is>>method;
            break;
        }
        case 0: method = "unknown"; break;
        default: std::cout<<"Invalid option."; method = "unknown";
    }
    std::cout<<"\nRegisters: \nHow many registers are affected: ";
    std::cin>>registers;
}

std::ostream& malware::write(std::ostream& os) const{
    std::cout<<"\n\nImpact: "<<impact<<"\nDate: "<<d<<"\nName: "<<name
    <<"\nMethod: "<<method<<"\nRegisters: "<< registers;
    return os;
}

double malware::getImpact() const {
    return impact;
}

template<> std::istream& operator>><std::shared_ptr<malware>>(std::istream& is,std::vector<std::shared_ptr<malware>>& vec){
    std::cout<<"\nHow many malware: ";
    int n; std::cin>>n;
    for(int i = 0; i < n; ++i)
    {
        std::shared_ptr<malware> obj =std::make_shared<malware>();
        std::cin>>*obj;
        vec.push_back(obj);
    }
    return is;
}

template<> std::ostream& operator<<<std::shared_ptr<malware>>(std::ostream& os,const std::vector<std::shared_ptr<malware>>& vec){
    for(const auto& elem:vec)
        std::cout<<*elem;
    return os;
}

class computer: public ioBase{
    int id = ::id++;
    std::vector<std::shared_ptr<malware>> mal;
    double finalRating = 0;
public:
    computer() = default;
    computer(const std::vector<std::shared_ptr<malware>>& mal): mal(mal){
        for(const auto& elem: mal)
            finalRating += elem->getImpact();
    }
    std::istream& read(std::istream&) override;
    std::ostream& write(std::ostream&) const override;
    double getFinalRating() const;
};

double computer::getFinalRating() const {
    return finalRating;
}

std::istream& computer::read(std::istream& is){
    std::cout<<"\nMalware list: ";
    is>>mal;
    for(const auto& elem: mal)
        finalRating+= elem->getImpact();
    return is;
}

std::ostream& computer::write(std::ostream& os) const{
    std::cout<<"\n\nID: "<<id;
    std::cout<<"\nMalware list: ";
    std::cout<<mal;
    std::cout<<"\nFinal rating: "<<finalRating;
    return os;
}

class baseMenu: public ioBase{
public:
    virtual void mainLoop(){}
    virtual void printOptions(){}
    virtual int selectOption(){}
};

class smallCompany: public baseMenu{
    std::vector<computer> computerList;
public:
    smallCompany() = default;
    smallCompany(const std::vector<computer>& vec):computerList(vec){}
    std::istream& read(std::istream&) override;
    void printOptions() override;
    void mainLoop() override;
    int selectOption() override;
};

std::istream& smallCompany::read(std::istream& is){
    std::cout<<"How many computers: ";
    int n; is >> n;
    for(int i = 0; i < n; ++i)
    {
        computer c;
        std::cin>>c;
        computerList.push_back(c);
    }
    return is;
}

void smallCompany::printOptions() {
    std::cout<<"\n\nTo start choose an option 1-5: ";
    std::cout<<"\n1. Print all computers."<<"\n2. Print computers sorted by finalRating."<<"\n3. Print the first k computers by finalRating."<<"\n4. Show percent of infected computers."<<"\n5. Close app.";
}

bool compareImpact(const computer& c1, const computer& c2){
    return c1.getFinalRating() < c2.getFinalRating();
}

int smallCompany::selectOption() {
    int option;
    std::cout<<"\nChoose: ";
    std::cin>>option;

    switch (option) {
        case 1: std::cout<<"List of computers: "<<computerList; break;
        case 2: { std::sort(computerList.begin(),computerList.end(), compareImpact);
            std::cout<<"List of sorted computers: "<<computerList;
            break;}
        case 3: break;
        case 4: break;
        case 5: std::cout<<"\n\n--------------------------------\nApp closed successfully."; break;
        default: std::cout<<"\nThis is not a valid option.";
    }

    return option;
}

void smallCompany::mainLoop() {
    int option = 1;
    while(option != 5)
    {
        this->printOptions();
        option = this->selectOption();
    }
}

int main() {

    smallCompany c;
    std::cin>>c;
    c.mainLoop();

    return 0;
}
