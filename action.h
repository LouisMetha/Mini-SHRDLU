#pragma once

class Action {
    public:
        int source;
        int destination;
        int heuristic;

    bool operator<(const Action a) const {
        if(heuristic < a.heuristic)
            return true;
        else
            return false;
    }
};