#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// This is an enumeration of possible suits
enum Suit { HEARTS, CLUBS, DIAMONDS, SPADES };
// This is an array of C strings
string suit_names[] = { "Hearts", "Clubs", "Diamonds", "Spades" };
// This is an enumeration of all possible ranks
enum Rank {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
};
// This is an array of C strings
string rank_names[] = {
    "2", "3", "4", "5", "6", "7", "8", "9", "10",
    "Jack", "Queen", "King", "Ace"
};
// A card is a suit and a rank
typedef struct {
    // Type variable_name
    Suit suit;
    // Type variable_name
    Rank rank;
} Card;

// Prints out a card in the form: Ace of Spades
// return_type identifier (ParameterType parameter, ...) 
// Switch is when you have one variable / expression
// and you want to do something different each possible value.
void printCard(Card card) {
    cout << rank_names[card.rank];
    cout << " of ";
    cout << suit_names[card.suit];
}

vector<Card> makeDeck() {
    // create a vector of Cards
    vector<Card> deck;
    Card card;
    // Create a deck of cards
    // for every possible suit,
    for (int i = 0; i < 4; i++) {
        // for every possible rank,
        for (int j = 0; j < 13; j++) {
            card.suit = (Suit) i; // typecast 
            card.rank = (Rank) j; // typecast
            deck.push_back(card);
        }
    }
    // return the vector
    return deck;
}

// How do we shuffle stuff?
void shuffle(vector<Card> & cards) {
    // just use the fancy library. :-)
    random_shuffle(cards.begin(), cards.end());
    random_shuffle(cards.rbegin(), cards.rend());
    random_shuffle(cards.begin(), cards.end());
    random_shuffle(cards.rbegin(), cards.rend());
}

int main() {
    // type name; // declares a variable
    int age;
    string name;
    
    vector<Card> deck = makeDeck();
    srand(time(0));
    shuffle(deck);
    
    for (int i = 0; i < deck.size(); i++) {
        printCard(deck[i]);
        cout << endl;
    }
    
    // The compiler still uses ints behind the scenes
    // But now we can't shoot ourselves in the foot
    Card card;
    
    // variable = some_value;
    card.rank = JACK;
    card.suit = DIAMONDS;
    
    printCard(card);
    
    return 0;
}