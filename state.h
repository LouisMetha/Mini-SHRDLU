#pragma once

class State {
private:
	vector<vector<int>> grid;
	vector<int> numbers;
	int passBlock;

public:

	int num_blocks = 6;
	int BOARDSIZE = 3;

	State() {

		grid.resize(BOARDSIZE, vector<int>(BOARDSIZE));
        numbers.resize(BOARDSIZE * BOARDSIZE);
		fill(numbers.begin(), numbers.end(), 0);
		
		for (int i = 1; i <= num_blocks; i++) {
   			numbers[i] = i;
		}
		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				int temp = rand() % numbers.size();
				grid[i][j] = numbers[temp];
				numbers.erase(numbers.begin() + temp);
			}
		}
		pushDown();
	}
 
	State(int size, int n) : BOARDSIZE(size),num_blocks(n) {
		
		grid.resize(size, vector<int>(size));
        numbers.resize(size * size);
		fill(numbers.begin(), numbers.end(), 0);
		
		for (int i = 1; i <= num_blocks; i++) {
   			numbers[i] = i;
		}

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
	priority_queue<Action> legalActions();
	priority_queue<Action> legalActions(Goal goal);
};

void State::printBoard() {

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (grid[i][j] == 0) {
				cout << "| " << " " << "  ";

			} else {
				if (grid[i][j] < 10)
					cout << "| " << grid[i][j] << "  ";
				else
					cout << "| " << grid[i][j] << " ";

			}
		}
		cout << "|\n";
	}

	for (int i = 0; i < BOARDSIZE; i++)
		cout << " ----";
	cout << "\n\n";
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

	int topBlock = 0;

	for (int i = 0; i < BOARDSIZE; i++) {
		if (grid[i][column] != 0){
			topBlock = grid[i][column];
			grid[i][column] = 0;
			break;
		}
	}

	if (topBlock == 0)
		return 0;

	return topBlock;
}

bool State::insertBlockTo(int column, int value) {

	for (int i = 0; i < BOARDSIZE; i++) {
		if (grid[BOARDSIZE - i - 1][column] == 0) {
			grid[BOARDSIZE - i - 1][column] = value;
			return true;
		}
	}

	return false;
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

priority_queue<Action> State::legalActions() {

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

priority_queue<Action> State::legalActions(Goal goal) {

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

	int blocks = 0;
	int curCol, curRow;
	int value = 100;

	State newState(*this); // does not use the same memory location as the original State
	newState.moveBlock(source, destination);

	if (newState.grid[BOARDSIZE - goal.row - 1][goal.col] == goal.block) {
		return value;
	}

	//find currenet position of goal block
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (newState.grid[BOARDSIZE - i - 1][j] == goal.block) {
				curRow = i;
				curCol = j;
				break;
			}
		}
	}

	for (int k = 0; k < BOARDSIZE; k++) {
		if (newState.grid[BOARDSIZE - k - 1][curCol] != 0) {
			blocks++;
		}
	}

	if (curRow == (blocks - 1)) {
		value -= 50;
		value += (curRow)*1;
	} else if (blocks > curRow ) {
		value -= 50 + 15 * (blocks - curRow);
	}
	
	blocks = 0;
	for (int n = 0; n < BOARDSIZE; n++) {
		if (newState.grid[BOARDSIZE - n - 1][goal.col] != 0) {
			blocks++;
		}
	}

	if (blocks > goal.row) {
		value -= (blocks - goal.row) * 9; 
	}

	return value;
}