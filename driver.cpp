#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

#include "state.h"

int main() {

	srand(time(NULL));

	State state;
	list<State> lists;

	int from, to;
	state.printBoard();
	// cout << "from which col? ";
	// cin >> from;
	// cout << "to which col?";
	// cin >> to;
	// state.moveBlock(from, to);
	// state.printBoard();
	state.findLegalActions();

	return 0;
}