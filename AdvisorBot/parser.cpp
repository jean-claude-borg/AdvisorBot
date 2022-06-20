#include "parser.h"
#include <sstream>
#include <bits/stdc++.h>

std::vector<std::string> Parser::parseText(std::string text, char delimiter) {

    std::vector<std::string> tokenVector;

    // stringstreams will emulate an input stream containing the supplied string
    // this allows us to tokenise the string by simply using getline on the emulated input stream
    std::stringstream stream1(text);
    std::string tempToken; // this will store the token generated for each iteration

    while(getline(stream1, tempToken, delimiter))
    {
        tokenVector.push_back(tempToken);
    }

    return tokenVector;
}