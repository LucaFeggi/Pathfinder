#ifndef INPUT_H
#define INPUT_H

#include <array>

#include "SDL.h"

enum Commands{
    QUIT = 0,
    RENDER,
    TOTAL
};

class Input{
public:
    void poll(const SDL_Event &event);
    bool is_command_active(const Commands comm) const;
    void set_command_active(const Commands comm);
    void set_command_inactive(const Commands comm);
private:
    std::array<bool, Commands::TOTAL> command{};
};

#endif // !INPUT_H
