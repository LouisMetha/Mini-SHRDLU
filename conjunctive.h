#pragma once

class Conjunctive : public Disjunctive {

public:
    Conjunctive(State* initial_state) : Disjunctive(initial_state) {}
    void solve() override;
    bool checkMultiGoals(priority_queue<Goal>& goals, list<State*>& visited, int& steps);
};

void Conjunctive::solve() {

    getGoal();
    list<State*> visited;
    visited.push_back(current_state);
    int steps = 0;

    if (checkMultiGoals(goals, visited, steps)) {
        cout << "\nAll goals are found within " << steps << " steps.\n\n";
    }
}

bool Conjunctive::checkMultiGoals(priority_queue<Goal>& goals, list<State*>& visited, int& steps) {

    int num_visits = 0;

    while (!goals.empty()) {

        Goal goal = goals.top();
        priority_queue<Action> actions = current_state->legalActions(goal);
        
        while (!actions.empty()) {

            State* next_state = new State(*current_state);
            Action a = actions.top();
            next_state->moveBlock(a.source, a.destination);

            if (searchVisitedStates(visited, next_state)) {
                actions.pop();
                num_visits++;
                
                // prevent inf-loop - force a move
                if (num_visits == 50) { 
                    priority_queue<Action> temp_actions = current_state->legalActions();
                    a = temp_actions.top();
                    current_state->moveBlock(a.source,a.destination);
                    cout << "Step " << ++steps << " : Move " << current_state->getBlock() << " from " << a.source << " to " << a.destination << " with Heuristic: " << a.heuristic << endl; 
                    current_state->printBoard();
                    num_visits = 0;
                }
                continue;
            } else {
                cout << "Step " << ++steps << " : Move " << next_state->getBlock() << " from " << a.source << " to " << a.destination << " with Heuristic: " << a.heuristic << endl; 
                visited.push_back(next_state);
                current_state = next_state;
                current_state->printBoard();
                break;
            }
        }

        if (checkGoal(goal)) {
            goals.pop();
            cout << "Goal: (" << goal.block << ", "<< goal.row << ", "<< goal.col << ") ";
            cout << "is found within " << steps << " steps.\n" << endl;
        }
    }

    return true;
}