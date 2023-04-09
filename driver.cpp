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

	State state;

	int from, to;
	state.printBoard();
	// cout << "from which col? ";
	// cin >> from;
	// cout << "to which col?";
	// cin >> to;
	// state.moveBlock(from, to);
	// state.printBoard();
	state.findLegalActions();
	state.executeMove();
	state.printBoard();

	return 0;
}