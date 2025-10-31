#ifndef CONFIG_H
#define CONFIG_H

// ==================== Simulation Settings ====================
// Change these values to control the path shape, resolution, and start/end positions
constexpr float INNER_RADIUS = 7.0f;           // Inner radius of the circular path
constexpr float OUTER_RADIUS = 10.0f;          // Outer radius of the circular path
constexpr unsigned int NODES_HORIZONTAL = 128; // Number of nodes along the direction of travel
constexpr unsigned int NODES_VERTICAL = 24;    // Number of nodes in the radial direction

constexpr unsigned int NODE_START_X = 0;                    // Starting node (x-index)
constexpr unsigned int NODE_START_Y = NODES_VERTICAL - 1;   // Starting node (y-index)
constexpr unsigned int NODE_END_X = NODES_HORIZONTAL - 1;   // Goal node (x-index)
constexpr unsigned int NODE_END_Y = NODES_VERTICAL - 1;     // Goal node (y-index)

constexpr float ANGLE = 3.14159f; // Total angle of the path in radians (pi -> semicircle, 2pi -> full circle)

// ==================== Renderer Settings ====================
// Change this value to scale the rendered coordinates to window size
constexpr float scaler = 11.0f;

#endif // CONFIG_H
