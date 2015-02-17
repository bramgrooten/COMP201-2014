// Defining your own types
#include <iostream>
#include <vector>
// Silly randomness
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

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

// return_type identifier(parameters, ...);
vector<Card> makeDeck() {
    // create a vector
    vector<Card> deck;
    // create all the cards
    Card card;
    // for each suit,..
    for (int i = 0; i < 4; i++) {
        // for each rank,...
        for (int j = 0; j < 13; j++) {
            // create the appropriate card
            card.suit = (Suit) i; // type cast, FTW
            card.rank = (Rank) j;
            // push it into the vector
            deck.push_back(card);
        }
    }
    // return the vector
    return deck;
}

// Type
// variable
// CONSTANT

int main() {
    // type variable_name; // Declare a variable
    int age;
    string name;
    
    // We'll need to define makeDeck()
    vector<Card> deck = makeDeck();
    
    for (int i = 0; i < deck.size(); i++) {
        printCard(deck[i]);
        cout << endl;
    }
    
    return 0;
}

// return_type identifier (ParameterType param, ...)
// How about "Ace of Spades"
void printCard(Card card) {
    cout << rank_names[card.rank] << " of "
        << suit_names[card.suit];
}
