/*
Student ID: 18142222, Name: Ritthikiet Methaviriyavanich

I hereby certify that no other part of this submission has been copied from any
other sources, including the Internet, books or other student’s work, or
generated from generative AI tools, such as ChatGPT except the ones I have
listed below:
	n/a
I hold a copy of this assignment that I can produce if the original is lost or
damaged.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>
#include <string.h>
#include <unordered_map>

using namespace std;

#include "goal.h"
#include "action.h"
#include "state.h"
#include "solver.h"
#include "heuristicSolver.h"
#include "disjunctive.h"
#include "conjunctive.h"

int getSize();
int getBlocks(int size);

int main() {

	srand(time(NULL));

    int choice;
    cout << "Choose an option to run:\n";
    cout << "1. Single goal solver without heuristics\n";
    cout << "2. Single goal solver with heuristics\n";
    cout << "3. Disjunctive goal solver\n";
    cout << "4. Conjunctive goal solver\n";
    cout << "5. Conjunctive goal solver on size*size board\n";
	cout << "7. Quit\n";
    cin >> choice;

	State* initial_state;

	switch (choice) {
		case 1: {
			initial_state = new State();
			Solver s(initial_state);
			s.solve();
			break;
		}
		case 2: {
			initial_state = new State();
			HeuristicSolver h(initial_state);
			h.solve();
			break;
		}
		case 3: {
			initial_state = new State();
			Disjunctive d(initial_state);
			d.solve();
			break;
		}
		case 4: {
			initial_state = new State();
			Conjunctive c(initial_state);
			c.solve();
			break;
		}
		case 5: {
			int size = getSize();
			initial_state = new State(size,getBlocks(size));
			Conjunctive c(initial_state);
			c.solve();
			break;
		}

		case 7: {
			break;
		}
		default: {
			break;
		}
	}

	delete initial_state;
	return 0;
}

int getSize() {

	int BOARDSIZE = 0;
	cout << "Enter the size of board: ";
	cin >> BOARDSIZE;

	return BOARDSIZE;
}

int getBlocks(int size) {

	int n = 0;
	cout << "Enter the number of blocks: ";
	cin >> n;

	while (n <= size || n > (size*size - size)) {
		cout << "The number of blocks must be between " << size << " and " << size*size - size << endl;
		cout << "Enter the number of blocks again: ";
		cin >> n;
		cout << endl;
	}

	return n;
}