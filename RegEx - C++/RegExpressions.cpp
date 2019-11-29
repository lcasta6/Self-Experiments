#include <iostream>
#include <regex>
#include <string>

int main(){
    std::string x = "8";
    std::string y = "h";
    std::string z = "8h";
    std::string i = "";

    //RedEx that takes in one number and makes a letter optional
    std::regex pat ("\\d(\\w)?");

    //RedEx that only allows 1 or 2 or 3
    std::regex anotherPat ("[1-3]");

    std::smatch match;

    /********* RegEx 'pat' Experiments ************/
    if(std::regex_search(x,match,pat))
        std::cout << "THIS WORKED!\n";

    if(!std::regex_search(y,match,pat))
        std::cout << "THIS DID NOT WORKED!\n";

    if(std::regex_search(z,match,pat))
        std::cout << "THIS ALSO WORKED!\n";


    std::cout << "\nEND OF FIRST PATTERN\n\n";
    /********* RegEx 'anotherPat' Experiments ************/
    x = "1";
    y = "8";
    z = "2";
    i = "h";


    if(std::regex_search(x,match,anotherPat))
        std::cout << "THIS WORKED!\n";

    if(std::regex_search(y,match,anotherPat))
        std::cout << "THIS WORKED!\n";

    if(std::regex_search(z,match,anotherPat))
        std::cout << "THIS WORKED!\n";

    if(std::regex_search(i,match,anotherPat))
        std::cout << "THIS WORKED!\n";

    return 0;
}