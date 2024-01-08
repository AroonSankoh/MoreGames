//GoFishGame_T.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for GoFishGame class template

#include "GoFishGame_T.h"

using namespace std;

template<>
GoFishGame<PinochleRank, Suit, PinochleDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv) {
    names.erase(names.begin());
    for (unsigned int i = 0; i < names.size(); ++i) {
        CardSet<PinochleRank, Suit> hand;
        hands.push_back(hand);
        books.push_back(hand);
    }
    int expected_ranks = 4; 
    for (PinochleRank rankIter = PinochleRank::nine; rankIter < PinochleRank::undefined; ++rankIter) {
        function<bool(Card<PinochleRank, Suit>&)> matching_rank = [rankIter](Card<PinochleRank, Suit>& card) {
            return card.rank == rankIter;
        };   
        if (count_if(deck.get_front(), deck.get_back(), matching_rank) < expected_ranks) {
            throw length_error("Invalid deck for GoFish.");
        }
    }
}

template<>
GoFishGame<HoldEmRank, Suit, HoldEmDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv) {
    names.erase(names.begin());
    for (unsigned int i = 0; i < names.size(); ++i) {
        CardSet<HoldEmRank, Suit> hand;
        hands.push_back(hand);
        books.push_back(hand);
    }
    int expected_ranks = 4; 
    for (HoldEmRank rankIter = HoldEmRank::two; rankIter < HoldEmRank::undefined; ++rankIter) {
        function<bool(Card<HoldEmRank, Suit>&)> matching_rank = [rankIter](Card<HoldEmRank, Suit>& card) {
            return card.rank == rankIter;
        };   
        if (count_if(deck.get_front(), deck.get_back(), matching_rank) < expected_ranks) {
            throw length_error("Invalid deck for GoFish.");
        }
    }
}

template<>
GoFishGame<UnoRank, Color, UnoDeck>::GoFishGame(int argc, const char* argv[]): Game(argc, argv) {
    names.erase(names.begin());
    for (unsigned int i = 0; i < names.size(); ++i) {
        CardSet<UnoRank, Color> hand;
        hands.push_back(hand);
        books.push_back(hand);
    }
    int expected_ranks = 4; 
    for (UnoRank rankIter = UnoRank::zero; rankIter < UnoRank::undefined; ++rankIter) {
        function<bool(Card<UnoRank, Color>&)> matching_rank = [rankIter](Card<UnoRank, Color>& card) {
            return card.rank == rankIter;
        };   
        if (count_if(deck.get_front(), deck.get_back(), matching_rank) < expected_ranks) {
            cout << "Matching ranks: " << count_if(deck.get_front(), deck.get_back(), matching_rank) << endl;
            throw length_error("Invalid deck for GoFish.");
        }
    }
}

template<typename Rank, typename Suit, typename Deck>
GoFishGame<Rank, Suit, Deck>::~GoFishGame() {}

template<> 
bool GoFishGame<PinochleRank, Suit, PinochleDeck>::collect_books(unsigned int player) {
    int expected_ranks = 4; 
    for (PinochleRank rankIter = PinochleRank::nine; rankIter < PinochleRank::undefined; ++rankIter) {
        function<bool(Card<PinochleRank, Suit>&)> matching_rank = [rankIter](Card<PinochleRank, Suit>& card) {
            return card.rank == rankIter;
        };   
        if (count_if(hands[player].get_front(), hands[player].get_back(), matching_rank) >= expected_ranks) {
            books[player].collect_if(hands[player], matching_rank);
            return true;
        }
    }
    return false;
}

template<> 
bool GoFishGame<HoldEmRank, Suit, HoldEmDeck>::collect_books(unsigned int player) {
    int expected_ranks = 4; 
    for (HoldEmRank rankIter = HoldEmRank::two; rankIter < HoldEmRank::undefined; ++rankIter) {
        function<bool(Card<HoldEmRank, Suit>&)> matching_rank = [rankIter](Card<HoldEmRank, Suit>& card) {
            return card.rank == rankIter;
        };   
        if (count_if(hands[player].get_front(), hands[player].get_back(), matching_rank) >= expected_ranks) {
            books[player].collect_if(hands[player], matching_rank);
            return true;
        }
    }
    return false;
}

template<> 
bool GoFishGame<UnoRank, Color, UnoDeck>::collect_books(unsigned int player) {
    int expected_ranks = 4; 
    for (UnoRank rankIter = UnoRank::zero; rankIter < UnoRank::undefined; ++rankIter) {
        function<bool(Card<UnoRank, Color>&)> matching_rank = [rankIter](Card<UnoRank, Color>& card) {
            return card.rank == rankIter;
        };   
        if (count_if(hands[player].get_front(), hands[player].get_back(), matching_rank) >= expected_ranks) {
            books[player].collect_if(hands[player], matching_rank);
            return true;
        }
    }
    return false;
}

template<typename Rank, typename Suit, typename Deck> 
void GoFishGame<Rank, Suit, Deck>::deal() {
    if (names.size() == two) {
        for (unsigned int i = 0; i < num_cards_for_two_players; ++i) {
            for (unsigned int j = 0; j < hands.size(); ++j) {
                try {
                    deck >> hands[j];
                }
                catch (const exception& e) {
                    cerr << "Exception Caught: " << e.what() << endl;
                }
            }
        }
    }
    else {
        for (unsigned int i = 0; i < default_num_cards; ++i) {
            for (unsigned int j = 0; j < hands.size(); ++j) {
                try {
                    deck >> hands[j];
                }
                catch (const exception& e) {
                    cerr << "Exception Caught: " << e.what() << endl;
                }
            }
        }
    }
}

template<typename Rank, typename Suit, typename Deck> 
int GoFishGame<Rank, Suit, Deck>::play() {
    deck.shuffle();
    deal();
    for (unsigned int i = 0; i < names.size(); ++i) {    
        while (collect_books(i)) {}; 
    }
    int round = 1;
    int players_remaining = names.size();
    while (check_game_conditions(players_remaining)) {
        for (unsigned int i = 0; i < names.size(); ++i) {
            if (!hands[i].is_empty() || !deck.is_empty()) {
                while (turn(i)) {};
            }
            else {
                cout << "Player " << i << " is out!" << endl;
                --players_remaining;
            }
        }
        cout << "---- Round " << round << " Results ----" << endl;
        for (unsigned int i = 0; i < names.size(); ++i) {
            cout << names[i] << " books: " << endl;
            for (unsigned int j = 0; j < books[i].size(); ++j) {
                cout << books[i].get_card(j) << " ";
            }
            cout << endl;
        }
        ++round;
    } 
    print_end_game();
    return game_over;
}

/*
* check_game_conditions(int remaining_players)
* Uses the number of remaining players to determine if the game is over by checking it, 
* the deck, and the hands of all the players
*
* @param remaining_players 
*/
template<typename Rank, typename Suit, typename Deck> 
bool GoFishGame<Rank, Suit, Deck>::check_game_conditions(int remaining_players) {
    if (remaining_players < two) {
        return false;
    }
    for (unsigned int i = 0; i < names.size(); ++i) {
        if (!hands[i].is_empty()) {
            return true;
        }
    }
    if (deck.is_empty()) {
        return false;
    }
    return true;
}

template<typename Rank, typename Suit, typename Deck> 
void GoFishGame<Rank, Suit, Deck>::print_end_game() {
    vector<string> winners; 
    unsigned int most_books = 0;
    for (unsigned int i = 0; i < books.size(); ++i) {
        if (most_books < books[i].size()) {
            winners.empty();
            winners.push_back(names[i]);
            most_books = books[i].size();
        }
        else if (most_books == books[i].size()) {
            winners.push_back(names[i]);
        }
    }
    cout << "The player(s) with the most books are:  " << endl;
    for (unsigned int i = 0; i < winners.size(); ++i) {
        cout << winners[i] << " ";
    } 
    cout << endl;
}

template<typename Rank, typename Suit, typename Deck> 
bool GoFishGame<Rank, Suit, Deck>::turn(unsigned int player) {
    if (hands[player].is_empty()) {
        try {
            deck >> hands[player];
        }
        catch (const exception& e) {
            cerr << "Exception Caught: " << e.what() << endl;
        }
        return false;
    }
    cout << "Player " << player << "'s " << "Turn: " << endl << "Board: " << endl;
    print_game_stats();
    string user_response = "";
    prompt(user_response, player);
    long unsigned int space_pos = user_response.find(" ");
    string rank_string = user_response.substr(0, space_pos);
    string player_string = user_response.substr(space_pos + 1);
    return retrieve(player, stoi(player_string), rank_string);
}

template<typename Rank, typename Suit, typename Deck> 
void GoFishGame<Rank, Suit, Deck>::prompt(string& input, unsigned int player) {
    while(!check_input(input, player)) {
        cout << "What card rank from what player would you like?" << endl;
        cout << "Input like the following: \"rank\" \"player#\"" << endl;
        getline(cin, input);
    }
}

template<typename Rank, typename Suit, typename Deck> 
void GoFishGame<Rank, Suit, Deck>::print_game_stats() {
    for (unsigned int i = 0; i < names.size(); ++i ) {
        cout << names[i] << " (" << i << ")" << endl;
        cout << "hand: "; 
        for (unsigned int j = 0; j < hands[i].size(); ++j) {
            cout << hands[i].get_card(j) << " ";
        }
        cout << endl << "books: ";
        for (unsigned int j = 0; j < books[i].size(); ++j) {
            cout << books[i].get_card(j) << " ";
        }
        cout << endl;
    }
}

/*
* retrieve(unsigned int player, int target_player, string rank_string)
* Requests a rank from the player who the user inputted in, and if successfull calls collect_books 
* on the player whose turn it is. Otherwise it attempts to draw a card from the deck.
* (This specialization has the same functionality for HoldEm and Uno)
*
* @param player the players whose turn it is
* @param target_player the player the user inputted
* @param rank_string the string representing the player the user inputted
*/
template<> 
bool GoFishGame<PinochleRank, Suit, PinochleDeck>::retrieve(unsigned int player, int target_player, string rank_string) {
    PinochleRank rank = PinochleRank::undefined;
    set_rank(rank_string, rank);
    if (hands[player].request(hands[target_player], rank)) {
        cout << "Successfully retrieved card." << endl;
        while (collect_books(player)) {}
        return true;
    }
    else {
        cout << "Could not retrieve requested card." << endl;
        if (deck.is_empty()) {
            deck.collect(hands[player]);
            cout << "Player " << player << " is out!" << endl;
        }
        else {
            deck >> hands[player];
            if ((hands[player].get_back() - 1)->rank == rank) {
                while (collect_books(player)) {}
                return true;
            }
        }
        return false;
    }
}

template<> 
bool GoFishGame<HoldEmRank, Suit, HoldEmDeck>::retrieve(unsigned int player, int target_player, string rank_string) {
    HoldEmRank rank = HoldEmRank::undefined;
    set_rank(rank_string, rank);
    if (hands[player].request(hands[target_player], rank)) {
        cout << "Successfully retrieved card." << endl;
        while (collect_books(player)) {}
        return true;
    }
    else {
        cout << "Could not retrieve requested card." << endl;
        if (deck.is_empty()) {
            deck.collect(hands[player]);
            cout << "Player " << player << " is out!" << endl;
        }
        else {
            deck >> hands[player];
            if ((hands[player].get_back() - 1)->rank == rank) {
                while (collect_books(player)) {}
                return true;
            }
        }
        return false;
    }
}

template<> 
bool GoFishGame<UnoRank, Color, UnoDeck>::retrieve(unsigned int player, int target_player, string rank_string) {
    UnoRank rank = UnoRank::undefined;
    set_rank(rank_string, rank);
    if (hands[player].request(hands[target_player], rank)) {
        cout << "Successfully retrieved card." << endl;
        while (collect_books(player)) {}
        return true;
    }
    else {
        cout << "Could not retrieve requested card." << endl;
        if (deck.is_empty()) {
            deck.collect(hands[player]);
            cout << "Player " << player << " is out!" << endl;
        }
        else {
            deck >> hands[player];
            if ((hands[player].get_back() - 1)->rank == rank) {
                while (collect_books(player)) {}
                return true;
            }
        }
        return false;
    }
}

/*
* check_input(string input, unsigned int player)
* Determines if the user typed in a valid input and returns based on the inputs validity 
* (This specialization has the same functionality for HoldEm and Uno)
*
* @param input the user input
* @param player the player whose turn it is
*/
template<> 
bool GoFishGame<PinochleRank, Suit, PinochleDeck>::check_input(string input, unsigned int player) {
    long unsigned int space_pos = input.find(" ");
    if (space_pos != string::npos) {
           string rank_string = input.substr(0, space_pos);
           string player_string = input.substr(space_pos + 1);
           unsigned int player_num = names.size();
           try {
                player_num = stoi(player_string);
           }
           catch (const exception& e) {
                cerr << "Exception Caught: " << e.what() << endl;
           }
           if(player_num != player && player_num < names.size()) {
                PinochleRank rank = PinochleRank::undefined;
                set_rank(rank_string, rank);
                function<bool(Card<PinochleRank, Suit>&)> matching_rank = [rank](Card<PinochleRank, Suit>& card) {
                    return card.rank == rank;
                };
                if (find_if(hands[player].get_front(), hands[player].get_back(), matching_rank) != hands[player].get_back()) {
                    return true;
                }
           }
    } 
    return false;
}

template<> 
bool GoFishGame<HoldEmRank, Suit, HoldEmDeck>::check_input(string input, unsigned int player) {
    long unsigned int space_pos = input.find(" ");
    if (space_pos != string::npos) {
           string rank_string = input.substr(0, space_pos);
           string player_string = input.substr(space_pos + 1);
           unsigned int player_num = names.size();
           try {
                player_num = stoi(player_string);
           }
           catch (const exception& e) {
                cerr << "Exception Caught: " << e.what() << endl;
           }
           if(player_num != player && player_num < names.size()) {
                HoldEmRank rank = HoldEmRank::undefined;
                set_rank(rank_string, rank);
                function<bool(Card<HoldEmRank, Suit>&)> matching_rank = [rank](Card<HoldEmRank, Suit>& card) {
                    return card.rank == rank;
                };
                if (find_if(hands[player].get_front(), hands[player].get_back(), matching_rank) != hands[player].get_back()) {
                    return true;
                }
           }
    } 
    return false;
}

template<> 
bool GoFishGame<UnoRank, Color, UnoDeck>::check_input(string input, unsigned int player) {
    long unsigned int space_pos = input.find(" ");
    if (space_pos != string::npos) {
           string rank_string = input.substr(0, space_pos);
           string player_string = input.substr(space_pos + 1);
           unsigned int player_num = names.size();
           try {
                player_num = stoi(player_string);
           }
           catch (const exception& e) {
                cerr << "Exception Caught: " << e.what() << endl;
           }
           if(player_num != player && player_num < names.size()) {
                UnoRank rank = UnoRank::undefined;
                set_rank(rank_string, rank);
                function<bool(Card<UnoRank, Color>&)> matching_rank = [rank](Card<UnoRank, Color>& card) {
                    return card.rank == rank;
                };
                if (find_if(hands[player].get_front(), hands[player].get_back(), matching_rank) != hands[player].get_back()) {
                    return true;
                }
           }
    } 
    return false;
}
 




