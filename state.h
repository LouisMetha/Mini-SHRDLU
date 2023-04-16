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
	int getHeuristicValue(int source, int destination, Goal goal);
	priority_queue<Action> blindLegalActions();
	priority_queue<Action> heuristicActions(Goal goal);

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

priority_queue<Action> State::blindLegalActions() {

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

priority_queue<Action> State::heuristicActions(Goal goal) {

	priority_queue<Action> actions;
	Action action;
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (checkMove( i,j)) {
				action.source = i;
				action.destination = j;
				action.heuristic = getHeuristicValue(i,j,goal);
				actions.push(action);
			}
		}
	}


	return actions;
}

int State::getHeuristicValue(int source, int destination, Goal goal) {

	int goalblock = goal.block;
    int row = goal.row;
    int col = goal.col;
	int value = 0;
	int blocks = 0;
	int curCol, curRow;

	State newState(*this); // does not use the same memory location as the original State
	newState.moveBlock(source, destination);

	if (newState.grid[BOARDSIZE - row - 1][col] == goalblock) {
		return value += 100;
	}

	//find currenet position of goal block
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (newState.grid[BOARDSIZE - i - 1][j] == goalblock) {
				curRow = i;
				curCol = j;
				break;
			}
		}
	}

	//get value if on top of blocks
	for (int k = 0; k < BOARDSIZE; k++) {
		if (newState.grid[BOARDSIZE - k - 1][curCol] != 0) {
			blocks++;
		}
	}

	if (curRow == (blocks - 1)) {
		value += 50;
	} else {
		value += 15 - (blocks - curRow - 1)*5;
	}
	
	//get value depends on blocks to move at goal position
	blocks = 0;

	for (int n = 0; n < BOARDSIZE; n++) {
		if (newState.grid[BOARDSIZE - n - 1][col] != 0) {
			blocks++;
		}
	}

	if (blocks == row) {
		value += 35;
	} else if (blocks == row - 1) {
		value += 25;
	} else if (blocks > row){
		value += 15 - (blocks - row)*5;
	}

	return value;

}