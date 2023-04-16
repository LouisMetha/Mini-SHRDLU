#pragma once

class Conjunctive : public Disjunctive {

public:
    Conjunctive(State* initial_state) : Disjunctive(initial_state) {}
    void solve() override;
    bool multiGoals();
};

void Conjunctive::solve() {

    getGoal();
    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;
    bool goalsAchieved = false;
   
    queue<vector<int>> temp_goals = goals.front();

    if (multiGoals(goals, visited, steps)) {
        cout << "\nAll goals are found within " << steps << " steps." << endl;
    } else {
        cout << "Not all goals are found within " << steps << " steps." << endl;
    }    

    while(!goalsAchieved && steps < 100) {
        
        priority_queue<Action> actions = current_state->heuristicActions(goal);

        while(!actions.empty()) {

            State* next_state = new State(*current_state);
            Action a = actions.top();
            next_state->moveBlock(a.source,a.destination);
    
            if (searchVisitedStates(visited,next_state)) {
                actions.pop();
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
        cout << "\nGOAL: (";
        for (int i = 0; i < goal.size(); i++) {
            cout << goal[i];
            if (i != goal.size() -1) cout << ", "; else cout << ") ";
        }
        cout << "is found within " << steps << " steps." << endl;
    } else {
        cout << "Goal state is NOT found within " << steps << " steps." << endl;
    }
}

bool findNextGoals() {

}