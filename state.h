#pragma once

const int BOARDSIZE = 3;

class State {
private:
	int grid[BOARDSIZE][BOARDSIZE] = {};
	vector<int> numbers{ 0,0,0,1,2,3,4,5,6 };
	vector<vector<int>> legalActions;
	int tempGrid[BOARDSIZE][BOARDSIZE] = {};

public:
 
	State() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int temp = rand() % numbers.size();
				grid[i][j] = numbers[temp];
				numbers.erase(numbers.begin() + temp);
			}
		}
		pushDown();
	}

	State(int test_grid[BOARDSIZE][BOARDSIZE]) {
		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				grid[i][j] = test_grid[i][j];
			}
    	}
		pushDown();
	}

	bool operator==(State s) {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				if (s.grid[i][j] != grid[i][j])
					return false;
		return true;
	}

	bool operator!=(State s) {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				if (s.grid[i][j] != grid[i][j])
					return true;
		return false;
	}

	void printBoard();
	bool checkMatch(int (*list)[3]);
	void pushDown();
	int removeBlockFrom(int column);
	bool insertBlockTo(int column, int value);
	bool moveBlock(int source, int destination);
	void findLegalActions();

};

void State::printBoard() {

	cout << " --- --- --- \n";
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			cout << "| " << grid[i][j] << " ";
		}
		cout << "|\n";
	}
	cout << " --- --- --- \n";

}

bool State::checkMatch(int (*list)[3]) {	 

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (grid[i][j] != list[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void State::pushDown() {

	stack<int> tempStack;

	for (int i = 0; i < BOARDSIZE; i++) {

		for (int j = 0; j < BOARDSIZE; j++) {
			if (grid[j][i] != 0){
				tempStack.push(grid[j][i]);
			}
		}

		for (int k = 0; k < BOARDSIZE; k++) {
			if (tempStack.empty() == true) {
				grid[BOARDSIZE - k - 1][i] = 0;
			} else {
				grid[BOARDSIZE - k - 1][i] = tempStack.top();
				tempStack.pop();
			}
		}
	}
}

int State::removeBlockFrom(int column) {

	stack<int> tempStack;
	int topBlock;

	for (int i = 0; i < BOARDSIZE; i++) {
		if (tempGrid[i][column] != 0){
			tempStack.push(tempGrid[i][column]);
		}
	}

	if (tempStack.size() == 0) {
		cout << "removeBlockFrom: Empty stack.\n";
		return -1;
	}

	for (int k = 0; k < BOARDSIZE; k++) {
		if (tempStack.empty() == true) {
			tempGrid[BOARDSIZE - k - 1][column] = 0;

		} else if (tempStack.size() == 1) {			// replace last element of stack with 0 then pop it
			tempGrid[BOARDSIZE - k - 1][column] = 0;
			topBlock = tempStack.top();
			tempStack.pop();
			
		} else {
			tempGrid[BOARDSIZE - k - 1][column] = tempStack.top();
			tempStack.pop();
		}
	}

	return topBlock;
	
}

bool State::insertBlockTo(int column, int value) {

	stack<int> tempStack;
	
	tempStack.push(value);	

	for (int i = 0; i < BOARDSIZE; i++) {
		if (tempGrid[i][column] != 0) {
			tempStack.push(tempGrid[i][column]);
		}
	}

	if (tempStack.size() > BOARDSIZE) { // if size of 4 = cannot add a block on top
		cout << "\nFALSE\n";
		return false;
	}

	for (int k = 0; k < BOARDSIZE; k++) {
		if (tempStack.empty() == true) {
			tempGrid[BOARDSIZE - k - 1][column] = 0;

		} else {
			tempGrid[BOARDSIZE - k - 1][column] = tempStack.top();
			tempStack.pop();
		}
	}

	return true;
}

bool State::moveBlock(int source, int destination) {

	tempGrid = grid;

	if (!insertBlockTo(destination, removeBlockFrom)) {
		insertBlockTo(source,block);
		return false;
	}

	return true;
}

void State::findLegalActions() {

	vector<int> legalActions;
	stack<int> tempStack;

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {

			if (grid[j][i] != 0)
				tempStack.push(grid[j][i]);
		}

	
		



	}



}



