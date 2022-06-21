#pragma once
#include "parser.h"
#include "commands.h"
#include "../OrderBook.h"

class AdvisorBot{

public:
    AdvisorBot();
    void startAdvisorBot(OrderBook orderBook);

private:
    bool shouldExit;
    std::vector<std::string> tokenVector;

Parser parser;
CommandProcessor commandProcessor;
};