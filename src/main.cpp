#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdexcept>
#include "Transversal.h"
#include "Set.h"

using namespace std;

vector< Set<string> > sets_generation();
vector< Set<string> > sets_input();

int main () {

    cout << "Input sets:" << endl;
    cout << "Choose input method: random generated (R) or input custom ones? (C): ";
    char choice {0};
    cin >> choice;

    vector< Set<string> > sets{};
    switch (choice)
    {
        case 'r':
        case 'R':
            sets = sets_generation();
        break;

        case 'c':
        case 'C':
            sets = sets_input();
        break;

        default:
            cerr << "You haven't choose input method!" << endl;
            throw std::runtime_error{"Wrong option"};
            break;
    }

    for (size_t i = 0; i != sets.size(); ++i) {
        cout << "Set " << i+1 << ": " << sets[i] << endl;
    }

    try {
        Transversal <string> tr {sets};

        tr.show_common_set();
        tr.show_graph();
    }
    catch( wrong_input_error) {
        cerr << "Impossible to build transversal with these input data!" << endl;
    }
    catch(runtime_error) {
        cerr << "Impossible to build transversal! Unknown error!" << endl;
    }

    return 0;
};

vector< Set<string> > sets_generation()
{
    srand(time(NULL));
    enum {MAX_NUMBER_OF_SETS = 10};

    std::vector< Set<string> > sets{};
    int number_of_sets = rand() % MAX_NUMBER_OF_SETS + 1;

    static const string mask {"0123456789"};

    for (int i = 0; i < number_of_sets; i++)
    {
        string str_to_add{};
        for (auto ch : mask)
        {
            if (rand() % 2)
                str_to_add += ch;
        }
        sets.push_back(str_to_add);
    }

    return sets;
};

vector< Set<string> > sets_input()
{
    size_t num {0};
    cout << "Choose number of sets: ";
    cin >> num;

    std::vector< Set<string> > sets{};
    for (int i = 0; i < num; i++)
    {
        string str{};
        cout << "Input set " << i + 1 << ": ";
        cin >> str;
        sets.push_back(str);
    }
    return sets;
};
