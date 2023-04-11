#pragma once

const int BOARDSIZE = 3;

class State {
private:
	int grid[BOARDSIZE][BOARDSIZE] = {};
	vector<int> numbers{ 0,0,0,1,2,3,4,5,6 };
	int passBlock;

public:
 
	State() {
		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				int temp = rand() % numbers.size();
				grid[i][j] = numbers[temp];
				numbers.erase(numbers.begin() + temp);
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

	int getBlock() {
		return passBlock;
	}

	void printBoard();
	void pushDown();
	int removeBlockFrom(int column);
	bool insertBlockTo(int column, int value);
	bool moveBlock(int source, int destination);
	bool checkMove(int source, int destination);
	int getGoalBlock(int row, int col);
	int getHeuristicValue();
	priority_queue<Action> findLegalActions();

};

void State::printBoard() {

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (grid[i][j] == 0) {
				cout << "| " << " " << " ";

			} else {
				cout << "| " << grid[i][j] << " ";
			}
		}
		cout << "|\n";
	}
	cout << " --- --- --- \n\n";

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
		if (grid[i][column] != 0){
			tempStack.push(grid[i][column]);
		}
	}

	if (tempStack.size() == 0) {
		return 0;
	}

	for (int k = 0; k < BOARDSIZE; k++) {
		if (tempStack.empty() == true) {
			grid[BOARDSIZE - k - 1][column] = 0;

		} else if (tempStack.size() == 1) {			// replace last element of stack with 0 then pop it
			grid[BOARDSIZE - k - 1][column] = 0;
			topBlock = tempStack.top();
			tempStack.pop();
			
		} else {
			grid[BOARDSIZE - k - 1][column] = tempStack.top();
			tempStack.pop();
		}
	}

	return topBlock;
}

bool State::insertBlockTo(int column, int value) {

	stack<int> tempStack;
	
	tempStack.push(value);	

	for (int i = 0; i < BOARDSIZE; i++) {
		if (grid[i][column] != 0) {
			tempStack.push(grid[i][column]);
		}
	}

	if (tempStack.size() > BOARDSIZE) { // if size of 4 = cannot add a block on top
		return false;
	}

	for (int k = 0; k < BOARDSIZE; k++) {
		if (tempStack.empty() == true) {
			grid[BOARDSIZE - k - 1][column] = 0;
		} else {
			grid[BOARDSIZE - k - 1][column] = tempStack.top();
			tempStack.pop();
		}
	}

	return true;
}

bool State::moveBlock(int source, int destination) {

	if (source == destination)
		return false;

	int block = removeBlockFrom(source);
	passBlock = block;
	
	if (!insertBlockTo(destination, block)) {
		insertBlockTo(source,block);
		return false;
	}

	return true;
}

bool State::checkMove(int source, int destination) {

	if (source == destination)
		return false;

	int block = removeBlockFrom(source);

	if (!insertBlockTo(destination, block) || block <= 0) {
		insertBlockTo(source,block);
		return false;
	}
	
	return insertBlockTo(source,removeBlockFrom(destination));
}

int State::getGoalBlock(int row, int col) {

	int block = grid[BOARDSIZE - row - 1][col];
	return block;
}

priority_queue<Action> State::findLegalActions() {

	priority_queue<Action> actions;
	Action action;
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (checkMove( i,j)) {
				action.source = i;
				action.destination = j;
				action.heuristic = rand() % (BOARDSIZE*BOARDSIZE);
				actions.push(action);
			}
		}
	}

	return actions;
}




