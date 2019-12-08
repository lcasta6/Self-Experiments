/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// Luis Castaneda
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <regex>
#include "ILplates.h"

using namespace std;


//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH

bool isNum(string &plate){
  return plate[0] > 47 && plate[0] < 58;
}
bool isNum(char &a){
  return a > 48 && a < 58;
}

//Hashing function
int ILplates::Hash(string plate)
{
  unsigned long long index = -1;

  //Make sure that the plate is in the format we're looking for
  std::regex vanity("([0-9]{1,3})|([A-Z]{1,7})");
  std::regex personalized("([A-Z]{1,5}\\s[0-99])|([A-Z]{1,6}\\s[0-9])");
  std::smatch match;


  if(!(std::regex_search(plate,match,vanity)) && !(std::regex_search(plate,match,personalized)))
    return index;


  //********************This is where Hashing will begin.************************//

  //If it's just a number then the number will just go to its indexed for, max is 999
  if(isNum(plate)) {
    index = stoi(plate);
    return index % HT.Size();
  }

  //If it's not a number, then it's a combination of numbers and letters
  unsigned long long chunk = 0;
  string retNum = "";

  for(auto &a : plate){
    if((a > 64 && a < 91))
      chunk += ((a - 'A') * 999) + (1*(a - 'A'));
  }

  auto hasNum = any_of(plate.begin(),plate.end(),[](char &a){
    return a>47 && a<58; 
  });

  //We check if the plate consist of only letters or not.
  if(hasNum){
    for(auto &a:plate)
      if(isNum(a))
        retNum = retNum + a;

    index = pow((chunk) + (stoi(retNum) * 999),3)/18;
  }
  else
    index = chunk;

  //return after it's been calculated.
  return index/2 % HT.Size();
}


//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
  //
  // TODO:
  //
  //Temp Parameters
  bool EmptyOrNot;
  string Key;
  int Value;

  int bucket = Hash(plate);
  int bucketsProbed = 0;

  while(bucketsProbed < HT.Size()){
    HT.Get(bucket,EmptyOrNot,Key,Value);

    if(EmptyOrNot){
      return -1;
    }
    else if(Key == plate){
      return Value;
    }

    bucket = (bucket + 1);
    bucketsProbed++;
  }

  return Value;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
  //
  // TODO:
  //
  int bucket = Hash(plate);
  int bucketsProbed = 0;

  //Temp Parameters
  bool EmptyOrNot;
  string Key;
  int Value = 0;

  //Loop Through Until you get an empty bucket
  while(bucketsProbed < HT.Size()){

    HT.Get(bucket,EmptyOrNot,Key,Value);

  //If the bucket was empty, just insert
    if(EmptyOrNot){
      HT.Set(bucket,plate,newValue);
      return;
    }

  //If the plate is already in the hash and all we need to do is update the ammount;
    else if(Key == plate){
      HT.Set(bucket,plate,newValue) ;
      return;
    }

  //Otherwise keep probing the Bucket
    bucket = (bucket + 1);
    bucketsProbed++;
  }

  return;
}
