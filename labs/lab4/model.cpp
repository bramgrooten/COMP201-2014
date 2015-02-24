#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model(int h, int w) {
    height = h;
    width = w;
    currentState = NO_MATCH;
    lastRow.push_back(0);
    lastRow.push_back(0);
    lastColumn.push_back(0);
    lastColumn.push_back(0);
    grid = new char*[height];
    visible = new char*[height];
    // For every row, create the array for that row
    for (int i = 0; i < height; i++) {
        grid[i] = new char[width];
        visible[i] = new char[width];
    }
    char letter = 'A';
    // Guarantee pairs of characters in the grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = letter;
            // Everything's invisible at first
            visible[i][j] = '_';
            // Every other iteration...
            if (j % 2 == 1) {
                letter++;
                if (letter > 'Z') {
                    letter = 'A';
                }
            }
        }
    }
    // Seed random number generator with time
    srand(time(0));
    // Randomize
    int otheri, otherj;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Pick a random spot in the grid
            otheri = rand() % height;
            otherj = rand() % width;
            // Swap grid[i][j] with grid[otheri][otherj]
            letter = grid[i][j];
            grid[i][j] = grid[otheri][otherj];
            grid[otheri][otherj] = letter;
        }
    }
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
    for (int i = 0; i < height; i++) {
        delete grid[i];
        delete visible[i];
    }
    delete grid;
    delete visible;
}
// Is the row/column valid?
// That is, is the row within the height, and is the column within the width?
// Return whether it is or isn't.
// TO DO: click on already guessed spot should not be valid (to avoid cheating)
bool Model::valid(int row, int column) {
    if (visible[row][column]!='_') {
        return false;
    }
    if (row<height && column<width && row>=0 && column >= 0) {
        return true;
    }
    return false;
}
bool Model::matched(int row, int column) {
    return true;
}
// Flip a cell
void Model::flip(int row, int column) {
    // If the row and column are not valid, break out and don't do anything
    if (!valid(row, column)) { return; }
    // We are selecting the next "cell" to flip
    // If the last cell and the current cell match, great!
    // Otherwise, make the last cell invisible (set it to *)
    // Make the current cell visible
    switch (currentState) {
        case NO_MATCH:
            visible[lastRow[0]][lastColumn[0]] = '_';
            visible[lastRow[1]][lastColumn[1]] = '_';
            visible[row][column] = grid[row][column];
            lastRow[0]=lastRow[1];
            lastColumn[0]=lastColumn[1];
            lastRow[1]=row;
            lastColumn[1]=column;
            currentState = FIRST;
            break;
        case FIRST:
            if (grid[row][column]==grid[lastRow[1]][lastColumn[1]]) {
                currentState = MATCH;
                visible[row][column] = grid[row][column];
                lastRow[0] = lastRow[1];
                lastColumn[0] = lastColumn[1];
                lastRow[1] = row;
                lastColumn[1] = column;
            } else {
                currentState = NO_MATCH;
                visible[row][column] = grid[row][column];
                lastRow[0] = lastRow[1];
                lastColumn[0] = lastColumn[1];
                lastRow[1] = row;
                lastColumn[1] = column;
            }
            break;
        case MATCH:
            visible[row][column] = grid[row][column];
            lastRow[0] = lastRow[1];
            lastColumn[0] = lastColumn[1];
            lastRow[1] = row;
            lastColumn[1] = column;
            currentState = FIRST;
            break;
    }
}
// If everything is visible, then it's game over
bool Model::gameOver() {
    // Assume the game is over
    bool isOver = true;
    // Loop through the grid and see if any element is not visible
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (visible[i][j] == '_') {
                isOver = false;
            }
        }
    }
    
    if (isOver) {
        // Set a nice game over message
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                visible[i][j] = '_';
            }
        }
        visible[1][2] = 'Y';
        visible[1][3] = 'O';
        visible[1][4] = 'U';
        visible[2][2] = 'W';
        visible[2][3] = 'I';
        visible[2][4] = 'N';
    }
    return isOver;
}
int Model::getWidth() {
    return width;
}
int Model::getHeight() {
    return height;
}
char Model::get(int row, int col) {
    return visible[row][col];
}
