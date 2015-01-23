// Defining your own types
#include <iostream>

using namespace std;

// TODO: vector<Card>
// shuffling a deck of cards
// drawing cards
// drawing cards onto the screen

// This is an enumeration
// It defines a type, along with the possibilities
enum Suit { HEARTS, SPADES, CLUBS, DIAMONDS };
// Array of suit names
const string suit_names[] = {
    "Hearts", "Spades", "Clubs", "Diamonds"
};
// Each possibility must be an identifier (legit name)
enum Rank {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
};
// Array of rank names
const string rank_names[] = {
    "2", "3", "4", "5", "6", "7", "8", "9", "10",
    "Jack","Queen", "King", "Ace"
};
// Defines a type, called Card
// It consists of a suit and a rank
typedef struct {
    // type variable;
    Suit suit;
    // type variable;
    Rank rank;
} Card;

// Forward declaration
void printCard(Card card);

// Type
// variable
// CONSTANT

int main() {
    // type variable_name; // Declare a variable
    int age;
    string name;
    
    Card card;
    
    // variable = some_value;
    card.suit = SPADES;
    card.rank = ACE;
    
    printCard(card);
    
    return 0;
}

// return_type identifier (ParameterType param, ...)
// How about "Ace of Spades"
void printCard(Card card) {
    cout << rank_names[card.rank] << " of "
        << suit_names[card.suit] << endl;
}
