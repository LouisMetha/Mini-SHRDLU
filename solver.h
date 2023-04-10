#pragma once

#include "state.h"
#include "action.h"

class Solver {

private:
    State current_state;
    int goal[3];
    vector<State> visited;

public:
    Solver(State initial, int* goal_state) {
        current_state = initial;
        goal[0] = goal_state[0];
        goal[1] = goal_state[1];
        goal[2] = goal_state[2];
    }

    bool isGoal() {
        int block = goal[0];
        int row = goal[1];
        int col = goal[2];
        return current_state->getPos(block) == make_pair(row, col);
    }

    bool searchVisitedStates(vector<State> states, State target) {

        for (int i = 0; i < states.size(); i++) {
            if (states[i] == target) {
                return true;
            }
        }

	    return false;
    }

    void solve();
};

void Solver::solve()  {

    actions.push(Action{-1, -1, 0});

    while (!actions.empty()) {
        Action action = actions.top();
        actions.pop();
        if (action.source == -1) {
            current_state->findLegalActions(actions, goal);
            continue;
        }
        if (visited.size() >= 100) {
            cout << "Exceeded max number of steps." << endl;
            break;
        }
        if (isGoal()) {
            cout << "Found goal state." << endl;
            break;
        }
        if (find(visited.begin(), visited.end(), current_state) != visited.end()) {
            continue;
        }

        visited.push_back(current_state);
        current_state->executeMove(action.source, action.destination);
        current_state->findLegalActions(actions, goal);
    }
}