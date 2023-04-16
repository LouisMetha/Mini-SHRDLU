#pragma once

class Conjunctive : public Disjunctive {
private:
    list<vector<int>> prev_goals;
public:
    Conjunctive(State* initial_state) : Disjunctive(initial_state) {}
    void solve() override;
    bool checkMultiGoals(queue<vector<int>>& goals, list<State*>& visited, int& steps);
};

void Conjunctive::solve() {

    getGoal();
    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;
   
    queue<vector<int>> temp_goals = goals;

    if (checkMultiGoals(temp_goals, visited, steps)) {
        cout << "\nAll goals are found within " << steps << " steps.\n\n";
    } else {
        cout << "\nNot all goals are found within " << steps << " steps.\n\n";
    }
}

bool Conjunctive::checkMultiGoals(queue<vector<int>>& goals, list<State*>& visited, int& steps) {

    if (goals.empty()) {
        return true;
    }

    int matched_goals = 0;
    vector<int> goal = goals.front();
    prev_goals.push_back(goal);
    goals.pop();

    while (steps < 100) {

        priority_queue<Action> actions = current_state->heuristicActions(goal);

        while (!actions.empty()) {

            State* next_state = new State(*current_state);
            Action a = actions.top();
            next_state->moveBlock(a.source, a.destination);

            if (searchVisitedStates(visited, next_state)) {
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

        for (list<vector<int>>::iterator it = prev_goals.begin(); it != prev_goals.end(); ++it) {
            if (checkGoal(*it)) {
                matched_goals++;
            } else {
                matched_goals = 0;
                break; // break if one of the checked goals are out of position, then try next action.
            }
        }

        // check if all pervious checked goals are in correct position, if true >> call checkMultiGoals() again.
        if (matched_goals == prev_goals.size()) {
            
            for (int i = 0; i < goal.size(); i++) {
                if (i == 0) cout << "\nGOAL: (";
                cout << goal[i];
                if (i != goal.size() - 1) cout << ", "; else cout << ") is found within " << steps << " steps." << endl;
            }

            if (checkMultiGoals(goals, visited, steps)) {
                return true;
            } else {
                steps--;
                visited.pop_back();
                prev_goals.pop_back();
                current_state = visited.back();
            }
        }
    }

    return false;
}
