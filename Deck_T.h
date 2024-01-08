//Deck_T.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for Deck class template
#pragma once 

#include "CardSet_T.h"
#include "iostream"

template <typename Rank, typename Suit>
class Deck: public CardSet<Rank, Suit> {
    public:
        void shuffle();
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE 
#include "Deck_T.cpp"
#endif




