#include "renderer.hpp"

#include "../config.hpp"

#include <string>
#include <stdexcept>

Renderer::Renderer(const Window &window)
    : window(window)
{
    ptr = SDL_CreateRenderer(window.get_ptr(), -1, SDL_RENDERER_ACCELERATED);
    if(ptr == nullptr) throw std::runtime_error(std::string("Failed to create renderer: ") + SDL_GetError());
}

Renderer::~Renderer(){
    SDL_DestroyRenderer(ptr);
}

void Renderer::render(const A_Star &a_star){
    SDL_SetRenderDrawColor(ptr, 0, 0, 0, 255);
    SDL_RenderClear(ptr);

    const std::vector<std::vector<std::pair<float, float>>> &nodes = a_star.get_node_coordinates();
    const std::vector<std::pair<int, int>> &path = a_star.get_path();

    // dynamic scaling based on window size
    int w, h;
    SDL_GetWindowSize(window.get_ptr(), &w, &h);
    int center_x = w / 2;
    int center_y = h / 2;
    int viewport = center_x < center_y ? center_x : center_y;
    float scale = viewport / scaler;

    // drawing grid points
    SDL_SetRenderDrawColor(ptr, 255, 255, 255, 255);
    for(size_t y = 0; y < nodes.size(); ++y){
        for(size_t x = 0; x < nodes[y].size(); ++x){
            int drawX = static_cast<int>(center_x + nodes[y][x].first * scale);
            int drawY = static_cast<int>(center_y - nodes[y][x].second * scale);
            SDL_RenderDrawPoint(ptr, drawX, drawY);
        }
    }

    // drawing path
    if(a_star.path_found()){
        SDL_SetRenderDrawColor(ptr, 255, 0, 0, 255);
        for(size_t i = 1; i < path.size(); ++i){
            // getting grid coords (x first, y second)
            int x1 = path[i - 1].first;
            int y1 = path[i - 1].second;
            int x2 = path[i].first;
            int y2 = path[i].second;

            // getting respective world coords and scaling them to window world for rendering
            int xA = static_cast<int>(center_x + nodes[y1][x1].first * scale);
            int yA = static_cast<int>(center_y - nodes[y1][x1].second * scale);
            int xB = static_cast<int>(center_x + nodes[y2][x2].first * scale);
            int yB = static_cast<int>(center_y - nodes[y2][x2].second * scale);

            SDL_RenderDrawLine(ptr, xA, yA, xB, yB);
        }
    }

    SDL_RenderPresent(ptr);
}
