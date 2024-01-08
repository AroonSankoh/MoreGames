//Deck_T.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for Deck class template

#include "Deck_T.h"
#include <random>
#include <algorithm>

template<typename Rank, typename Suit>
void Deck<Rank, Suit>::shuffle() {
    random_device seed;
    mt19937 num_generator(seed());
    std::shuffle(CardSet<Rank, Suit>::pile.begin(), CardSet<Rank, Suit>::pile.end(), num_generator);
}


