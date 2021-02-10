# Word_Puzzle_Solver 

CS 2150 Program and Data Representation Fall 2020 Assignment 6

Assignment Instructions:

            You need to implement a solution to the word puzzle problem described (look at Word_Search.png in main). Given a dictionary and word search grid, your program should output all the words in the grid that are in the dictionary.

            There are two main parts: 
              (1) Creating a hash table (Must write your own; can NOT use any STL hash table) --> My Solutions for this is found in Hashtable.h and Hashtable.cpp
              (2) Writing a word search solver --> My solution for this is found in wordPuzzle.cpp; which also contains the main() function and uses a hashtable created using (1). 

              Optimize your solution, We are interested in the timing of how long it takes to find all the valid words in a grid. Timing can be tested using the timer.h and timer.cpp programs provided.
  
  My Implementation:
  
              Used the C++ vector class as the base for my hash table.
              
              Linear Probing was used as the collision-resolution strategy.
              
              Look at hashtable.cpp to see how the hashkey was calculated. 
              
              Construction of hashtable, hence its capacity, is dependent on the number of inputted words in the dictionary. Therefore, there is no need to double the hashtable at any point, as it will always be above the maximum capacity needed to solve the word puzzle.
              
              Final result: 
              
                After numerous optimizations inlcuding adjusting the potential loadfactor, testing various collision-resolution strategies, and doing minor tweaks in the wordPuzzle solver program itself (such as printing after all words are found instead of while they are being discovered), the program was able to solve the largest puzzle provided --500x500 word search grid-- in about 6 seconds. 
