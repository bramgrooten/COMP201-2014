#include <iostream>
#include <ctime>

using namespace std;
// ANSI escape code to clear screen
// Concentration game model
// The model manages the state of the game
class Model {
public:
    // Methods (member functions)
    // Initialize a grid of letters randomly
    Model(int w, int h);
    // Return the width
    int getWidth();
    // Return the height
    int getHeight();
    // Return visible stuff (invisible stuff is shown with character *)
    char get(int row, int column);
    // Flip this row/column
    void flip(int row, int column);
    // Is the game over?
    bool gameOver();
private:
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
    int lastRow;
    int lastColumn;
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
        model = new Model(10,10);
        view = new View;
    }
    // Event loop
    // Read in coordinates
    // Show the board
    // Until we're done
    void loop();
private:
    Model * model;
    View * view;
};

Model::Model(int w, int h) {
    width = w;
    height = h;
    grid = new char*[h];
    visible = new char*[h];
    for (int i = 0; i < height; i++) {
        grid[i] = new char[w];
        visible[i] = new char[w];
    }
    // TODO: make this random-ish
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = 'a';
            visible[i][j] = '*';
        }
    }
}

// Make this row, column temporarily visible
// Returns true if we did a flip and the previous match matches the given row, column
bool Model::flip(int row, int column) {
    
}

// If everything is visible, then game over
bool Model::gameOver() {
    return false;
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

void View::show(Model * model) {
    for (int i = 0; i < model->getHeight(); i++) {
        for (int j = 0; j < model->getWidth(); j++) {
            cout << model->get(i, j);
        }
        cout << endl;
    }
}

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
}

int main() {
    Controller c;
    c.loop();
}
