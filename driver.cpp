#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

#include "action.h"
#include "state.h"
#include "solver.h"

int main() {

	srand(time(NULL));

	State* initial_state = new State();
	Solver solver(initial_state);
	solver.solve();

	delete initial_state;
	
	return 0;
}