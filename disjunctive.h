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

        vector<int> goal;
        block = 0;
        cout << "Enter the goal (Block, row, col): ";

        while (block <= 0 || block > num_blocks) {
            cout << "\nBlock 1-6 : ";
            cin >> block;
        }
        goal.push_back(block);

        cout << "Row 0-2 : ";
        cin >> row;
        goal.push_back(row);

        cout << "Col 0-2 : ";
        cin >> col;
        goal.push_back(col);

        goals.push(goal);

        cout << "\nGoal: (";
        for (int i = 0; i < BOARDSIZE; i++) {	
            cout << goal[i];
            if (i != 2) cout << ", "; else cout << ") ";
        }
        cout << "added.\n\n";

        cout << "Do you want to enter more goals? (y/n): ";
        cin >> input;
    }
}
