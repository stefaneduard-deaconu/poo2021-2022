#include <iostream>

#include "scripts/sample.h"
#include "gui/main.h"


//int main() {
////    sample::main();
//    Console::main();
//    return 0;
//}

//int main() {
//    Game game; // nu are nevoie de date,
//    //            deoarece numele jucatorilor si scorurile sunt citite de la tastatura
//
//    game.mainLoop();
//}

#include <memory>

using namespace std;

class FormInput {

public:
    virtual ~FormInput() {

    }
};


class Form {
private:
    vector<shared_ptr<FormInput> > fields;
public:
    Form(const vector<shared_ptr<FormInput>> &fields) : fields(fields) {}

    void fillIn() {

    }

    virtual ~Form() = 0;
};

class GradedFormInput {
protected:
    int maxGrade;
public:
    virtual int computeGrade() = 0;

    void printGrade() {
        cout << computeGrade() << " out of " << maxGrade << endl;
    }
};

class MultipleChoice : public GradedFormInput {
    vector<string> choices;
    int correctChoice, choice = -1;
public:
    MultipleChoice(const vector<string> &choices, int correctChoice, int choice) : choices(choices), correctChoice(correctChoice), choice(choice) {}

    int computeGrade() override {
        if (choice == correctChoice) {
            return maxGrade;
        } else {
            return 0;
        }
    }
};

class LinearGradient : public GradedFormInput {
    int maxChoice;
    int preferredChoice, choice = -1;
public:
    LinearGradient(int maxChoice, int preferredChoice, int choice) : maxChoice(maxChoice),
                                                                     preferredChoice(preferredChoice), choice(choice) {}

    int computeGrade() override {
        if (choice == -1) {
            return 0; // the user chosed nothing
        }

        return maxGrade - abs(choice - preferredChoice);
    }
};

class CheckBox : public GradedFormInput {
    vector<string> allChoices;
    vector<int> correctChoices, choices;
public:
    CheckBox(const vector<string> &allChoices, const vector<int> &correctChoices, const vector<int> &choices)
            : allChoices(allChoices), correctChoices(correctChoices), choices(choices) {}



    int computeGrade() override {
        if (commonChoices() == correctChoices.size()) {
            return maxGrade;
        } else {
            return 0;
        }
    }
private:
    // utilitary functions
    int commonChoices() {
        return 0; // TODO
    }
};

class GradedForm : public Form {
public:
    GradedForm(const vector<shared_ptr<FormInput>> &fields) : Form(fields) {}
};

class FormCreator {
private:
    vector<shared_ptr<Form> > forms;
public:
    void run() {

    }
};

int main() {
    vector<shared_ptr<FormInput> > formFields;
    formFields = {
            make_shared<MultipleChoice>(
                    MultipleChoice(
                            {"A", "B", "C"},
                            2,
                            -1 // user's choice (index)
                    )
            ),
            make_shared<LinearGradient>(
                    LinearGradient(
                            5, // max value
                            3, // preferred value (in [1,5] ) is 3
                            -1 // our choice. -1 when not chosen
                            )
            ),
            make_shared<CheckBox>(
                    CheckBox(
                            {"A", "B", "C"}, // possible choices
                            {"A", "B"}, // correct choices
                            {} // user's choices
                            )
            ),
    };

    shared_ptr<GradedForm> anyForm = make_shared<GradedForm>(
            GradedForm(formFields)
    );

    anyForm->fillIn(); // incepem completarea form-ului

    cout << anyForm << endl; // afiseaza form-ul completat

    return 0;
}