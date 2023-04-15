#pragma once

class HeuristicSolver : public Solver {

public:
    HeuristicSolver(State* initial_state) : Solver(initial_state) {}
    virtual void solve();
};

void HeuristicSolver::solve()  {

    getGoal();
    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;
    

    while (!goals.empty()) {

        vector<int> goal = goals.front();
        cout << "\nGOAL:";
        for (int i = 0; i < goal.size(); i++) {
            cout << goal[i];
            if (i != goal.size() -1) cout << ", "; else cout << ") \n";
        }

        while(!checkGoal(goal) && steps < 5) {
        
        priority_queue<Action> actions = current_state->heuristicActions(goal);

            while(!actions.empty()) {

                State* next_state = new State(*current_state);
                Action a = actions.top();
                next_state->moveBlock(a.source,a.destination);
        
                if (searchVisitedStates(visited,next_state)) {
                    actions.pop();
                    continue;
                } else {
                    cout << "Step " << ++steps << " : Move " << next_state->getBlock() 
                    << " from " << a.source << " to " << a.destination << endl; 
                    visited.push_back(next_state);
                    current_state = next_state;
                    current_state->printBoard();
                    break;
                }
            }
        }

        if (checkGoal(goal)) {
            cout << "Goal state is found within " << steps << " steps." << endl;
            break;
        } else {
            cout << "Goal state is NOT found within " << steps << " steps." << endl;
        }

        goals.pop();
        steps = 0;
    }



}