#include <iostream>
#include <string>
#include <vector>
#include "Transversal.h"
#include "Set.h"

int main () {
    using namespace std;

    std::vector< Set<string> > sets{
        Set<string>{"145"},
        Set<string>{"1"},
        Set<string>{"234"},
        Set<string>{"24"}
    };

    Transversal<string> tr {sets};

    for (auto set : sets) {
        cout << set << endl;
    }

    tr.show_common_set();
    tr.show_graph();

    return 0;
}
