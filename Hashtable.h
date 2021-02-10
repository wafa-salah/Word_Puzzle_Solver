//Name: Wafa Salah (wss9fb)
//Date: 10/6/20
//Hashtable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Hashtable {

public:
  Hashtable();
  Hashtable(unsigned int size);
  ~Hashtable();

  //methods
  void insert(string s);
  bool contains(string s) const;
  unsigned int hash(string key) const;

 private:
  unsigned int powers_of_11[22];
  vector<string> myTable;
  unsigned int tableSize;
  //string& myTable;

  //friend class wordPuzzle;
};


#endif
