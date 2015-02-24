
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "model.h"
#include <map>
#include <string>

#ifndef _VIEW_H
#define _VIEW_H

// Show (output) the state of the model
class View {
public:
    View(std::string title, int width, int height);
    ~View();
    // Print out the visible stuff in the grid
    void show(Model * model);
private:
    SDL_Window* window;
    SDL_Surface* screen;
    bool fail;
    SDL_Surface* load(char * path);
};
#endif