#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>
#include <string.h>

using namespace std;

#include "action.h"
#include "state.h"
#include "solver.h"
#include "heuristicSolver.h"
#include "disjunctive.h"
#include "conjunctive.h"

int main() {

	srand(time(NULL));

	State* initial_state = new State();
	
	// Solver solver(initial_state);
	// solver.solve();
	
	// HeuristicSolver h(initial_state);
	// h.solve();

	// Disjunctive d(initial_state);
	// d.solve();

	// Conjunctive c(initial_state);
	// c.solve();

	delete initial_state;

	return 0;
}