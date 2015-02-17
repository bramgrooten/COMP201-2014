/**
 * Draw Venus and Earth in a 1024x768 window.
 *
 * Windows users: In Git Bash:
 * ~/COMP201-2014/sdl-upgrade.sh
 * cd ~/COMP201-2014/in-class
 * gmake
 * ./sdltest.exe
 * 
 * Mac users:
 * Install SDL from here: https://www.libsdl.org/release/SDL2-2.0.3.dmg
 * Install SDL_image from here: http://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.dmg
 * In Terminal:
 * cd ~/COMP201-2014/in-class
 * g++ sdltest.cpp -lSDL2main -lSDL2 -lSDL2_image -o sdltest
 */

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * Magic incantations to get SDL going
 * Return whether it worked or not
 */
bool init(SDL_Window*& window, SDL_Surface*& screenSurface, int width, int height) {
    // Init SDL
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        return false;
    }
    // Init window
    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        return false;
    }
    // Get the screen
    screenSurface = SDL_GetWindowSurface(window);
    //Initialize JPEG and PNG loading
    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        return false;
    }
    return true;
}

/**
 *  Magic incantations to get SDL to shutdown cleanly.
 */
void close(SDL_Window* window) {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/**
 *  Load an image from a file to a SDL_Surface
 */
SDL_Surface* load(SDL_Surface*& screenSurface, string path) {
    // Load image
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        return NULL;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
    
    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    
    return optimizedSurface;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    
    // Initialize SDL window and screen surface
    if ( ! init(window, screenSurface, 1024, 768) ) {
        cout << "Unable to initialize SDL. Derp!" << endl;
        return 1;
    }

    SDL_Surface* planets = load(screenSurface, "image.png");
    if (planets == NULL) {
        return 1;
    }

    // Draw to screen surface
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,
        0x00, 0x00, 0x00));
    SDL_BlitSurface( planets, NULL, screenSurface, NULL );
    
    // Show surface on screen window
    // This is when we see what we drew to the screen surface
    SDL_UpdateWindowSurface(window);
    
    // Wait around
    SDL_Delay(2000);
    
    // Free the planets allocated earlier
    SDL_FreeSurface( planets );
    close(window);
    return 0;
}
