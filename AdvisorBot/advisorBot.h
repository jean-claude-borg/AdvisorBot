#pragma once
#include "parser.h"
#include "commands.h"

class AdvisorBot{

public:
    AdvisorBot();
    void startAdvisorBot();

private:
    bool shouldExit;
    std::vector<std::string> tokenVector;

Parser parser;
CommandProcessor commandProcessor;
};