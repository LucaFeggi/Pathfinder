#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include <utility>

/*
Note: The algorithm is implemented using cartesian coordinates rather than polar coordinates, even though the path is circular.
This allows the path to be modeled conceptually as a circle while treating it as a regular cartesian path for distance calculations.
Furthermore, this approach facilitates extending the algorithm to handle full circuits with arbitrary shapes,
since the underlying computations are not tied to a specific coordinate system.
Finally, it avoids complications with angular wrapping and variable arc lengths that would be necessary in a polar coordinate system.
*/

class A_Star{
public:
    A_Star() noexcept;
    void run();
    // Data accessors for rendering
    const std::vector<std::vector<std::pair<float, float>>> &get_node_coordinates() const;
    const std::vector<std::pair<int, int>> &get_path() const;
    bool path_found() const;
private:
    std::vector<std::vector<std::pair<float, float>>> node_coords; // 2D grid of points, each point has a (x,y) coord
    std::vector<std::pair<int, int>> path;  // 2D vector to store the grid points (just the indices, not the coords) for the path
    bool found;
};

#endif // !A_STAR_H
