Lab 3
Aroon Sankoh
a.j.sankoh@wustl.edu 

Errors & Solutions: 
1. 
Error: Template specialization after initialization 
Solution: Changed the template specialization to an overloaded function and moved it
outside of the template class.

2. 
Error: Linker issues for compiler 
Solution: Checked which functions were being called where and whether the correct libraries 
were being included when I used specific algorithms or data structures.

3.
Error: Inclusion errors 
Solution: Checked if my inclusion chains between templates and other files were correct, 
and also made sure template headers included their sources in the proper inclusion guards.

4. 
Error: Seg Faults 
Solution: Allocation of hands and books was different in the GoFishGame than in 
previous games because the first 3 commmand line arguments were not names instead of just 
the first 2. It took me a while to realize this and change my implementation accordingly. 

5. 
Error: Removing a card from a Cardset 
Solution: Without the accessor to a cardset's pile, I struggled to think of a way to remove 
a card from a vector's cardset without further violating encapsulation of the cardset class.
I eventually decided on a method where I allocated a duplicate cardset with every card in the 
original except for the cards I wanted to remove, and then moved this cardset into the old one.

6. 
Error: std::logic_error being thrown and program core dumps (out of bounds error)
Solution: In my check_arguments(argc, argv[]) function in main, I need to check if argv[1] exists
before I check to see what the value, or else I'll get a segmentation fault error.

7. 
Erorr: std::invalid_argument being thrown and program core dumps (out of bounds error)
Solution: In my check_input function, I tried immediately wrapping the string input to a 
call to stoi to get the player rank, but this threw an exception when the input wasn't a string 
digit (eg. "3"). I had to wrap this call in a try/catch block to stop the error from propogating 
out of main. 

8. 
Error: Out of scope errors
Solution: Just being aware of the scope of class member variables, functions, and other instances

9. 
Error: play() function logic
Getting the play function to compile took a while, and even after there were certain parts of the game 
that didn't make sense which I changed for the sake of a smooth game. Here's a small list. 
1) I made it so the collect_books function is called not just whenever I player successfully 
requests a card but whenever a new card enters a players deck 
2) I made it so if a player has an empty hand and it switches onto their turn, they automatically 
draw a card and then game jumps to the next player. 
3) I made it so the prompt will continously call unless the user inputs 1) a valid rank—or a rank 
that is currently in their hand and 2) a valid number for a player—a number that is between 0 and the 
names size() that is not their own. 
4) Since each deck is constructed with a multiple of 4 of each card rank, the only way the game can end 
is if the deck is empty and every hand is empty, so all the cards end up in the books vector of each player. 

Warnings Fixed: 
- Comparisons between two different integer types (unsigned and signed)
- Comparisons between two different string types: string literal and char *
- Control reaches end of non-void function without hitting a return statement
- Unused parameter warnings when defining and testing functions

--------------------------------------------------------------------------------------------

Test Cases: Expected denotes the output is correct
1. Running with just the executable name and no other arguments. 
Output: 
[a.j.sankoh@linuxlab007 lab_3]$ ./lab3
Run the executable in the command line followed by: 
1) "Pinochle" and four player names or 
2) "HoldEm" and between two and nine player names
3) "GoFish" and either "Pinochle", "HoldEm", or "Uno" and between two and five player names

Expected 

2. Running with the executable name, "GoFish", and 5 names:
Output: 
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish a b c d e
Run the executable in the command line followed by: 
1) "Pinochle" and four player names or 
2) "HoldEm" and between two and nine player names
3) "GoFish" and either "Pinochle", "HoldEm", or "Uno" and between two and five player names

Expected 

3. Running with the executable name, "GoFish", "Pinochle" and no other arguments: 
Output: 
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Pinochle
Run the executable in the command line followed by: 
1) "Pinochle" and four player names or 
2) "HoldEm" and between two and nine player names
3) "GoFish" and either "Pinochle", "HoldEm", or "Uno" and between two and five player names

Expected 

3. Running with the executable name, "GoFish", "Pinochle" and less than two arguments
Output: 
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Pinochle a 
Run the executable in the command line followed by: 
1) "Pinochle" and four player names or 
2) "HoldEm" and between two and nine player names
3) "GoFish" and either "Pinochle", "HoldEm", or "Uno" and between two and five player names
2) "HoldEm" and between two and nine player names

Expected

4. Running with the executable name, "GoFish", "Pinochle" and more than five arguments
Output: 
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Pinochle a b c d e f
Run the executable in the command line followed by: 
1) "Pinochle" and four player names or 
2) "HoldEm" and between two and nine player names
3) "GoFish" and either "Pinochle", "HoldEm", or "Uno" and between two and five player names

Expected

Playing through PINOCHLE

5. Running with the executable name, "GoFish", "Pinochle" and 2 arguments:
Output: 
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Pinochle a b 
Player 0's Turn: 
Board: 
a (0)
hand: 10H 10C JD KH QD 9C JH 
books: 
b (1)
hand: 9H AC JS KC 9S AH 9D 
books: 

Expected

Inputing an invalid rank/player strings 
Output: 
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Pinochle a b 
Player 0's Turn: 
Board: 
a (0)
hand: 10H 10C JD KH QD 9C JH 
books: 
b (1)
hand: 9H AC JS KC 9S AH 9D 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
4 5
What card rank from what player would you like?
Input like the following: "rank" "player#"
drawtwo 3
What card rank from what player would you like?
Input like the following: "rank" "player#"
A 1
What card rank from what player would you like?
Input like the following: "rank" "player#"
428
What card rank from what player would you like?
Input like the following: "rank" "player#"

Inputting a valid rank/player string
Output: 
a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Pinochle a b 
Player 0's Turn: 
Board: 
a (0)
hand: 10H 10C JD KH QD 9C JH 
books: 
b (1)
hand: 9H AC JS KC 9S AH 9D 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
4 5
What card rank from what player would you like?
Input like the following: "rank" "player#"
drawtwo 3
What card rank from what player would you like?
Input like the following: "rank" "player#"
A 1
What card rank from what player would you like?
Input like the following: "rank" "player#"
428
What card rank from what player would you like?
Input like the following: "rank" "player#"
J 1
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 10H 10C JD KH QD 9C JH JS 
books: 
b (1)
hand: 9H AC KC 9S AH 9D 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Expected

Creating a book for Player 0: 
Output:
What card rank from what player would you like?
Input like the following: "rank" "player#"
9 1
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 10H 10C JD KH QD 9C JH JS 9H 
books: 
b (1)
hand: AC KC 9S AH 9D 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
9 1
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 10H 10C JD KH QD 9C JH JS 9H 9S 
books: 
b (1)
hand: AC KC AH 9D 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
9 1
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 10H 10C JD KH QD JH JS 
books: 9C 9H 9S 9D 
b (1)
hand: AC KC AH 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Expected

Inputting a valid rank/player string that the other player doesn't have:
Output: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
10 1
Could not retrieve requested card.
Player 1's Turn: 
Board: 
a (0)
hand: 10H 10C JD KH QD JH JS JH 
books: 9C 9H 9S 9D 
b (1)
hand: AC KC AH 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Expected 

Completing a Round:
Output: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
K 0
Successfully retrieved card.
Player 1's Turn: 
Board: 
a (0)
hand: 10H 10C JD QD JH JS JH 
books: 9C 9H 9S 9D 
b (1)
hand: AC KC AH KH 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
A 0
Could not retrieve requested card.
---- Round 1 Results ----
a books: 
9C 9H 9S 9D 
b books: 

Player 0's Turn: 
Board: 
a (0)
hand: 10H 10C JD QD JH JS JH 
books: 9C 9H 9S 9D 
b (1)
hand: AC KC AH KH KD 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Expected 

Completing the Game: 
Player 0's Turn: 
Board: 
a (0)
hand: QC QD QS 
books: 9C 9H 9S 9D JD JH JS JH QD QC QS QH 10H 10C 10D 10C 9S 9D 9C 9H AS AC AD AS JD JC JC JS 
b (1)
hand: 
books: KC KH KD KH AC AH AH AD KC KD KS KS 10H 10D 10S 10S 
What card rank from what player would you like?
Input like the following: "rank" "player#"
Q 1
Could not retrieve requested card.
Exception Caught: Pile of implicit cardset is empty.
Player 1 is out!
---- Round 14 Results ----
a books: 
9C 9H 9S 9D JD JH JS JH QD QC QS QH 10H 10C 10D 10C 9S 9D 9C 9H AS AC AD AS JD JC JC JS QC QD QS QH 
b books: 
KC KH KD KH AC AH AH AD KC KD KS KS 10H 10D 10S 10S 
The player(s) with the most books are:  
a 

Expected.

6. Running with the executable name, "GoFish", "Pinochle" and 5 arguments:
Output: 
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Pinochle a b c d e
Player 0's Turn: 
Board: 
a (0)
hand: 9H 10S 10C JH 9C 
books: 
b (1)
hand: KH KS 10H AC JS 
books: 
c (2)
hand: KD 9D 9C KC 10H 
books: 
d (3)
hand: 10D 9S 9D JS AD 
books: 
e (4)
hand: QS JH 9S QH AH 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Playing through HOLDEM

Expected. 

7. Running with the executable name, "GoFish", "HoldEm" and 5 arguments:
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish HoldEm a b c d e
Player 0's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 
books: 
b (1)
hand: 7H QS 7D 8C 8H 
books: 
c (2)
hand: KH 2H 8D KD JC 
books: 
d (3)
hand: AS 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 8S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Expected. 

Playing a round of HoldEm:
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish HoldEm a b c d e
Player 0's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 
books: 
b (1)
hand: 7H QS 7D 8C 8H 
books: 
c (2)
hand: KH 2H 8D KD JC 
books: 
d (3)
hand: AS 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 8S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
7 1
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 
books: 
b (1)
hand: QS 7D 8C 8H 
books: 
c (2)
hand: KH 2H 8D KD JC 
books: 
d (3)
hand: AS 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 8S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
7 1
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D 
books: 
b (1)
hand: QS 8C 8H 
books: 
c (2)
hand: KH 2H 8D KD JC 
books: 
d (3)
hand: AS 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 8S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
J 2
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC 
books: 
b (1)
hand: QS 8C 8H 
books: 
c (2)
hand: KH 2H 8D KD 
books: 
d (3)
hand: AS 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 8S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
A 3
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 
books: 
b (1)
hand: QS 8C 8H 
books: 
c (2)
hand: KH 2H 8D KD 
books: 
d (3)
hand: 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 8S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
A 4
Could not retrieve requested card.
Player 1's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 8C 8H 
books: 
c (2)
hand: KH 2H 8D KD 
books: 
d (3)
hand: 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 8S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
* 2
What card rank from what player would you like?
Input like the following: "rank" "player#"
8 2
Successfully retrieved card.
Player 1's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 8C 8H 8D 
books: 
c (2)
hand: KH 2H KD 
books: 
d (3)
hand: 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 8S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
8 4
Successfully retrieved card.
Player 1's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 
books: 8C 8H 8D 8S 
c (2)
hand: KH 2H KD 
books: 
d (3)
hand: 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
Q 2
Could not retrieve requested card.
Player 2's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 4D 
books: 8C 8H 8D 8S 
c (2)
hand: KH 2H KD 
books: 
d (3)
hand: 10H 6S KS 10D 
books: 
e (4)
hand: 5H 3S KC 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
K 3
Successfully retrieved card.
Player 2's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 4D 
books: 8C 8H 8D 8S 
c (2)
hand: KH 2H KD KS 
books: 
d (3)
hand: 10H 6S 10D 
books: 
e (4)
hand: 5H 3S KC 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
K 4
Successfully retrieved card.
Player 2's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 4D 
books: 8C 8H 8D 8S 
c (2)
hand: 2H 
books: KH KD KS KC 
d (3)
hand: 10H 6S 10D 
books: 
e (4)
hand: 5H 3S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
2 3
Could not retrieve requested card.
Player 3's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 4D 
books: 8C 8H 8D 8S 
c (2)
hand: 2H JH 
books: KH KD KS KC 
d (3)
hand: 10H 6S 10D 
books: 
e (4)
hand: 5H 3S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
10 0
Could not retrieve requested card.
Player 4's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 4D 
books: 8C 8H 8D 8S 
c (2)
hand: 2H JH 
books: KH KD KS KC 
d (3)
hand: 10H 6S 10D 4H 
books: 
e (4)
hand: 5H 3S 5C 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
5 0
Could not retrieve requested card.
---- Round 1 Results ----
a books: 

b books: 
8C 8H 8D 8S 
c books: 
KH KD KS KC 
d books: 

e books: 

Player 0's Turn: 
Board: 
a (0)
hand: 7S 6D 9H AC JD 7H 7D JC AS 6H 
books: 
b (1)
hand: QS 4D 
books: 8C 8H 8D 8S 
c (2)
hand: 2H JH 
books: KH KD KS KC 
d (3)
hand: 10H 6S 10D 4H 
books: 
e (4)
hand: 5H 3S 5C QD 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Expected. 

Playing through UNO
 
8. Running with the executable name, "GoFish", "Uno" and 3 arguments:
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Uno a b c
Player 0's Turn: 
Board: 
a (0)
hand: 7red 5green 1blue blankblack 7yellow 
books: 
b (1)
hand: 1yellow 3yellow 9blue 2yellow reverseyellow 
books: 
c (2)
hand: 1green skipblue 2green 1blue 6green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Expected. 

Playing a round of Uno:
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 GoFish Uno a b c
Player 0's Turn: 
Board: 
a (0)
hand: 7red 5green 1blue blankblack 7yellow 
books: 
b (1)
hand: 1yellow 3yellow 9blue 2yellow reverseyellow 
books: 
c (2)
hand: 1green skipblue 2green 1blue 6green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
1 1
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 7red 5green 1blue blankblack 7yellow 1yellow 
books: 
b (1)
hand: 3yellow 9blue 2yellow reverseyellow 
books: 
c (2)
hand: 1green skipblue 2green 1blue 6green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
1 2
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 7red 5green 1blue blankblack 7yellow 1yellow 1green 
books: 
b (1)
hand: 3yellow 9blue 2yellow reverseyellow 
books: 
c (2)
hand: skipblue 2green 1blue 6green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
1 2
Successfully retrieved card.
Player 0's Turn: 
Board: 
a (0)
hand: 7red 5green blankblack 7yellow 
books: 1blue 1yellow 1green 1blue 
b (1)
hand: 3yellow 9blue 2yellow reverseyellow 
books: 
c (2)
hand: skipblue 2green 6green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
7 1
Could not retrieve requested card.
Player 1's Turn: 
Board: 
a (0)
hand: 7red 5green blankblack 7yellow blankblack 
books: 1blue 1yellow 1green 1blue 
b (1)
hand: 3yellow 9blue 2yellow reverseyellow 
books: 
c (2)
hand: skipblue 2green 6green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
2 2
Successfully retrieved card.
Player 1's Turn: 
Board: 
a (0)
hand: 7red 5green blankblack 7yellow blankblack 
books: 1blue 1yellow 1green 1blue 
b (1)
hand: 3yellow 9blue 2yellow reverseyellow 2green 
books: 
c (2)
hand: skipblue 6green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
9 2
Could not retrieve requested card.
Player 2's Turn: 
Board: 
a (0)
hand: 7red 5green blankblack 7yellow blankblack 
books: 1blue 1yellow 1green 1blue 
b (1)
hand: 3yellow 9blue 2yellow reverseyellow 2green 4green 
books: 
c (2)
hand: skipblue 6green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"
6 2
What card rank from what player would you like?
Input like the following: "rank" "player#"
6 0
Could not retrieve requested card.
---- Round 1 Results ----
a books: 
1blue 1yellow 1green 1blue 
b books: 

c books: 

Player 0's Turn: 
Board: 
a (0)
hand: 7red 5green blankblack 7yellow blankblack 
books: 1blue 1yellow 1green 1blue 
b (1)
hand: 3yellow 9blue 2yellow reverseyellow 2green 4green 
books: 
c (2)
hand: skipblue 6green 7green 
books: 
What card rank from what player would you like?
Input like the following: "rank" "player#"

Expected.

9. Playing Pinochle: 
a.j.sankoh@linuxlab002 lab_3]$ ./lab3 Pinochle a b c d
a: QS 10D QC 10S QC JS KD 9C 10S QH KC 9H 
b: 10D JC 9H JD AH AS AD KS 9C 10H 9S KH 
c: QS 9D QD JD JH 10C KC AD AC KD QD 10C 
Pinochle: 40
d: 9D AH QH JH AC KH JC AS KS 10H 9S JS 
Would you like to continue playing?
yes
a: 10D AC 10C KH KH 9D QH 9C 9H QD QH KS 
b: KC 10H JH AD AC AH JD AS KC 9S AS KS 
Hundred Aces: 100
c: QC AD 10H JH QC 10S JC QS QS JC 9S 9H 
d: QD JD AH KD JS 9D 9C 10C 10D JS KD 10S 
Would you like to continue playing?
yes
a: 9S AC 9C JH QD 10S JS KD KC JC 9C JD 
Forty Jacks: 40
b: AD 9S QS 9H JC AD KS 10C JS 9D QC KS 
c: 10C AH QS AH KH JH 10S QH QC 9H 10D KD 
d: AS AC 10H JD QD QH 10D 9D AS KH KC 10H 
Would you like to continue playing?
yes
a: 9S 10H KC 9C KH JC AS 10D 10S 9D KS JS 
b: AS JD AD 10D QC QH AH KC JH AH QS KD 
Pinochle: 40
c: QS 10C AD QH QD JH QC 10C 9H 9H KD 9C 
Sixty Queens: 60
d: 9S KS JC JS AC QD 9D JD AC 10H 10S KH 
Would you like to continue playing?
yes
a: AD 9D QH 9D AS 9S QD QC 9S 10D JC AH 
b: 9C 9H JD JD 10D AH 10H QS JH KC AC QH 
Pinochle: 40
c: 10S KS 10C KD QD QS 10C KC JC 10H JH KH 
Eighty Kings: 80
d: KS AD AC KH JS AS 9C 9H QC JS 10S KD 
Would you like to continue playing?
yes
a: 9S 10D KC KC JS 9C QH 9H 10S KD 9D QH 
b: QS KH QS 10C QD JD JC AC AH AH AC KS 
Pinochle: 40
c: 10H 9S JD QC QC AS JS 10C KS 10D JH JC 
Forty Jacks: 40
d: 9H AS JH KD AD 10H QD 9C KH 10S 9D AD 
Would you like to continue playing?
yes
a: JD KD 10D 9D 9S KD AD 9C AH 9S QS 9D 
Pinochle: 40
b: 9H JS JH 10S JS 10D 10H AD JD JH AS 10C 
c: QD AC AS KC KH KS QC QC QD JC QH AH 
d: KH 10C AC 10H 10S 9H 9C QS QH KC KS JC 
Would you like to continue playing?
yes
a: 9D AS QS KD JC QD JS 9H 9C AH 9H JC 
b: AC 10C AH 10S AS JH KS QS KH JD 10D 10H 
Pinochle: 40
c: KC KC 10D 9S AD QC QD KS 9D KH JH 10H 
d: QC AC QH 10C JD 9S JS 10S KD AD 9C QH 
Would you like to continue playing?
yes
a: KC KD 9D 9S QH 9C AH 9C JD AC JC JH 
b: JS QD QH 9S AS QC 10D 9H KS KD KH 9H 
c: 10H KC JD AC 10C QS 9D QD AD 10S AH 10S 
Pinochle: 40
d: KS AS JH QS KH JC 10D JS QC 10H AD 10C 
Would you like to continue playing?

10. PLaying HoldEm: 
[a.j.sankoh@linuxlab002 lab_3]$ ./lab3 HoldEm a b c d e f g
a: 10H KD 
b: QD AD 
c: 3C 8S 
d: 6D 8D 
e: 10C KH 
f: 10D 2C 
g: JC 2H 
BOARD (flop): 
AC 
QS 
4H 
b: QD AD AC QS 4H -> Two Pair
a: 10H KD AC QS 4H -> X High
e: 10C KH AC QS 4H -> X High
g: JC 2H AC QS 4H -> X High
f: 10D 2C AC QS 4H -> X High
d: 6D 8D AC QS 4H -> X High
c: 3C 8S AC QS 4H -> X High
BOARD (turn): 
AC 
QS 
4H 
4S 
BOARD (river): 
AC 
QS 
4H 
4S 
6H 
Would you like to continue playing?
yes
a: 10D 2S 
b: JH 6S 
c: 9C 9H 
d: 7D 7H 
e: 10H 8H 
f: 6H 10S 
g: QD AS 
BOARD (flop): 
AH 
8S 
4D 
g: QD AS AH 8S 4D -> Pair
c: 9C 9H AH 8S 4D -> Pair
e: 10H 8H AH 8S 4D -> Pair
d: 7D 7H AH 8S 4D -> Pair
b: JH 6S AH 8S 4D -> X High
f: 6H 10S AH 8S 4D -> X High
a: 10D 2S AH 8S 4D -> X High
BOARD (turn): 
AH 
8S 
4D 
JC 
BOARD (river): 
AH 
8S 
4D 
JC 
JD 
Would you like to continue playing?
yes
a: 2H 5S 
b: 8D 7D 
c: QD 2C 
d: 3H 6H 
e: 6S 5D 
f: 4H 6D 
g: 8C 4C 
BOARD (flop): 
JS 
9S 
10H 
b: 8D 7D JS 9S 10H -> Straight
c: QD 2C JS 9S 10H -> X High
g: 8C 4C JS 9S 10H -> X High
e: 6S 5D JS 9S 10H -> X High
f: 4H 6D JS 9S 10H -> X High
d: 3H 6H JS 9S 10H -> X High
a: 2H 5S JS 9S 10H -> X High
BOARD (turn): 
JS 
9S 
10H 
KC 
BOARD (river): 
JS 
9S 
10H 
KC 
KH 
Would you like to continue playing?
yes
a: 2C 6D 
b: KS AS 
c: 10D 9C 
d: 6C 7S 
e: 3C AD 
f: KH 8D 
g: 6S JC 
BOARD (flop): 
QS 
QD 
7C 
d: 6C 7S QS QD 7C -> Two Pair
b: KS AS QS QD 7C -> Pair
e: 3C AD QS QD 7C -> Pair
f: KH 8D QS QD 7C -> Pair
g: 6S JC QS QD 7C -> Pair
c: 10D 9C QS QD 7C -> Pair
a: 2C 6D QS QD 7C -> Pair
BOARD (turn): 
QS 
QD 
7C 
7H 
BOARD (river): 
QS 
QD 
7C 
7H 
2S 
Would you like to continue playing?
yes
a: KC 4D 
b: 8C 7C 
c: JC 9C 
d: 4S 2D 
e: 10H KD 
f: 9S JS 
g: 6S 5D 
BOARD (flop): 
AC 
3D 
JD 
c: JC 9C AC 3D JD -> Pair
f: 9S JS AC 3D JD -> Pair
e: 10H KD AC 3D JD -> X High
a: KC 4D AC 3D JD -> X High
b: 8C 7C AC 3D JD -> X High
g: 6S 5D AC 3D JD -> X High
d: 4S 2D AC 3D JD -> X High
BOARD (turn): 
AC 
3D 
JD 
8H 
BOARD (river): 
AC 
3D 
JD 
8H 
7D 
Would you like to continue playing?
yes
a: QH 4H 
b: 10H 10C 
c: 8S 4S 
d: AD 3S 
e: 9H 5C 
f: 9S KD 
g: 7D 7H 
BOARD (flop): 
6C 
10D 
6D 
b: 10H 10C 6C 10D 6D -> Full House
g: 7D 7H 6C 10D 6D -> Two Pair
d: AD 3S 6C 10D 6D -> Pair
f: 9S KD 6C 10D 6D -> Pair
a: QH 4H 6C 10D 6D -> Pair
e: 9H 5C 6C 10D 6D -> Pair
c: 8S 4S 6C 10D 6D -> Pair
BOARD (turn): 
6C 
10D 
6D 
2D 
BOARD (river): 
6C 
10D 
6D 
2D 
3D 
Would you like to continue playing?
yes
a: JS 10H 
b: 8S 7C 
c: 4D 10S 
d: AS 5C 
e: 7D 6C 
f: 7S JH 
g: QS KS 
BOARD (flop): 
2D 
8C 
6S 
b: 8S 7C 2D 8C 6S -> Pair
e: 7D 6C 2D 8C 6S -> Pair
d: AS 5C 2D 8C 6S -> X High
g: QS KS 2D 8C 6S -> X High
a: JS 10H 2D 8C 6S -> X High
f: 7S JH 2D 8C 6S -> X High
c: 4D 10S 2D 8C 6S -> X High
BOARD (turn): 
2D 
8C 
6S 
10D 
BOARD (river): 
2D 
8C 
6S 
10D 
4H 
Would you like to continue playing?

Expected?: Yes 

--------------------------------------------------------------------------------------------

System Design Choices: 

Added Controlled Violation of Encapsulation: back_inserter_iterator of vector "pile" of cardset 
I declared and defined a back_inserter_iterator of the vector pile to the cardset so that you could indirectly 
write to the vector of a cardset using that inserter and iterators. I think this is a controlled violation of 
encapsulation that adequately provides you the same access as our pointer to class member variable did 
in lab 2, but with the use of iterators instead.

PinochleGame sort_cards function: PinochleGame declares and defines it's own sort_cards function which uses 
the sort_set function of cardsets because I sort hands in Pinochle differently than just sorting cards in ascending 
order (I sort by descending order). I decided it would be more modular and readable to define a sort cards function 
rather than just placing the function logic in some block of code.  

typedef for Card and vector iterators: I only defined a typedef for Card <Rank, Suit> because I feel like 
suit and rank are already easily readable and not error-prone to type. Defining a typedef for such as 
typedef Rank rank_type is redundant in my opinion. I decided to move the typedef for vector iterators 
into the HoldemGame and Pinochle Game source files respectively because I think it's important to distinguish 
between the two different types of Ranks, and having two seperate iterators make this simple. 

find_if function in CardSet request function: Since there isn't a defined == operator between cards and 
we're only comparing the ranks of cards in the call to find, I used find_if instead of find so I could 
put a predicate in which I defined earlier as a comparison between the ranks of cards. 

Template specializations for collect_books(): I decided to add template specializations for the collect_books()
function because the implementation required me to access the lowest enum of a respective rank. The easiest 
and most readable way to do this was with template specializations.

Templae specializations for other GoFishGame functions: Whenever a function had to deal with the specific ranks 
of a game (retrieve, check_input), it made sense for me to implement them has a specialization because of how the 
ranks differ between the games. The functionality for almost all the specializations are nearly identical other 
than how the ranks are dealt with.

Overloaded set_rank functions in Deck source files: To map a string input to a rank, I defined overloaded set_rank 
functions in the PinochleDeck, HoldEmDeck, and UnoDeck source files. These functions simply map a string input to a 
valid rank based on the deck that is being used for a GoFish game.

Changing the compare_equal hand rank function to one function for all suits: This is not related to most of Lab 3—but I 
changed the comparison functions in HoldEm when two players have equal hand ranks to one function that can be 
used for any hand rank instead of specific functions for each hand rank. This generalized my code a lot more and made the 
HoldEmGame header and source files a lot less cluttered.

Change implementation of collect_if function: In the instructions for Lab 3 we are told to use the remove_if 
function to remove cards from the passed in cardset in collect_if. While this function would work if we called 
it on the implicit cardset, I don't believe it would for a passed in cardset because we got rid of the accessor 
to a cardset's vector storing all their cards. I chose to instead create a duplicate cardset, populate the cardset 
with all of the old cardsets cards except for the rank that we collected, and then move the that cardset to the 
old cardset with std::move. This approach worked in many places where I had to remove cards from a cardset, but no 
longer had the accessor which we used in lab 2.


