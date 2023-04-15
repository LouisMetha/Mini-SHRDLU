#pragma once

class Solver {

protected:
    State* current_state;
    queue<vector<int>> goals;
    int num_blocks = 6;

public:
    Solver(State* initial_state) : current_state(initial_state) {
        cout << "--- Initial State ---\n\n";
        current_state->printBoard();

    }
    ~Solver() {}
    bool checkGoal(vector<int> goal);
    bool searchVisitedStates(list<State*>& states,State* target) const;
    virtual void solve();
    virtual void getGoal();
};

bool Solver::checkGoal(vector<int> goal) {

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

void Solver::getGoal() {

    vector<int> goal;
	int block = 0;
	int row,col;
    char input = 'y';
        
    cout << "Enter the goal (Block, row, col): ";

    while (block <= 0 || block > num_blocks) {
        cout << "\nBlock 1-6 : ";
        cin >> block;
    }
    goal.push_back(block);

    cout << "Row 0-2 : ";
    cin >> row;
    goal.push_back(row);

    cout << "Col 0-2 : ";
    cin >> col;
    goal.push_back(col);

    goals.push(goal);

    cout << "Goal: (";
    for (int i = 0; i < BOARDSIZE; i++) {	
        cout << goal[i];
        if (i != BOARDSIZE -1) cout << ", "; else cout << ") ";
    }
}

void Solver::solve()  {

    getGoal();
    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;
    int num_visits = 0;
   
    vector<int> goal = goals.front();

    for (int i = 0; i < goal.size(); i++) {
        cout << "GOAL:";
        cout << goal[i] << ", ";
    }

    while(!checkGoal(goal) && steps < 100) {
        
        priority_queue<Action> actions = current_state->blindLegalActions();

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

    if (checkGoal(goal)) {
        cout << "Goal state is found within " << steps << " steps." << endl;
    } else {
        cout << "Goal state is NOT found within " << steps << " steps." << endl;
    }
}
