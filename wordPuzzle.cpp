//Name: Wafa Salah (wss9fb)
//Date: 10/11/20
//wordPuzzle.cpp

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Hashtable.h"
#include "timer.h"
#include <vector>  //for storing words found
using namespace std;

//COPY-PASTED from getWordInGrid.cpp (part 1/2) --> Given Code;this chunk is not written by Wafa
// We create a 2-D array of some big size, and assume that the grid
// read in will be less than this size (a valid assumption for lab 6)
#define MAXROWS 500
#define MAXCOLS 500
char grid[MAXROWS][MAXCOLS];
Hashtable the_dict;
vector<string> theWords; //will store all the discovered words for printing later

// Forward declarations
bool readInGrid(string filename, int& rows, int& cols);
string getWordInGrid(int startRow, int startCol, int dir, int len,
                     int numRows, int numCols);
bool checkprime(unsigned int p);
int getNextPrime (unsigned int n);

//end of code from the grid reading file (part 1/2)



/** this function reads from a file and stores the words into a global hashtable the_dict */
bool readInDict(string filename) {
  //opening file
  ifstream file(filename);
  //upon error, return false
  if (!file.is_open()) {
    return false;
  }

  int numb_words = 1;
  string word;
  while (file.good()) { 
    file >> word;
    the_dict.insert(word);
    numb_words++;
  }

  file.close();

  return true;
}




/** function takes in the number of rows & colums of the grid,
    generates words from the grid, 
    cross-checks if word is present in the dictionary, 
    prints it out if there's a match
    assumptions/given: maximum length of word there can be a match for is 22; minimum is 3; */

void isMatch(int num_rows, int num_cols) {
  int numb_matches = 0;
  for (int r=0; r < num_rows; r++) { //rows
    for (int c=0; c < num_cols; c++) { //columns
      for (int dirxn=0; dirxn < 8; dirxn++) { //direction
	
	//strictly for printing purposes per assignment instructions
	string d;
	if (dirxn == 0) {d = "N";}
	else if (dirxn == 1) {d = "NE";}
	else if (dirxn == 2) {d = "E";}
	else if (dirxn == 3) {d = "SE";}
	else if (dirxn == 4) {d = "S";}
	else if (dirxn == 5) {d = "SW";}
	else if (dirxn == 6) {d = "W";}
	else{d = "NW";} //the only one left is dirxn = 7

	for (int length=3; length < 23; length++) { //length of the word we are searching for
	  string grid_word = getWordInGrid(r,c,dirxn,length,num_rows,num_cols);
	  if (grid_word.size() == length) { 
	    if (the_dict.contains(grid_word)) {
	      string wwd;
	      wwd = d + " (" + to_string(r) + ", " + to_string(c) + "): " + grid_word;
	      theWords.push_back(wwd);
	      
	      //cout << d << " " << "(" << r << ", " << c << "): " << grid_word << endl;
	      numb_matches++;
	    }
	  }
	}
      }
    }
  }

  cout << numb_matches << " words found" << endl;
}




//////////////////////////////////// MAIN FUNCTION /////////////////////////////////

int main(int argc, char **argv) {
  if (argv[1] == NULL) {
    cout << "Please input command-line parameters."<< endl;
    exit(-1);
  }

  
  //dictionary reading (1) -->to determine size of hashtable
  string dict_txt(argv[1]);
  ifstream file(dict_txt);
  
  //upon error, return false
  if (!file.is_open()) {
    cout << "Error reading in the dictionary file!" << endl;
    return 1;
  }

  string read;
  unsigned int numWords = 0; // will tell program the # spots I need in hashtable
  while (file.good()) { 
    file >> read;
    numWords++;
  }
  file.close();

  unsigned int tabSize = getNextPrime(numWords);
  
  the_dict = Hashtable(tabSize);  //constructs the hastable with the appropriate size


  //dictionary reading (2) --> to insert into the hashtable
  bool read_dict_success = readInDict(dict_txt);
  if(!read_dict_success) {
    cout << "Error reading the dictionary file!" << endl;
    return 1;
  }
  
  //grid reading
  int rows, cols; 
  string grid_txt(argv[2]); //second commandline param is the grid txt
  bool read_grid_success = readInGrid(grid_txt, rows, cols);
  if (!read_grid_success) {
    cout << "Error reading the grid file!" << endl;
    return 1;
  }


  //start timer
    timer t;
    t.start();
    isMatch(rows,cols);

    for (int i = 0; i < theWords.size(); i++){
      cout << theWords[i] << endl;
    }
    
    for (int i = 0; i < 1000000000; i++) {}
    t.stop();
    cout << "Found all words in " << t.getTime() << " seconds" << endl;

  return 0;
}



//COPY-PASTED from getWordInGrid.cpp (part 2/2) --> Given Code; this chunk is not written by Wafa

//implementation of readInGrid function --> read the source file to better understand
bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
    ifstream file(filename);
    // upon an error, return false
    if (!file.is_open()) {
        return false;
    }

    // first comes the number of rows
    file >> rows;
    //cout << "There are " << rows << " rows." << endl;

    // then the columns
    file >> cols;
    //cout << "There are " << cols << " cols." << endl;

    // and finally the grid itself
    string data;
    file >> data;

    // close the file
    file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
            //cout << grid[r][c];
        }
        //cout << endl;
    }
    return true;
}

//Implementation of getWordInGrid --> look at source file to better understand
string getWordInGrid (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocation.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= numCols || r >= numRows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }

    return output;
}


//End of input from the grid reading file (part 2/2)


// Prime Number input

bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}
