//CardSet_T.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for CardSet class template 

#include "CardSet_T.h"

using namespace std;

template<typename Rank, typename Suit>
void CardSet<Rank, Suit>::print(ostream& stream, size_t line_break) {
    for (unsigned int i = 0; i < pile.size(); ++i) { 
        if (i % line_break == 0 ) {
            stream << endl;
        }
        stream << pile[i] << ", "; 
    }
    stream << endl;
}

template<typename Rank, typename Suit> 
CardSet<Rank, Suit>::CardSet(const CardSet<Rank, Suit> &copy) {
    pile = copy.pile;
}

/*
* >> template operator takes a CardSet and shifts cards from the implicit CardSet to the passed 
* CardSet if the the implicit CardSet isn't empty, otherwise it throws run_time error
*
* @param CardSet<Rank, Suit>& the CardSet to shift cards into 
* @return the implicit CardSet
*/
template<typename Rank, typename Suit> 
CardSet<Rank, Suit>& CardSet<Rank, Suit>::operator>>(CardSet<Rank, Suit>& c_set) {
    if ( this->pile.empty() ) {
        throw runtime_error("Pile of implicit cardset is empty.");
    }
    else {
        c_set.pile.push_back(this->pile.back());
        this->pile.pop_back();
    }
    return *this;
}

template<typename Rank, typename Suit> 
back_insert_iterator <vector <Card <Rank, Suit> > > CardSet<Rank, Suit>::inserter() {
    back_insert_iterator<vector <Card <Rank, Suit> > > back_insert(CardSet<Rank, Suit>::pile);
    return back_insert;
}

template<typename Rank, typename Suit>
typename vector< Card <Rank, Suit> >::iterator CardSet<Rank, Suit>::get_front() {
    return this->pile.begin();
}

template<typename Rank, typename Suit>
typename vector< Card <Rank, Suit> >::iterator CardSet<Rank, Suit>::get_back() {
    return this->pile.end();
}

template<typename Rank, typename Suit>
void CardSet<Rank, Suit>::sort_set() {
    sort(this->get_front(), this->get_back(), compare_ranks<Rank, Suit>);
}

template<typename Rank, typename Suit> 
Card<Rank, Suit> CardSet<Rank, Suit>::get_card(int index) {
    return this->pile[index];
}

template<typename Rank, typename Suit>
unsigned int CardSet<Rank, Suit>::size() {
    return pile.size();
}

template<typename Rank, typename Suit>
bool CardSet<Rank, Suit>::is_empty() {
    if (size() == 0 ) {
        return true;
    }
    else {
        return false;
    }
}

template<typename Rank, typename Suit>
void CardSet<Rank, Suit>::collect(CardSet<Rank, Suit>& c_set) {
    move(c_set.get_front(), c_set.get_back(), this->inserter());
    c_set.pile.clear();
}

/*
* collect_if(CardSet<Rank, Suit>& deck, std::function<bool(Card<Rank, Suit>&)> pred)
* Uses the predicate to determine which card rank to collect from the passed in cardset, and then 
* moves cards of those rank from the passed in cardset to the implicit cardset 
*
* @param deck the passed in cardset 
* @param pred the the predicate
*/
template<typename Rank, typename Suit> 
void CardSet<Rank, Suit>::collect_if(CardSet<Rank, Suit>& deck, std::function<bool(Card<Rank, Suit>&)> pred) {
    copy_if(deck.get_front(), deck.get_back(), this->inserter(), pred);
    CardSet<Rank, Suit> dup; 
    for (typename vector< Card< Rank, Suit> >:: iterator i = deck.get_front(); i != deck.get_back(); ++i) {
        if (i->rank != (this->get_back()- 1)->rank) {
            copy(i, i+1, dup.inserter());
        }
    }
    deck = move(dup);
}

/*
* request(CardSet<Rank, Suit>& c_set, Rank r)
* Takes in a cardset and a predicate and uses the predicate to transfer cards of a certain 
* rank from the passed in cardset to the implicit cardset
*
* @param c_set the passed in cardset 
* @param r the specific rank
*/
template<typename Rank, typename Suit> 
bool CardSet<Rank, Suit>::request(CardSet<Rank, Suit>& c_set, Rank r) {
    function<bool(Card<Rank, Suit>&)> matching_rank = [r](Card<Rank, Suit>& card) {
        return card.rank == r;
    };
    typename vector< Card< Rank, Suit> >::iterator i = find_if(c_set.get_front(), c_set.get_back(), matching_rank); 
    if (i != c_set.get_back()) {
        copy(i, i + 1, this->inserter());
        CardSet<Rank, Suit> dup;
        for (typename vector< Card< Rank, Suit> >::iterator j = c_set.get_front(); j != c_set.get_back(); ++j) {
            if (j != i) {
                copy(j, j+1, dup.inserter());
            }
        }
        c_set = move(dup);
        return true;
    }
    else {
        return false;
    }
}

