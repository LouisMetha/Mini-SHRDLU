#pragma once

class Disjunctive : public HeuristicSolver {

public:
    Disjunctive(State* initial_state) : HeuristicSolver(initial_state) {}
    void getGoal() override;
};

void Disjunctive::getGoal() {

	int block = 0;
	int row,col;
    char input = 'y';

    while (tolower(input) == 'y') {

        Goal goal;
        block = 0;
        cout << "Enter the goal (Block, row, col): ";

        while (block <= 0 || block > current_state->num_blocks) {
            cout << "\nBlock 1-" << current_state->num_blocks << " : ";
            cin >> block;
        }
        goal.block = block;

        cout << "Row 0-" << current_state->BOARDSIZE -1 << " : ";
        cin >> row;
        goal.row = row;

        cout << "Col 0-" <<  current_state->BOARDSIZE -1 << " : ";
        cin >> col;
        goal.col = col;

        goals.push(goal);

        cout << "Goal: (" << goal.block << ", "<< goal.row << ", "<< goal.col << ")" << " added.\n\n";

        cout << "Do you want to enter more goals? (y/n): ";
        cin >> input;
    }
}
