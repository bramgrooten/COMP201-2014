#include "model.h"
#include "view.h"

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

// Handle input
class Controller {
public:
    Controller();
    ~Controller();
    // Event loop
    void loop();
private:
    Model * model;
    View * view;
};
#endif