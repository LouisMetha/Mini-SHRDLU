#pragma once

#include "state.h"
#include "action.h"

class Solver {

private:
    State* current_state;
    vector<State*> visited;
    priority_queue<Action> actions;
    queue<Action> q;
    
    int goal[3];

public:

    Solver(State* initial_state) : current_state(initial_state) {
        getGoal();
    }

    ~Solver() {
        for (auto state : visited) {
            delete state;
        }
    }

    bool checkGoal();
    bool searchVisitedStates(State target);
    void solve();
    int* getGoal();
    void findLegalActions();
    int getHeuristicValue();
};

bool Solver::checkGoal() {
    int block = goal[0];
    int row = goal[1];
    int col = goal[2];
    return current_state->getBlock_inGoalPos(goal) == block;
}

bool Solver::searchVisitedStates(State target) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == target) {
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

	cout << "Goal: ";

	for (int i = 0; i < 3; i++) {	
		cout << goal[i];
		if (i != 2) cout << ", "; else cout << endl;
	}

	return goal;

}

void Solver::findLegalActions() {

	Action action;

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (current_state->checkMove(i,j)) {
				action.source = i;
				action.destination = j;
				action.heuristic = getHeuristicValue();
				actions.push(action);
                q.push(action);
			}
		}
	}

}

int Solver::getHeuristicValue() {

	// int count = 0;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         if (state[i][j] != goal[i][j]) {
    //             count++;
    //         }
    //     }
    // }
    // return count;

	return 1;

}

void Solver::solve()  {

    visited.push_back(current_state);
    int steps = 0;
    
    while(!checkGoal() && steps < 100) {
        findLegalActions();
        
        while(!actions.empty()) {
            State* next_state = new State(*current_state);
            next_state->executeMove(q.top());

            if (searchVisitedStates(next_state)) {
                q.pop();
                continue;
                
            } else {
                visited.push_back(next_state);
                delete next_state;

            }
            cout << "Step: " << ++steps << endl;
            current_state->printBoard();
        }
        

    }
}
