//CardSet_T.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for CardSet class template 

#pragma once

#include "Card_T.h"
#include <iostream>
#include <vector>
#include <functional>

template <typename Rank, typename Suit>
class CardSet {
    protected: 
        std::vector< Card<Rank, Suit> > pile;

    public: 
        void print(ostream& stream, size_t len);
        CardSet() = default;
        CardSet(const CardSet<Rank, Suit> &copy);
        CardSet<Rank, Suit>& operator>>(CardSet<Rank, Suit>& c_set);
        std::back_insert_iterator <std::vector <Card <Rank, Suit> > > inserter();
        typename std::vector< Card <Rank, Suit> >::iterator get_front();
        typename std::vector< Card <Rank, Suit> >::iterator get_back();
        void sort_set();
        Card<Rank, Suit> get_card(int index);
        unsigned int size();
        bool is_empty();
        void collect(CardSet<Rank, Suit>& c_set);
        void collect_if(CardSet<Rank, Suit>& deck, std::function<bool(Card<Rank, Suit>&)> pred);
        bool request(CardSet<Rank, Suit>& c_set, Rank r);

        typedef Card <Rank, Suit> card_type;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE 
#include "CardSet_T.cpp"
#endif


