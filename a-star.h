#include <queue>

class Node {
    public:
        int** state;
        int g; // Cost to reach this node from start node
        int h; // Heuristic value of this node
        Node* parent;

        Node(int** state, int g, int h, Node* parent) {
            this->state = state;
            this->g = g;
            this->h = h;
            this->parent = parent;
        }

        ~Node() {
            // Free memory allocated for state
        }
};

struct CompareNodes {
    bool operator()(Node* n1, Node* n2) {
        return (n1->g + n1->h) > (n2->g + n2->h);
    }
};

void a_star(int** start_state, int** goal_state, int n) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> frontier;
    std::unordered_set<int**> explored;

    Node* start_node = new Node(start_state, 0, manhattan_distance(start_state, goal_state, n), nullptr);
    frontier.push(start_node);

    while(!frontier.empty()) {
        Node* current_node = frontier.top();
        frontier.pop();

        if(is_goal_state(current_node->state, goal_state, n)) {
            print_solution(current_node);
            break;
        }

        explored.insert(current_node->state);

        std::vector<Action> actions = get_actions(current_node->state, n);
        for(Action action : actions) {
            int** child_state = apply_action(current_node->state, action, n);

            if(explored.count(child_state) > 0) {
                // State already explored, skip it
                delete_state(child_state, n);
                continue;
            }

            Node* child_node = new Node(child_state, current_node->g + 1, manhattan_distance(child_state, goal_state, n), current_node);
            frontier.push(child_node);
        }
    }
}
