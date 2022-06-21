#pragma once
#include <iostream>
#include <vector>
#include "../OrderBook.h"

class CommandProcessor{

public:
    static int processCommands(std::vector<std::string> tokenVector, OrderBook orderBook);
    static void printHelp(std::vector<std::string> tokenVector);
    static void listProducts(OrderBook orderBook);
    static void getMinimumBid(std::vector<std::string> tokenVector, OrderBook orderBook);

private:
    static void clearScreen();
};