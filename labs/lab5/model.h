#include <list>

#ifndef _MODEL_H
#define _MODEL_H

enum Direction { UP, DOWN, LEFT, RIGHT, DEAD };

typedef struct {
    unsigned int x;
    unsigned int y;
} Coordinate;

// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    Model(int w, int h);
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Which way should the snake face?
    void go(Direction d);
    // Move foward one
    void crawl();
    // Is the game over?
    bool gameOver();
    // The snake
    std::list<Coordinate> snake;
    // The food
    Coordinate food;
    // Which way is the snake moving?
    Direction direction;
    // What's the width?
    int width;
    // What's the height?
    int height;
};

#endif