//Name: Wafa Salah (wss9fb)
//Date: 10/12/20
//Hashtable.cpp

#include "Hashtable.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath> //to use pow()

using namespace std;

Hashtable::Hashtable() {};


Hashtable::Hashtable(unsigned int size) {
  for (int i=0; i<22; i++) {
    if (i==19 || i==20 || i==21) { //pow(11,i) of these three values is gonna evaluate to 0 b/c
                                   //there's not enough bits in unsigned int to rep actual value
      powers_of_11[i] = pow(7,i);
    }
    else {
      powers_of_11[i] = pow(11,i);}
  }


   tableSize = size * 11;
   myTable = vector<string>(tableSize, "");

}

Hashtable::~Hashtable() {}


void Hashtable::insert(string s) {
  unsigned int index = hash(s);
  if (myTable[index] == "") { //Empty spot, NO Collision
    myTable[index] = s;
  }

  else { //There is a collision --> resolving strategy: Linear Probing

    //PSEUDO -- Linear Probing
    //while index++ is not empty, keep adding
    int newIndex = index;
    while ( myTable[newIndex] != "") { 
      newIndex++;
      if (newIndex >= tableSize) { //index has gone out of bound
	newIndex = newIndex % tableSize; //makes it wrap around
      }
    }
    myTable[newIndex] = s;
  }
}

unsigned int Hashtable::hash(string key) const{
  unsigned int hashNum = 0;
  for (int i = 0; i < key.size(); i++ ) {
    hashNum += (key.at(i) * powers_of_11[i]);
  }

  hashNum = hashNum % tableSize;
  return hashNum;
  
}

/** will return false in two cases: 
    1) string is not in there, i.e --> you run into your first "" if the hash indx it supposed to be at is already taken by another s
    2)  there's another string there, so linearly searches and runs into "" before the target string */
bool Hashtable::contains(string s) const{
  unsigned int indx = hash(s); //where the s is supposed to be if it got inserted unless it's linearly probed
  string valueAtIndx = myTable[indx];
  if (valueAtIndx == s) { // target string is found, return true
    return true;
  }

  else {
    if (valueAtIndx == "") { //Nothing was ever inserted here, so just return false
      return false;
    }
    else { //there was a collision at this spot, so look linearly until you find your s or an empty string
      int newIndx = indx;
      while (myTable[newIndx] != s && myTable[newIndx] != "") {
	newIndx++;
	if (newIndx >= tableSize) { //makes sure to not go out of bound
	  newIndx = newIndx % tableSize;
	}	
      }// end of while loop

      //Only two reasons/cases it left while loop 1) myTable[newIndx] == s OR 2) myTable[newIndx] == ""

      //case 1
      if (myTable[newIndx] == s) {return true;}

      //case 2
      else {return false;}
    }
  }
}
