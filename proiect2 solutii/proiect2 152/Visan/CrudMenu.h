//
// Created by visan on 5/3/22.
//

#ifndef COLOCVIU_CRUDMENU_H
#define COLOCVIU_CRUDMENU_H

#include<vector>
#include<memory>
#include<map>
#include<functional>
#include"Computer.h"

using namespace std;

class CrudMenu {
private:
    std::vector<Computer> computers;
    map<std::string, std::function<void(std::vector<Computer> &)>> options;
public:
    explicit CrudMenu(map<string, function<void(vector<Computer> &)>> _options)
            : computers(), options(std::move(_options)) {

    }

    explicit CrudMenu(map<string, function<void(vector<Computer> &)>> _options,
                      std::vector<Computer> _computers) : computers(std::move(_computers)),
                                                          options(std::move(_options)) {

    }

    void listOptions() {
        int current = 1;
        for (const auto &x: options) {
            cout << current << ". " << x.first << endl;
            current++;
        }
        cout << current << ". Exit." << '\n';
    }

    int chooseOption(int first, int last) {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeți un număr între "
                 << first << " și " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }


    void mainLoop() {
        while (true) {
            int option = chooseOption(1, options.size() + 1);
            if (option == options.size() + 1) {
                break;
            } else {
                auto iter = options.begin();
                for (int k = 1; k < option; k++) {
                    iter++;
                }
                iter->second(computers);
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a încheiat cu success";
    }
};

#endif //COLOCVIU_CRUDMENU_H
