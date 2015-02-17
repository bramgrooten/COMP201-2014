//
//  main.cpp
//  lab3
//
//  Created by Bram Joris Grooten on 2/3/15.
//  Copyright (c) 2015 Bram Joris Grooten. All rights reserved.
//


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

enum State { FIRST, MATCH, NO_MATCH };

// To clear the screen, look up ANSI escape codes
// Concentration game model
// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    // Initialize a grid of letters randomly
    Model(int w, int h);
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Methods (member functions)
    // Return the width
    int getWidth();
    // Return the height
    int getHeight();
    // Returns the turn
    int getTurn();
    // Increment turn
    void increaseTurn();
    // Return visible stuff (invisible stuff is shown with character *)
    char get(int row, int column);
    // Flip this row/column
    void flip(int row, int column);
    // Is the game over?
    bool gameOver();
private:
    // Is the row/column valid?
    bool valid(int row, int column);
    // Fields (member data)
    // Randomly generated grid. This has pairs of characters in it
    char ** grid;
    // What is visible to the user?
    char ** visible;
    // What's the width?
    int width;
    // What's the height?
    int height;
    // What'd we flip last?
    int lastRow, last2Row;
    int lastColumn, last2Column;
    int turn = 0;
    State currentState;
};

// Show (output) the state of the model
class View {
public:
    // Print out the visible stuff in the grid
    void show(Model * model);
};

// Handle input
class Controller {
public:
    Controller() {
        model = new Model(2,4);
        view = new View;
    }
    ~Controller() {
        delete model;
        delete view;
    }
    // Event loop
    void loop();
private:
    Model * model;
    View * view;
};

// Constructor initializes the object
Model::Model(int h, int w) {
    width = w;
    height = h;
    last2Row = -1;
    last2Column = -1;
    lastRow = -1;
    lastColumn = -1;
    currentState = NO_MATCH;
    grid = new char*[height];
    visible = new char*[height];
    // For every row, create the (column)array for that row
    for (int i = 0; i < height; i++) {
        grid[i] = new char[width];
        visible[i] = new char[width];
    }
    // Initializes the random number generator
    srand(time(0));
    // Made this random-ish
    // Look at asciitable.com and do some stuff with rand() % number
    // Hint: insert characters in order, then shuffle later in a separate loop
    vector<char> letters;
    vector<int> lettersCount;
    int numberLettersNeeded, alphabets=0;
    if (width*height%2!=0) {
        cout << "Board doesn't have an even number of spots!" << endl;
        exit(1);
    }
    numberLettersNeeded = width*height/2;
    for (int i=0; i<numberLettersNeeded; i++) {
        if (i>25) {
            alphabets = i/26;
            letters.push_back(char(65+i-alphabets*26));
            lettersCount.push_back(0);
        } else {
            letters.push_back(char(65+i));
            lettersCount.push_back(0);
        }
    }
    // int randNum = rand()%(max-min + 1) + min;
    int randNum = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            randNum = rand()%(numberLettersNeeded);
            visible[i][j] = '*';
            if (lettersCount[randNum]<2) {
                grid[i][j] = letters[randNum];
                lettersCount[randNum]++;
            } else {
                for (int k=numberLettersNeeded-1; k>=0; k--) {
                    // this could be better
                    // better, meaning, more random
                    if (lettersCount[k]<2) {
                        grid[i][j] = letters[k];
                        lettersCount[k]++;
                        break;
                    }
                }
            }
        }
    }
    // Shuffle (even more)
    int otheri, otherj;
    char temp;
    for (int i=0; i< height; i++) {
        for (int j=0; j < width; j++) {
            // Pick a random spot in grid
            otheri =rand() % height;
            otherj =rand() % width;
            // Swap grid[i][j] with grid[otheri][otherj]
            temp = grid[i][j];
            grid[i][j] = grid[otheri][otherj];
            grid[otheri][otherj] = temp;
        }
    }
}

// Destructor deletes dynamically allocated memory
Model::~Model() {
    // Delete inner arrays (columns)
    for (int i = 0; i < height; i++) {
        delete grid[i];
        delete visible[i];
    }
    // Delete outer arrays (rows)
    delete grid;
    delete visible;
}

// Is the row/column valid?
// That is, is the row within the height, and is the column within the width?
// Return whether it is or isn't.
bool Model::valid(int row, int column) {
    if (row==lastRow && column==lastColumn) {
        cout << "You just guessed the same spot!" << endl;
        return false;
    } else if (visible[row][column]!='*') {
        cout << "That spot is already visible." << endl;
        return false;
    } else if (row<height && column<width && row>=0 && column >= 0) {
        return true;
    }
    return false;
}

// Flips a cell
void Model::flip(int row, int column) {
    // If the row and column are not valid, break out and don't do anything
    while (!valid(row, column)) {
        cout << "That's not a valid spot, try again: " << endl;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> column;
    }
    // We are selecting the next "cell" to flip
    // If the last cell and the current cell match, great!
    // Otherwise, make the last cell invisible (set it to *)
    // Make the current cell visible
    switch (currentState) {
        case NO_MATCH:
            if (turn > 0) {
                if (turn > 1) {
                visible[last2Row][last2Column] = '*';
                }
                visible[lastRow][lastColumn] = '*';
            }
            visible[row][column] = grid[row][column];
            last2Row = lastRow;
            last2Column = lastColumn;
            lastRow = row;
            lastColumn = column;
            currentState = FIRST;
            break;
        case FIRST:
            if (grid[row][column]==grid[lastRow][lastColumn]) {
                currentState = MATCH;
                visible[row][column] = grid[row][column];
                last2Row = lastRow;
                last2Column = lastColumn;
                lastRow = row;
                lastColumn = column;
            } else {
                currentState = NO_MATCH;
                visible[row][column] = grid[row][column];
                last2Row = lastRow;
                last2Column = lastColumn;
                lastRow = row;
                lastColumn = column;
            }
            break;
        case MATCH:
            visible[row][column] = grid[row][column];
            last2Row = lastRow;
            last2Column = lastColumn;
            lastRow = row;
            lastColumn = column;
            currentState = FIRST;
            break;
    }
}

// If everything is visible, then it's game over
bool Model::gameOver() {
    // Hint: assume the game is over, unless it isn't
    // Hint: Loop through the grid and see if any element is not visible
    for (int i = 0; i<height; i++) {
        for(int j=0;j<width;j++){
            if (visible[i][j]=='*'){
                return false;
            }
        }
    }
    return true;
}

int Model::getWidth() {
    return width;
}
int Model::getHeight() {
    return height;
}
char Model::get(int row, int col) {
    // you can test if constructor works by switching "visible" to "grid" here
    return visible[row][col];
}
// Turn
int Model::getTurn() {
    return turn;
}
// IncrementTurn
void Model::increaseTurn() {
    turn++;
}

// Show the model, one cell at a time
void View::show(Model * model) {
    for (int j = 0; j < model->getWidth(); j++) {
        cout << "\t" << j;
    }
    cout << endl;
    for (int i = 0; i < model->getHeight(); i++) {
        cout << i;
        for (int j = 0; j < model->getWidth(); j++) {
            cout << "\t" << model->get(i, j);
        }
        cout << endl;
    }
}


// Show the board
// Read in coordinates
// Until we're done
void Controller::loop() {
    int row, col;
    while (!model->gameOver()) {
        view->show(model);
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        // a lot of endl's to "make sure" the user can't see his/her previous board and kinda cheat ;)
        cout << endl << endl << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl << endl << endl;
        model->flip(row, col);
        model->increaseTurn();
    }
    cout << "Hooray, you win!" << endl;
    cout << "You finished in " << model->getTurn() << " turns." << endl;
    view->show(model);
}

int main() {
    Controller c;
    c.loop();
    return 0;
}

