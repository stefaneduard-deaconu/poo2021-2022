#include <iostream>
#include"Malware.h"
#include"Computer.h"
#include"CrudMenu.h"
#include<algorithm>

using namespace std;


void print(std::vector<Computer> &computers) {
    for (const auto &x: computers) {
        cout << x << endl;
    }
}

bool compare(const Computer &a, const Computer &b) {
    return a.final_rating() < b.final_rating();
}

void print_sorted(std::vector<Computer> &computers) {
    sort(computers.begin(), computers.end(), compare);
    print(computers);
}

void print_k_sorted(std::vector<Computer> &computers) {
    int k;
    cout << "Enter k:";
    cin >> k;
    sort(computers.begin(), computers.end(), compare);
    for (int i = 0; i < k; i++) {
        cout << computers[i] << " ";
    }
}

void infected(std::vector<Computer> &computers) {
    double total = computers.size();
    double infected = 0;
    for (const Computer &x: computers) {
        if (x.infected()) {
            infected++;
        }
    }
    cout << "Percentage of infection: " << (infected / total) * 100 << "%" << endl;
}

int main() {
    int n;
    vector<Computer> computers;
    cout << "Introduceti numarul de calculatoare: ";
    cin >> n;
    computers.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> computers[i];
    }


    CrudMenu crudMenu({{"print ",               print},
                       {"print sorted",         print_sorted},
                       {"print k sorted",       print_k_sorted},
                       {"infection percentage", infected}},
                      computers);
    crudMenu.mainLoop();
    return 0;
}
