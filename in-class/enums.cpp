#include <iostream>
#include <string>

using namespace std;

// TODO: Have a vector<Card>
// TODO: We want to shuffle said cards

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

int main() {
    // type name; // declares a variable
    int age;
    string name;
    
    // The compiler still uses ints behind the scenes
    // But now we can't shoot ourselves in the foot
    Card card;
    
    // variable = some_value;
    card.rank = JACK;
    card.suit = DIAMONDS;
    
    printCard(card);
    
    return 0;
}