#pragma once

class HeuristicSolver : public Solver {

public:
    HeuristicSolver(State* initial_state) : Solver(initial_state) {}
    void solve();
};

void HeuristicSolver::solve() {

    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;

    while(!checkGoal() && steps < 100) {
        
        priority_queue<Action> actions = current_state->findLegalActions();
        
        while(!actions.empty()) {

            State* next_state = new State(*current_state);
            Action a = actions.top();
            next_state->moveBlock(a.source,a.destination);

            if (searchVisitedStates(visited,next_state)) {
                actions.pop();
                if (actions.empty())
                    current_state->moveBlock(a.source,a.destination); // prevent inf-loop - brute force move
                continue;
            } else {
                int block = current_state->removeBlockFrom(a.source);
                cout << "Step " << ++steps << " : Move " << block << " from " << a.source << " to " << a.destination << endl; 
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