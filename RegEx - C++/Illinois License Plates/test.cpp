#include "catch.hpp"
#include "ILplates.h"
#include <string>


bool CheckVanity(string &plate){
  //This is if the plate is only numbers
  if(plate[0] > 47 && plate[0] < 58 && plate.length() > 3) return false;
  else if(plate.length() > 7) return false;

  //Lambda to check the whole string
  auto vanChecker = [&](char &a){
    if(plate[0] > 47 && plate[0] < 58)
      return(a > 47 && a < 58);
    else
      return(a > 64 && a < 91);
  };

  return all_of(plate.begin(),plate.end(),vanChecker);
}

//Helper function to check Personalized Plates
bool CheckPersonalized(string &plate){
  //Checks proper length and starting with a letter
  if(plate.length() > 8)return false;
  if(!(plate[0] > 64 && plate[0] < 91))return false;
  
  bool CheckNumber = false;
  int numCount = 0;

  auto perCheck = [&](char &a){
    if(a == 32) {
        CheckNumber = true;
        return true;
    }
    if(CheckNumber){
      numCount++;
      if(numCount > 2) return false;
      return (a > 47 && a < 58) || a==32;
    }
    else
      return (a > 64 && a < 91)  || a==32;
  };

  return all_of(plate.begin(),plate.end(),perCheck) && CheckNumber;
}


int test(string &plate){
  int index = -1;
  auto isPerso = find(plate.begin(),plate.end(),' ');
  int numSpaces = count(plate.begin(),plate.end(), ' ');
  bool cont;

  //Too many spaces
  if(numSpaces > 1) return index;
  //Make sure that the String is in proper format
  if(isPerso == plate.end()){
    cont = CheckVanity(plate);
  }
  else{
    cont = CheckPersonalized(plate);
  }
  if(cont) std::cout << plate << std::endl;
  if(!cont) return index;

}

int main()
{
    std::vector<std::string> testStr {"T 60","WWWW 10","UVWXY ZZ","ILUVUIC"};

    for(auto &a : testStr){
        test(a);
    }

    return 0;
}