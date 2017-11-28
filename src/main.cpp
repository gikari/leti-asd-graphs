#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "Transversal.h"
#include "Set.h"

using namespace std;

vector< Set<string> > sets_generation();
vector< Set<string> > sets_input();

int main () {

	vector< Set<string> > sets{
		Set<string>{"145"},
		Set<string>{"1"},
		Set<string>{"234"},
		Set<string>{"24"}
		};
	char c;
	cout << "Choose sets generation or keyboard input (G/K)" << endl;
	char choose;
	cin >> choose;
	switch (choose)
	{
		case 'g':
		{
			vector< Set<string> > sets_gen = sets_generation();
			sets = sets_gen;
			break;
		}
		case 'k':
		{
			vector< Set<string> > sets_key = sets_input();
			sets = sets_key;
			break;
		}
		default:
		{
			cout << "No one option choosed, program will use custom sets" << endl;
			break;
		}
	}
	
   Transversal<string> tr {sets};

    for (auto set : sets) {
        cout << set << endl;
    }

    tr.show_common_set();
    tr.show_graph();
	system("pause");
    return 0;
}

vector< Set<string> > sets_generation()
{
	srand(time(NULL));
	int num_sets = rand() % 10;
	char mask[] = "123456789";
	char ch_to_string[10];
	std::vector< Set<string> > sets(num_sets);
	int i, j, k;
	string str;
	for (i = 0; i < num_sets; i++)
	{
		k = 0;
		for (j = 0; j < 10; j++)
		{
			if (rand() % 2 == 1)
			{
				ch_to_string[k] = mask[j];
				k++;
			}
		}
		ch_to_string[k] = '\0';
		str = ch_to_string;
		sets[i] = str;
	}

	return sets;
}

vector< Set<string> > sets_input()
{
	cout << "Choose number of sets" << endl;
	int num;
	cin >> num;
	std::vector< Set<string> > sets(num);
	string str;
	for (int i = 0; i < num; i++)
	{
		cout << "Input set " << i + 1 << ": ";
		cin >> str;
		sets[i] = str;
	}
	return sets;
}