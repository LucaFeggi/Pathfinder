#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

enum Commands{
    QUIT = 0,
    RENDER,
    TOTAL
};

class Input{
public:
    Input() noexcept;
    void poll(const SDL_Event &event);
    bool is_command_active(const Commands comm) const;
    void set_command_active(const Commands comm);
    void set_command_inactive(const Commands comm);
private:
    bool command[Commands::TOTAL];
};

#endif // !INPUT_H
