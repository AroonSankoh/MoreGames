//Card_T.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for Card struct template and left shift operator << template for printing cards
#pragma once 

#include "Suit.h"


template <typename Rank, typename Suit>
struct Card;

template <typename Rank, typename Suit>
std::ostream & operator<<(std::ostream& stream, const Card<Rank, Suit> &card);

template <typename Rank, typename Suit> 
bool compare_ranks(const Card<Rank, Suit> &card_1, const Card<Rank, Suit> &card_2);

template <typename Rank, typename Suit> 
bool compare_suits(const Card<Rank, Suit> &card_1, const Card<Rank, Suit> &card_2);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE 
#include "Card_T.cpp"
#endif






