/**
 * Draw a white square in a 640x480 window.
 * Windows users: You already went through the pain of setting this all up.
 * g++ sdltest.cpp -lmingw32 -lSDL2main -lSDL2 -w -Wl,-subsystem,windows -o sdltest.exe
 * Mac users: First, install SDL from here: https://www.libsdl.org/release/SDL2-2.0.3.dmg
 * g++ sdltest.cpp -lSDL2main -lSDL2 -o sdltest
 */

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    
    // Init SDL
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        cout << "Couldn't initialize SDL: " << SDL_GetError() << endl;
        return 1;
    }
    
    // Init window
    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Couldn't create window: " << SDL_GetError() << endl;
        return 1;
    }
    
    // Draw the screen
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,
        0xff, 0xff, 0xff));
    
    // Technically, this is when the drawing happens...
    SDL_UpdateWindowSurface(window);
    
    // Wait around
    SDL_Delay(2000);
    
    // kthxbye
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}