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

int main() {

	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		State state;
		state.printBoard();
		state.findLegalActions();
		state.executeMove();
		state.printBoard();
	}

	return 0;
}