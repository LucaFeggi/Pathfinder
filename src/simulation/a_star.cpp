#include "a_star.hpp"

#include "../config.hpp"

#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>

struct Node{
    int x;      // grid coord
    int y;      // grid coord
    float f;
    bool operator>(const Node &other) const { return f > other.f; }
};

// The actual Parent pr stores its parent's coords.
// For instance, if pr = (20, 10) and its parent were (19, 10), pr.x = 19, pr.y = 10.
// pr's son will be son.x = 20, son.y = 10
struct Parent{
    int x;  // parent node grid coord x
    int y;  // parent node grid coord y
    bool has_parent;
};

A_Star::A_Star() noexcept : found{ false } {}

void A_Star::run(){

    // setting the grid points coordinates
    node_coords.assign(NODES_VERTICAL, std::vector<std::pair<float, float>>(NODES_HORIZONTAL));
    for(int y = 0; y < NODES_VERTICAL; ++y) {
        float radius = INNER_RADIUS + (OUTER_RADIUS - INNER_RADIUS) * y / float(NODES_VERTICAL - 1);
        for(int x = 0; x < NODES_HORIZONTAL; ++x) {
            float theta = ANGLE * x / float(NODES_HORIZONTAL - 1);
            float X = radius * std::cos(theta);
            float Y = radius * std::sin(theta);
            node_coords[y][x] = std::make_pair(X, Y);
        }
    }

    // function to calculate euclidean distace
    auto euclidean_dist = [&](int x1, int y1, int x2, int y2) -> float{
        float xA = node_coords[y1][x1].first;
        float yA = node_coords[y1][x1].second;
        float xB = node_coords[y2][x2].first;
        float yB = node_coords[y2][x2].second;
        return std::hypot(xB - xA, yB - yA);
    };

    // heuristic function for the algorithm (basically the euclidean distance from actual_node to end_node)
    auto heuristic = [&](int x, int y) -> float{
        return euclidean_dist(x, y, NODE_END_X, NODE_END_Y);
    };

    const int dx[8] = { -1, 1, 0, 0, -1, 1, -1, 1 };    // directions x
    const int dy[8] = { 0, 0, -1, 1, -1, -1, 1, 1 };    // directions y

    // initializing 2d vectors for calculations
    // every g_score and f_score node is set to infinity by default, since we haven't still reached any node yet
    // g_score is the cost (distance) from the start node to each node 
    std::vector<std::vector<float>> g_score(NODES_VERTICAL, std::vector<float>(NODES_HORIZONTAL, std::numeric_limits<float>::infinity()));
    // f score = g score + heuristic, the final score that the algorithm uses to choose the next node
    std::vector<std::vector<float>> f_score(NODES_VERTICAL, std::vector<float>(NODES_HORIZONTAL, std::numeric_limits<float>::infinity()));
    // visited is to know if a node has been visited or not
    std::vector<std::vector<bool>> visited(NODES_VERTICAL, std::vector<bool>(NODES_HORIZONTAL, false));
    // parent is a 2d vector of parents used for path reconstruction
    std::vector<std::vector<Parent>> parent(NODES_VERTICAL, std::vector<Parent>(NODES_HORIZONTAL, { -1, -1, false }));

    g_score[NODE_START_Y][NODE_START_X] = 0.0f;
    f_score[NODE_START_Y][NODE_START_X] = heuristic(NODE_START_X, NODE_START_Y);

    // A priority_queue is used for the open set to achieve O(log n) time complexity,
    // compared to O(n) if a plain array were used.
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;
    open_set.push({ NODE_START_X, NODE_START_Y, f_score[NODE_START_Y][NODE_START_X] });

    found = false;

    // main A* search loop
    while(!open_set.empty()){

        // take the node with the lowest f_score from the open set
        Node current = open_set.top();
        open_set.pop();

        int cx = current.x;
        int cy = current.y;

        // skip if this node was already visited; otherwise, mark it as visited
        if(visited[cy][cx])
            continue;
        visited[cy][cx] = true;

        // goal reached; exit the search
        if(cx == NODE_END_X && cy == NODE_END_Y){
            found = true;
            break;
        }

        // explore all 8 neighbors and update their scores if a better path is found
        for(int d = 0; d < 8; ++d){
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            // skip neighbors that are out of grid bounds
            if(ny < 0 || ny >= NODES_VERTICAL || nx < 0 || nx >= NODES_HORIZONTAL)
                continue;

            /// compute cost to move to neighbor and tentative g_score
            float cost = euclidean_dist(cx, cy, nx, ny);
            float tentative_g = g_score[cy][cx] + cost; // cost to reach this neighbor if we go through the current node

            // If moving to this neighbor provides a shorter path to the end_node than any previously known path,
            // update scores, parent, and add it to the open set
            if(tentative_g < g_score[ny][nx]){
                g_score[ny][nx] = tentative_g;
                f_score[ny][nx] = tentative_g + heuristic(nx, ny);
                parent[ny][nx].x = cx;
                parent[ny][nx].y = cy;
                parent[ny][nx].has_parent = true;
                open_set.push({ nx, ny, f_score[ny][nx] }); // nodes are automatically ordered by the priority_queue based on their f_scores
            }
        }
    }

    // path reconstruction
    path.clear();
    if(!found) return;

    // going from the end_node to the start_node when reconstructing the path
    int cx = NODE_END_X, cy = NODE_END_Y;
    while(!(cx == NODE_START_X && cy == NODE_START_Y)){
        path.push_back(std::make_pair(cx, cy));
        if(!parent[cy][cx].has_parent)
            break;
        int px = parent[cy][cx].x;
        int py = parent[cy][cx].y;
        cx = px;
        cy = py;
    }
    path.push_back(std::make_pair(NODE_START_X, NODE_START_Y));

    //  std::reverse(path.begin(), path.end());
    //  The reverse is not necessary, but is the correct thing to do if you want the path "from start to end".
    //  Without the reverse, the path is "from end to start".
    //  Note: the reverse operation has time complexity O(n).
}

// getters for rendering
const std::vector<std::vector<std::pair<float, float>>> &A_Star::get_node_coordinates() const{
    return node_coords;
}

const std::vector<std::pair<int, int>> &A_Star::get_path() const{
    return path;
}

bool A_Star::path_found() const{
    return found;
}
