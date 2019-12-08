/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     << YOUR NAME >>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;


//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}

void bubbleSort(vector<pair<string,int>>& a);

int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  //We're doing a vector of pair to properly
  //store our outputs;
  vector<pair<string,int>> toOut;

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();

  for (size_t i = 0; i < plates.size(); ++i)
  {
    cout << plates[i] << ", " << amounts[i] << endl;
    toOut.push_back(make_pair(plates[i],amounts[i]));
  }

  //OutPut a file with the sorted values
  bubbleSort(toOut);
  ofstream outfile(basename + "-output.txt");

  for(auto &a : toOut){
    outfile << "\"" << a.first << "\"" << " $" << a.second << endl;
  }

  //
  // done:
  //
  return 0;
}

void bubbleSort(vector<pair<string,int>>& vec)
{
      bool have_swapped = true;
    for (unsigned j = 1; have_swapped && j < vec.size(); ++j) {
        have_swapped = false;
        for (unsigned i = 0; i < vec.size() - j; ++i) {
            if (vec[i].first > vec[i + 1].first) {
                have_swapped = true;
                pair<string,int> tempObj = vec[i];  // Just use:
                vec[i] = vec[i + 1];      //    std::swap(vec[i], vec[i + 1]);
                vec[i + 1] = tempObj;     // instead of these three lines.
            }
        }
    }
}