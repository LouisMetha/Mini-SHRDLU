#pragma once

class Solver {

protected:
    State* current_state;
    priority_queue<Goal> goals;

public:
    Solver(State* initial_state) : current_state(initial_state) {
        cout << "\n--- Initial State ---\n\n";
        current_state->printBoard();

    }
    ~Solver() {}
    bool checkGoal(Goal goal);
    bool searchVisitedStates(list<State*>& states,State* target) const;
    virtual void solve();
    virtual void getGoal();
};

bool Solver::checkGoal(Goal goal) {

    int block = goal.block;
    int row = goal.row;
    int col = goal.col;

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

    Goal goal;
	int block = 0;
	int row = -1;
    int col = -1;
    char input = 'y';
        
    cout << "Enter the goal (Block, row, col): ";

    while (block <= 0 || block > current_state->num_blocks) {
        cout << "\nBlock 1-"<< current_state->num_blocks << " : ";
        cin >> block;
    }
    goal.block = block;

    while (row < 0 || row > current_state->BOARDSIZE - 1) {
        cout << "Row 0-" << current_state->BOARDSIZE - 1 << " : ";
        cin >> row;
    
    }
    goal.row = row;

    while (col < 0 || col > current_state->BOARDSIZE - 1) {
        cout << "Col 0-" << current_state->BOARDSIZE - 1 << " : ";
        cin >> col;
    
    }
    goal.col = col;

    goals.push(goal);

    cout << "Goal: (" << goal.block << ", "<< goal.row << ", "<< goal.col << ")\n\n";

}

void Solver::solve()  {

    getGoal();
    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;
    int num_visits = 0;
   
    Goal goal = goals.top();

    while(!checkGoal(goal) && steps < 100) {
        
        priority_queue<Action> actions = current_state->legalActions();

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
