#pragma once

class Disjunctive : public HeuristicSolver {

private:
    unordered_map<int, int> goalRecords;
    vector<int> tempBlock;

public:
    Disjunctive(State* initial_state) : HeuristicSolver(initial_state) {}
    void getGoal() override;
    void checkExtraGoal();
    
};

void Disjunctive::getGoal() {

	int block, row, col;
    char input = 'y';
    Goal goal;

    while (tolower(input) == 'y') {

        block = 0;
        row = -1;
        col = -1;

        cout << "Enter the goal (Block, row, col): ";

        while (block <= 0 || block > current_state->num_blocks || (find(tempBlock.begin(), tempBlock.end(), block) != tempBlock.end())) {
            cout << "Invalid block - not in range or already selected!\n";
            cout << "\nBlock 1-"<< current_state->num_blocks << " : ";
            cin >> block;
        }
        goal.block = block;
        tempBlock.push_back(block);

        while (row < 0 || row > current_state->BOARDSIZE - 1) {
            cout << "Row 0-" << current_state->BOARDSIZE - 1 << " : ";
            cin >> row;
        
        }
        goal.row = row;
        

        while (col < 0 || col > current_state->BOARDSIZE - 1) {
            cout << "Col 0-" << current_state->BOARDSIZE - 1 << " : ";
            cin >> col;
        
        }
        goal.col = col;

        if (!goalRecords.count(col) || goalRecords[col] > row) {
            goalRecords[col] = row;
        }


        goals.push(goal);

        cout << "Goal: (" << goal.block << ", "<< goal.row << ", "<< goal.col << ")" << " added.\n\n";

        cout << "Do you want to enter more goals? (y/n): ";
        cin >> input;

        if (tolower(input) != 'y') {
            checkExtraGoal();
        }
    }
}

void Disjunctive::checkExtraGoal() {

    Goal goal;

    for (int i = 0; i < current_state->BOARDSIZE; i++)
        if (goalRecords.count(i) > 0) {
            for (int j = 0; j < goalRecords[i]; j++) {

                for (int k = 1; k <= current_state->num_blocks; k++) {
                    if (!(find(tempBlock.begin(), tempBlock.end(), k) != tempBlock.end())) {
                        goal.block = k;
                        tempBlock.push_back(k);
                        break;
                    }
                } 

                goal.col = i;
                goal.row = j;
                goals.push(goal);
                cout << "Added extra goal. " << goal.block << " " << goal.row << " " << goal.col << endl;
            }
        }
}
