//HoldEmGame.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for HoldEmGame class and associated functions

#include "HoldEmGame.h"

using namespace std;

HoldEmGame::HoldEmGame(int argc, const char* argv[]): Game(argc, argv) {
    state = HoldEmState::preflop;
    for (unsigned int i = 0; i < names.size(); ++i) {
        CardSet<HoldEmRank, Suit> hand;
        hands.push_back(hand);
    }
}

void HoldEmGame::preflop_deal() {
    for (int i = 0; i < preflop_card_count; ++i) {
        for (unsigned int j = 0; j < names.size(); ++j) {
            try {
                deck >> hands[j];
            }
            catch (const exception& e) {
                cerr << "Exception Caught: " << e.what() << endl;
            }
        }
    }
}

void HoldEmGame::deal() {
    switch (state) {
        case HoldEmState::preflop: 
            preflop_deal();
            state = HoldEmState::flop;
            break;
        case HoldEmState::flop: 
            try {
                deck >> board >> board >> board;
            }
            catch (const exception& e) {
                cerr << "Exception Caught: " << e.what() << endl;
            }
            state = HoldEmState::turn;
            break;
        case HoldEmState::turn: 
            try {
                deck >> board;
            }
            catch (const exception& e) {
                cerr << "Exception Caught: " << e.what() << endl;
            }
            state = HoldEmState::river;
            break;
        case HoldEmState::river: 
            try {
                deck >> board;
            }
            catch (const exception& e) {
                cerr << "Exception Caught: " << e.what() << endl;
            }
            state = HoldEmState::undefined;
            break;
        case HoldEmState::undefined: 
            break;
    }
}

void HoldEmGame::collect_hands() {
    for (unsigned int i = 0; i < names.size(); ++i) {
        deck.collect(hands[i]);
    }
    deck.collect(board);
}

void HoldEmGame::print_players() {
    for (unsigned int i = 0; i < names.size(); ++i) {
        cout << names[i] << ": "; 
        for (unsigned int j = 0; j < hands[i].size(); ++j) {
            cout << hands[i].get_card(j) << " ";
        }
        cout << endl;
    }
}

void HoldEmGame::print_board(string state) {
    cout << "BOARD (" << state << "): " << endl;
    for (unsigned int i = 0; i < board.size(); ++i) {
        cout << board.get_card(i) << " " << endl;
    }
}

bool HoldEmGame::continue_game() {
    string user_response;
    cout << "Would you like to continue playing?" << endl; 
    getline(cin, user_response);
    if (user_response == "yes") {
        return true;
    }
    else {
        return false;
    }
}

struct HoldEmGame::player {
    CardSet<HoldEmRank, Suit> set;
    string name;
    HoldEmHandRank hand_rank;
    
    player(CardSet<HoldEmRank, Suit> s, string &n, HoldEmHandRank h): set(s), name(n), hand_rank(h) {}
};

bool HoldEmGame::valid_hand(holdem_vec_iterator front, holdem_vec_iterator back) {
    if (distance(front, back) == hand_size) {
        return true;
    }
    else {
        return false;
    }
}

/*
* straight_flush(holdem_vec_iterator front, holdem_vec_iterator back)
* Determines whether a hand has a straight by checking if the hand ascends from its lowest ranked 
* card and every suit is the same, and also checks the Ace edge cases
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
*/
bool HoldEmGame::straight_flush(holdem_vec_iterator front, holdem_vec_iterator back) {
    Suit first_suit = front->suit;
    holdem_vec_iterator i;
    if ((front + card5)->rank != HoldEmRank::ace) {
        HoldEmRank rankIter = front->rank;
         for (i = front + card2;  i != back; ++i) {
            ++rankIter;
            if (i->suit != first_suit || i->rank != rankIter) {
                return false;
            }
        }
    }
    //If an Ace is last, check if the first card is a Ten
    else if (front->rank == HoldEmRank::ten) {
        HoldEmRank rankIter = front->rank;
        for (i = front + card2;  i != back; ++i) {
            ++rankIter;
            if (i->suit != first_suit || i->rank != rankIter) {
                return false;
            }
        }
    }
    //Otherwise, check if the first card is a Two 
    else {
        HoldEmRank rankIter = HoldEmRank::two;
        for (i = front; i < back - 1; ++i) {
            if (i->suit != first_suit || i->rank != rankIter) {
                return false;
            }
            ++rankIter;
        }
        if (front->suit != (front+card2)->suit) {
            return false;
        }
    }
    return true;
}

/*
* four_of_a_kind(holdem_vec_iterator front, holdem_vec_iterator back)
* Determines whether a hand has a four of a kind by checking if there are three matching pairs
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
*/
bool HoldEmGame::four_of_a_kind(holdem_vec_iterator front, holdem_vec_iterator back) {
    map<HoldEmRank, int> rank_frequency;
    holdem_vec_iterator i;
    for (i = front; i != back; ++i) {
        rank_frequency[i->rank]++;
    }

    //Frequencies should be {4, 4, 4, 4, 1} in any order
    unsigned int expected_sum = 17;

    unsigned int sum_frequencies = 0;
    for (i = front; i != back; ++i) {
        sum_frequencies += rank_frequency[i->rank];
    }

    if (sum_frequencies == expected_sum) {
            return true;
    } 
    return false;
}

/*
* full_house(holdem_vec_iterator front, holdem_vec_iterator back)
* Determines whether a hand has a full house of by recording the frequency of each rank and summing them
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
*/
bool HoldEmGame::full_house(holdem_vec_iterator front, holdem_vec_iterator back) {
    map<HoldEmRank, int> rank_frequency;
    holdem_vec_iterator i;
    for (i = front; i != back; ++i) {
        rank_frequency[i->rank]++;
    }

    //Frequencies should be {3, 3, 3, 2, 2} in any order
    unsigned int expected_sum = 13;

    unsigned int sum_frequencies = 0;
    for (i = front; i != back; ++i) {
        sum_frequencies += rank_frequency[i->rank];
    }

    if (sum_frequencies == expected_sum) {
            return true;
    } 
    return false;
}

/*
* flush(holdem_vec_iterator front, holdem_vec_iterator back)
* Determines whether a hand has a flush by comparing every suit
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
*/
bool HoldEmGame::flush(holdem_vec_iterator front, holdem_vec_iterator back) {
    Suit first_suit = front->suit;
    holdem_vec_iterator i;
    for (i = front + card2; i != back; ++i) {
        if (i->suit != first_suit) {
            return false;
        }
    }
    return true;
}

/*
* straight(holdem_vec_iterator front, holdem_vec_iterator back)
* Determines whether a hand has a straight by checking if the hand ascends from its lowest ranked 
* card, and also checks the Ace edge cases
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
*/
bool HoldEmGame::straight(holdem_vec_iterator front, holdem_vec_iterator back) {
    holdem_vec_iterator i;
    if ((front + card5)->rank != HoldEmRank::ace) {
        HoldEmRank rankIter = front->rank;
         for (i = front + card2;  i != back; ++i) {
            ++rankIter;
            if (i->rank != rankIter) {
                return false;
            }
        }
    }
    //If an Ace is last, check if the first card is a Ten
    else if (front->rank == HoldEmRank::ten) {
        HoldEmRank rankIter = front->rank;
        for (i = front + card2;  i != back; ++i) {
            ++rankIter;
            if (i->rank != rankIter) {
                return false;
            }
        }
    }
    //Otherwise, check if the first card is a Two 
    else {
        HoldEmRank rankIter = HoldEmRank::two;
        for (i = front; i != back - 1; ++i) {
            if (i->rank != rankIter) {
                return false;
            }
            ++rankIter;
        }
    }
    return true;
}

/*
* three_of_a_kind(holdem_vec_iterator front, holdem_vec_iterator back)
* Determines whether a hand has a three of a kind by recording the frequency of each rank and summing them
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
*/
bool HoldEmGame::three_of_a_kind(holdem_vec_iterator front, holdem_vec_iterator back) {
    map<HoldEmRank, int> rank_frequency;
    holdem_vec_iterator i;
    for (i = front; i != back; ++i) {
        rank_frequency[i->rank]++;
    }

    //Frequencies should be {3, 3, 3, 1, 1} in any order
    unsigned int expected_sum = 11;

    unsigned int sum_frequencies = 0;
    for (i = front; i != back; ++i) {
        sum_frequencies += rank_frequency[i->rank];
    }

    if (sum_frequencies == expected_sum) {
            return true;
    } 
    return false;
}

/*
* two_pair(holdem_vec_iterator front, holdem_vec_iterator back)
* Determines whether a hand has two pairs by recording the frequency of each rank and summing them
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
*/
bool HoldEmGame::two_pair(holdem_vec_iterator front, holdem_vec_iterator back) {
    map<HoldEmRank, int> rank_frequency;
    holdem_vec_iterator i;
    for (i = front; i != back; ++i) {
        rank_frequency[i->rank]++;
    }

    //Frequencies should be {2, 2, 2, 2, 1} in any order
    unsigned int expected_sum = 9;

    unsigned int sum_frequencies = 0;
    for (i = front; i != back; ++i) {
        sum_frequencies += rank_frequency[i->rank];
    }

    if (sum_frequencies == expected_sum) {
            return true;
    } 
    return false;
}

/*
* pair(holdem_vec_iterator front, holdem_vec_iterator back)
* Determines whether a hand has a pair by recording the frequency of each rank and summing them
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
*/
bool HoldEmGame::pair(holdem_vec_iterator front, holdem_vec_iterator back) {
    map<HoldEmRank, int> rank_frequency;
    holdem_vec_iterator i;
    for (i = front; i!= back; ++i) {
        rank_frequency[i->rank]++;
    }

    //Frequencies should be {2, 2, 1, 1, 1} in any order
    unsigned int expected_sum = 7;

    unsigned int sum_frequencies = 0;
    for (i = front; i != back; ++i) {
        sum_frequencies += rank_frequency[i->rank];
    }  

    if (sum_frequencies == expected_sum) {
        return true;
    } 
    return false;
}

HoldEmHandRank HoldEmGame::check_hands(CardSet<HoldEmRank, Suit> &hand) {
    if (!valid_hand(hand.get_front(), hand.get_back())) {
        return HoldEmHandRank::undefined;
    }
    else if (straight_flush(hand.get_front(), hand.get_back())) {
        return HoldEmHandRank::straightflush;
    }
    else if (four_of_a_kind(hand.get_front(), hand.get_back())) {
        return HoldEmHandRank::fourofakind;
    }
    else if (full_house(hand.get_front(), hand.get_back()))  {
        return HoldEmHandRank::fullhouse;
    }
    else if (flush(hand.get_front(), hand.get_back())) {
        return HoldEmHandRank::flush;
    }
    else if (straight(hand.get_front(), hand.get_back())) {
        return HoldEmHandRank::straight;
    }
    else if (three_of_a_kind(hand.get_front(), hand.get_back())) {
        return HoldEmHandRank::threeofakind;
    }
    else if (two_pair(hand.get_front(), hand.get_back())) {
        return HoldEmHandRank::twopair;
    }
    else if (pair(hand.get_front(), hand.get_back())) {
        return HoldEmHandRank::pair;
    }
    return HoldEmHandRank::xhigh;
}

/*
* holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> &hand) 
* checks a player's hand for HoldEmHand hand and returns corresponding HoldEmHandRank
*
* @param hand the passed in cardset
*/
HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> &hand) {
    CardSet<HoldEmRank, Suit> c_set(hand);
    c_set.sort_set();
    return check_hands(c_set);
}

/*
* evaluate_players(vector<player> &player_list)
* Determines the hand rank of each player
*
* @param player_list the list of players 
*/
void HoldEmGame::evaluate_players(vector<player> &player_list) {
    for (unsigned int i = 0; i < names.size(); ++i) {
        player_list.push_back(player(hands[i], names[i], HoldEmHandRank::undefined));
    }
    for (unsigned int i = 0; i < names.size(); ++i) {
        copy(board.get_front(), board.get_back(), player_list[i].set.inserter());
        player_list[i].hand_rank = holdem_hand_evaluation(player_list[i].set);
    }
}

/*
* sort_players(vector<player> &player_list)
* Sorts the players based on hand rank
*
* @param player_list the list of players 
*/
void HoldEmGame::sort_players(vector<player> &player_list) {
    for(unsigned int i = 0; i < player_list.size(); ++i) {
        for (unsigned int j = i; j < player_list.size(); ++j) {
            if (player_list[i] < player_list[j]) {
                swap(player_list[i], player_list[j]);
            }
        }
    }
    for (unsigned int i = 0; i < player_list.size(); ++i) {
        cout << player_list[i].name << ": "; 
        holdem_vec_iterator front = player_list[i].set.get_front();
        holdem_vec_iterator back = player_list[i].set.get_back();
        for (holdem_vec_iterator j = front; j != back; ++j) {
            cout << *j << " ";
        }
        cout << "-> " << player_list[i].hand_rank << endl;
    }
}

int HoldEmGame::play() {
    bool game_state = true;
    while (game_state) {
        deck.shuffle();
        state = HoldEmState::preflop;
        deal();
        print_players();
        deal();
        print_board("flop");
        vector<player> list;
        evaluate_players(list);
        sort_players(list);
        deal();
        print_board("turn");
        deal();
        print_board("river");
        collect_hands(); 
        game_state = continue_game();
    }
    return game_over;
}

std::ostream & operator<<(std::ostream& stream, const HoldEmHandRank &rank) {
    switch (rank) {
        case HoldEmHandRank::xhigh: stream << "X High";
            return stream;
            break;
        case HoldEmHandRank::pair: stream << "Pair";
            return stream;
            break;
        case HoldEmHandRank::twopair: stream << "Two Pair";
            return stream;
            break;
        case HoldEmHandRank::threeofakind: stream << "Three of a Kind";
            return stream;
            break;
        case HoldEmHandRank::straight: stream << "Straight";
            return stream;
            break;
        case HoldEmHandRank::flush: stream << "Flush";
            return stream;
            break;
        case HoldEmHandRank::fullhouse: stream << "Full House";
            return stream;
            break;
        case HoldEmHandRank::fourofakind: stream << "Four of a Kind";
            return stream;
            break;
        case HoldEmHandRank::straightflush: stream << "Straight Flush";
            return stream;
            break;
        case HoldEmHandRank::undefined: stream << "Undefined";
            return stream;
            break;
    }
    return stream;
}

bool operator<(const HoldEmGame::player &a, const HoldEmGame::player &b) {
    if (a.hand_rank < b.hand_rank) {
        return true;
    }
    else if (a.hand_rank == b.hand_rank) {
        CardSet<HoldEmRank, Suit> a_hand(a.set);
        CardSet<HoldEmRank, Suit> b_hand(b.set);   
        return compare_equal_hands(a_hand, b_hand, a.hand_rank); 
    }
    return false;
}

/*
* compare_equal_hands(CardSet<HoldEmRank, Suit> &hand_1, CardSet<HoldEmRank, Suit> &hand_2, HoldEmHandRank rank)
* Determines which player has a higher hand if they have equal hand ranks
*
* @param hand_1 a reference to the hand of the first player
* @param hand_2 a reference to the hand of the second player
* @param rank the rank to of both hands
*/
bool compare_equal_hands(CardSet<HoldEmRank, Suit> &hand_1, CardSet<HoldEmRank, Suit> &hand_2, HoldEmHandRank rank) {
    choose_priority(hand_1, hand_2, rank);
    holdem_vec_iterator i = hand_1.get_front();
    holdem_vec_iterator j = hand_2.get_front();
    while ( i != hand_1.get_back()) {
        if (i->rank < j->rank) {
            return true;
        }
        else if (j->rank < i->rank) {
            return false;
        }
        ++i;
        ++j;
    }
    return false;
}

/*
* choose_priority(CardSet<HoldEmRank, Suit> &hand_1, CardSet<HoldEmRank, Suit> &hand_2, HoldEmHandRank rank)
* Sorts the hand based on their ranks  
*
* @param hand_1 a reference to the hand of the first player
* @param hand_2 a reference to the hand of the second player
* @param rank the rank to of both hands
*/
void choose_priority(CardSet<HoldEmRank, Suit> &hand_1, CardSet<HoldEmRank, Suit> &hand_2, HoldEmHandRank rank) { 
    switch(rank) {
        case HoldEmHandRank::pair: 
            prioritize_pair(hand_1);
            prioritize_pair(hand_2);
            break;
        case HoldEmHandRank::twopair: 
            prioritize_two_pair(hand_1);
            prioritize_two_pair(hand_2);
            break;
        case HoldEmHandRank::threeofakind: 
            prioritize_three_of_a_kind(hand_1);
            prioritize_three_of_a_kind(hand_2);
            break;
        case HoldEmHandRank::fullhouse: 
            prioritize_full_house(hand_1);
            prioritize_full_house(hand_2);
            break;
        case HoldEmHandRank::fourofakind: 
            prioritize_four_of_a_kind(hand_1);
            prioritize_four_of_a_kind(hand_2);
            break;
        default:
            prioritize(hand_1);
            prioritize(hand_2);
            break;
    }
}

/*
* prioritize(CardSet<HoldEmRank, Suit> &hand)
* Sorts the hand in ascending order then reverses it 
*
* @param hand1 the hand to be prioritized
*/
void prioritize(CardSet<HoldEmRank, Suit> &hand) {
    sort(hand.get_front(), hand.get_back(), compare_ranks<HoldEmRank, Suit>);
    reverse(hand.get_front(), hand.get_back());
}

/*
* prioritize_pair(CardSet<HoldEmRank, Suit> &hand)
* Sorts the hand so the pair is at the front of the vector and the remaining cards after 
* are sorted in descending order by rank
*
* @param hand1 the hand to be prioritized
*/
void prioritize_pair(CardSet<HoldEmRank, Suit> &hand) {
    //Sort the hand in ascending order
    sort(hand.get_front(), hand.get_back(), compare_ranks<HoldEmRank, Suit>);

    //Locate the pair in the hand 
    holdem_vec_iterator pair_iter;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back() - 1; ++i) {
        if (i->rank == (i+1)->rank) {
            pair_iter = i;
        }
    }
    
    //Copy the hand to another cardset, with the pair at the back
    CardSet<HoldEmRank, Suit> c_set;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back(); ++i) {
        if (i != pair_iter) {
            copy(i, i+1, c_set.inserter());
        }
        else {
            ++i;
        }
    }
    copy(pair_iter, pair_iter + 2, c_set.inserter());

    //Assign the new card set to the original hand
    hand = move(c_set); 
        
    //Reverse the vector so the pair is at the front
    reverse(hand.get_front(), hand.get_back());
}

/*
* prioritize_two_pair(CardSet<HoldEmRank, Suit> &hand)
* Sorts the hand so the higher pair is at the front of the vector, the lower pair is next, and the 
* remaning card is last
*
* @param hand1 the hand to be prioritized
*/
void prioritize_two_pair(CardSet<HoldEmRank, Suit> &hand) {
    //Sort the hand in ascending order
    sort(hand.get_front(), hand.get_back(), compare_ranks<HoldEmRank, Suit>);

    //Locate the pair in the hand 
    holdem_vec_iterator highest_pair_iter;
    holdem_vec_iterator lowest_pair_iter;
    bool lowest_pair_found = false;

    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back() - 1; ++i) {
        if ( ( i->rank == (i+1)->rank) && !lowest_pair_found) {
            lowest_pair_iter = i;
            lowest_pair_found = true;
            continue;
        }
        if ( (i->rank == (i+1)->rank) && lowest_pair_found) {
            highest_pair_iter = i;
        }
    }

    //Copy the hand to another cardset, with the highest pair at the back and the lower pair before
    CardSet<HoldEmRank, Suit> c_set;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back(); ++i) {
        if (i->rank != lowest_pair_iter->rank && i->rank != highest_pair_iter->rank) {
            copy(i, i+1, c_set.inserter());
        }
    }
    copy(lowest_pair_iter, lowest_pair_iter + 2, c_set.inserter());
    copy(highest_pair_iter, highest_pair_iter + 2, c_set.inserter());

    //Assign the new card set to the original hand
    hand = move(c_set); 
        
    //Reverse the vector so the pair is at the front
    reverse(hand.get_front(), hand.get_back());
}

/*
* prioritize_three_of_a_kind(CardSet<HoldEmRank, Suit> &hand)
* Sorts the hand so that the three of a kind is at the front and the remaining cards are sorted 
* from highest to lowest
*
* @param hand1 the hand to be prioritized
*/
void prioritize_three_of_a_kind(CardSet<HoldEmRank, Suit> &hand) {
    //Sort the hand in ascending order
    sort(hand.get_front(), hand.get_back(), compare_ranks<HoldEmRank, Suit>);

    //Locate the three of a kind in the vector
    holdem_vec_iterator three_kind_iter;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back() - 1; ++i) {
        if (i->rank == (i+1)->rank) {
            three_kind_iter = i;
            break;
        }
    }

    //Copy the hand to another cardset, with the three of a kind at the back
    CardSet<HoldEmRank, Suit> c_set;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back(); ++i) {
        if (i->rank != three_kind_iter->rank) {
            copy(i, i+1, c_set.inserter());
        }
    }
    copy(three_kind_iter, three_kind_iter + 3, c_set.inserter());

    //Assign the new card set to the original hand
    hand = move(c_set);

    //Reverse the vector so the three_of_a_kind is at the front
    reverse(hand.get_front(), hand.get_back());
}

/*
* prioritize_full_house(CardSet<HoldEmRank, Suit> &hand)
* Sorts the hand so the three of a kind is at the front 
*
* @param hand1 the hand to be prioritized
*/
void prioritize_full_house(CardSet<HoldEmRank, Suit> &hand) {
    //Sort the hand in ascending order
    sort(hand.get_front(), hand.get_back(), compare_ranks<HoldEmRank, Suit>);

    //Locate the three of a kind in the vector
    holdem_vec_iterator three_kind_iter;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back() - 1; ++i) {
        if (i->rank == (i+1)->rank) {
            three_kind_iter = i;
            break;
        }
    }

    //Copy the hand to another cardset, with the three of a kind at the back
    CardSet<HoldEmRank, Suit> c_set;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back(); ++i) {
        if (i->rank != three_kind_iter->rank) {
            copy(i, i+1, c_set.inserter());
        }
    }
    copy(three_kind_iter, three_kind_iter + 3, c_set.inserter());

    //Assign the new card set to the original hand
    hand = move(c_set);

    //Reverse the vector so the three_of_a_kind is at the front
    reverse(hand.get_front(), hand.get_back());
}

/*
* prioritize_four_of_a_kind(CardSet<HoldEmRank, Suit> &hand)
* Sorts the hand so the four cards of same rank are at the front
*
* @param hand1 the hand to be prioritized
*/
void prioritize_four_of_a_kind(CardSet<HoldEmRank, Suit> &hand) {
    //Sort the hand in ascending order
    sort(hand.get_front(), hand.get_back(), compare_ranks<HoldEmRank, Suit>);

    //Locate the three of a kind in the vector
    holdem_vec_iterator four_kind_iter;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back() - 1; ++i) {
        if (i->rank == (i+1)->rank) {
            four_kind_iter = i;
            break;
        }
    }

    //Copy the hand to another cardset, with the four of a kind at the back
    CardSet<HoldEmRank, Suit> c_set;
    for (holdem_vec_iterator i = hand.get_front(); i != hand.get_back(); ++i) {
        if (i->rank != four_kind_iter->rank) {
            copy(i, i+1, c_set.inserter());
        }
    }
    copy(four_kind_iter, four_kind_iter + 4, c_set.inserter());

    //Assign the new card set to the original hand
    hand = move(c_set);

    //Reverse the vector so the three_of_a_kind is at the front
    reverse(hand.get_front(), hand.get_back());
}
