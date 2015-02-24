#include "view.h"

using namespace std;

// Initialize SDL
View::View(string title, int width, int height) {
    fail = false;
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        fail = true;
        return;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fail = true;
        return;
    }
    // Get the screen
    screen = SDL_GetWindowSurface(window);
    //Initialize JPEG and PNG loading
    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        fail = true;
        return;
    }
}

View::~View() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/**
 *  Load an image from a file to a SDL_Surface
 */
SDL_Surface* View::load(char * path) {
    // Load image
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        return NULL;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, 0 );
    
    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    
    return optimizedSurface;
}

void View::show(Model * model) {

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
        0x00, 0x00, 0x00));

    SDL_Rect dest;
    dest.w = 16;
    dest.h = 16;
    
    // TODO: I went all Atari 2600 on you guys. Perhaps you'd like to upgrade
    // the view with something nice, like a cartoon snake?
    // HINT: you'd need up, down, left, and right facing assets for:
    // the snake head, a dead head, the tail, and elbows
    // HINT: you'd of course need assets for horizontal and vertical snake sections

    // Draw food
    dest.x = model->food.x * 16;
    dest.y = model->food.y * 16;
    SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format,
            0x80, 0x00, 0x00));
    
    // Draw the snake
    for (std::list<Coordinate>::iterator it=model->snake.begin(); it!=model->snake.end(); it++) {
        dest.x = it->x * 16;
        dest.y = it->y * 16;
        SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format,
        0x00, 0x80, 0x00));
    }
    

    SDL_UpdateWindowSurface(window);
}
