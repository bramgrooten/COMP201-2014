#include "controller.h"

using namespace std;

Controller::Controller() {
    model = new Model(8,8);
    view = new View("Concentration!", 1024, 768);
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
    while(!model->gameOver()) {
        view->show(model);
        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_QUIT:
                return;
            case SDL_MOUSEBUTTONDOWN:
                model->flip(e.button.y / 80, e.button.x / 80);
                break;
            }
        }
    }
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