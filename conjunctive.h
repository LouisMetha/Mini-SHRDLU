#pragma once

class Conjunctive : public Disjunctive {

public:
    Conjunctive(State* initial_state) : Disjunctive(initial_state) {}
    void solve() override;
    bool checkMultiGoals(priority_queue<Goal>& goals, list<State*>& visited, int& steps);
    list<Goal> prev_goals;
};

void Conjunctive::solve() {

    getGoal();
    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;
   
    priority_queue<Goal> temp_goals = goals;

    if (checkMultiGoals(temp_goals, visited, steps)) {
        cout << "\nAll goals are found within " << steps << " steps.\n\n";
    } else {
        cout << "\nNot all goals are found within " << steps << " steps.\n\n";
    }
}

bool Conjunctive::checkMultiGoals(priority_queue<Goal>& goals, list<State*>& visited, int& steps) {

    if (goals.empty()) {
        return true;
    }

    int matched_goals = 0;
    int num_visits = 0;
    Goal goal = goals.top();
    prev_goals.push_back(goal);
    goals.pop();

    while (steps < 5000) {

        priority_queue<Action> actions = current_state->heuristicActions(goal);
        
        while (!actions.empty()) {

            State* next_state = new State(*current_state);
            Action a = actions.top();
            next_state->moveBlock(a.source, a.destination);

            if (searchVisitedStates(visited, next_state)) {
                actions.pop();
                num_visits++;
                
                // prevent inf-loop - brute force move
                if (num_visits == 50) { 
                    priority_queue<Action> temp_actions = current_state->blindLegalActions();
                    a = temp_actions.top();
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

        for (list<Goal>::iterator it = prev_goals.begin(); it != prev_goals.end(); ++it) {
            if (checkGoal(*it)) {
                matched_goals++;
            } else {
                matched_goals = 0;
                break; // break if one of the checked goals are out of position, then try next action.
            }
        }

        // check if all pervious checked goals are in correct position, if true >> call checkMultiGoals() again.
        if (matched_goals == prev_goals.size()) {
            
            cout << "Goal: (" << goal.block << ", "<< goal.row << ", "<< goal.col << ") ";
            cout << "is found within " << steps << " steps." << endl;

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
