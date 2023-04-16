#pragma once

class Goal {
    public:
        int block;
        int row;
        int col;

    bool operator<(const Goal g) const {
        if(row > g.row)
            return true;
        else
            return false;
    }
};