#include "controller.h"
#include <map>

using namespace std;

Controller::Controller() {
    model = new Model(8,8);
    view = new View("Snake", 1024, 768);
}

Controller::~Controller() {
    delete model;
    delete view;
}
/**
References:
https://wiki.libsdl.org/SDL_PollEvent
https://wiki.libsdl.org/SDL_Event
*/
void Controller::loop() {
    SDL_Event e;
    unsigned int lastTime = 0, currentTime;
    std::map<SDL_Keycode, Direction> direction;
    direction[SDLK_UP] = UP;
    direction[SDLK_DOWN] = DOWN;
    direction[SDLK_LEFT] = LEFT;
    direction[SDLK_RIGHT] = RIGHT;

    while(!model->gameOver()) {
        currentTime = SDL_GetTicks();
        // Crawl (move) once every 100 milliseconds
        if (currentTime > lastTime + 100) {
            model->crawl();
            lastTime = currentTime;
        }
        view->show(model);
        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) {
                case SDLK_DOWN:
                case SDLK_UP:
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    model->go(direction[e.key.keysym.sym]);
                break;
                default:
                break;
                }
            case SDL_MOUSEBUTTONDOWN:
                break;
            }
        }
    }
    // TODO: show something nice?
    view->show(model);
    SDL_Delay(3000);
}

/*
// Show the board
// Read in coordinates
// Until we're done
void Controller::loop() {
    int row, col;
    while (!model->gameOver()) {
        view->show(model);
        cout << "Enter row:    ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        model->flip(row, col);
    }
    cout << "Hooray, you win!" << endl;
}
*/