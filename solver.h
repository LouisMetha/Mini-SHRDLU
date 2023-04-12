#pragma once

class Solver {

protected:
    State* current_state;
    int goal[3];

public:
    Solver(State* initial_state) : current_state(initial_state) {
        cout << "--- Initial State ---\n\n";
        current_state->printBoard();
        getGoal();
    }
    ~Solver() {}
    bool checkGoal();
    bool searchVisitedStates(list<State*>& states,State* target) const;
    virtual void solve();
    int* getGoal();
};

bool Solver::checkGoal() {
    int block = goal[0];
    int row = goal[1];
    int col = goal[2];

    return current_state->getGoalBlock(row,col) == block;
}

bool Solver::searchVisitedStates(list<State*>& states, State* target) const {

    for (State* state : states) {
        if (*state == *target) {
            return true;
        }
    }
    return false;
}

int* Solver::getGoal() {

	int block = 0;
	int row,col;

	cout << "Enter the goal (Block, row, col): ";

	while (block <= 0) {
		cout << "\nBlock 1-6 : ";
		cin >> block;
		goal[0] = block;
	}

	cout << "Row 0-2 : ";
	cin >> row;
	goal[1] = row;

	cout << "Col 0-2 : ";
	cin >> col;
	goal[2] = col;

	cout << "Goal: (";

	for (int i = 0; i < 3; i++) {	
		cout << goal[i];
		if (i != 2) cout << ", "; else cout << ")\n" << endl;
	}

	return goal;
}

void Solver::solve()  {

    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;
    int num_visits = 0;

    while(!checkGoal() && steps < 100) {
        
        priority_queue<Action> actions = current_state->findLegalActions();

        while(!actions.empty()) {

            State* next_state = new State(*current_state);
            Action a = actions.top();
            next_state->moveBlock(a.source,a.destination);
    
            if (searchVisitedStates(visited,next_state)) {
                actions.pop();
                num_visits++;

                // prevent inf-loop - brute force move
                if (num_visits == 50) { 
                    current_state->moveBlock(a.source,a.destination); 
                    cout << "Step " << ++steps << " : Move " << current_state->getBlock() << " from " << a.source << " to " << a.destination << endl; 
                    current_state->printBoard();
                    num_visits = 0;
                }
                continue;
            } else {
                cout << "Step " << ++steps << " : Move " << next_state->getBlock() << " from " << a.source << " to " << a.destination << endl; 
                visited.push_back(next_state);
                current_state = next_state;
                current_state->printBoard();
                break;
            }
        }
    }

    if (checkGoal()) {
        cout << "Goal state is found within " << steps << " steps." << endl;
    } else {
        cout << "Goal state is NOT found within " << steps << " steps." << endl;
    }
}
