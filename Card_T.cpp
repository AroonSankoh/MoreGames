//Card_T.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for Card struct template and left shift operator << template for printing cards

#include "Card_T.h"

using namespace std;

template <typename Rank, typename Suit>
struct Card
{
    Rank rank;
    Suit suit;

    //Constructor 
    Card(Rank r, Suit s): rank(r), suit(s) {}
};

template <typename Rank, typename Suit>
ostream & operator<<(ostream& stream, const Card<Rank, Suit> &card) {
    stream << card.rank << card.suit;
    return stream;
}

template <typename Rank, typename Suit> 
bool compare_ranks(const Card<Rank, Suit> &card_1, const Card<Rank, Suit> &card_2) {
    if (static_cast<int>(card_1.rank) < static_cast<int>(card_2.rank) || (card_1.rank == card_2.rank && card_1.suit < card_2.suit)) {
        return true;
    }
    return false;
}

template <typename Rank, typename Suit> 
bool compare_suits(const Card<Rank, Suit> &card_1, const Card<Rank, Suit> &card_2) {
    if (card_1.suit < card_2.suit || (card_1.suit == card_2.suit && static_cast<int>(card_1.rank) < static_cast<int>(card_2.rank))) {
        return true;
    }
    return false;
}




