#pragma once
#include <iostream>
#include <vector>
#include "../OrderBook.h"

class CommandProcessor{

public:
    static int processCommands(std::vector<std::string> tokenVector, OrderBook* orderBook);
    static void printHelp(std::vector<std::string> tokenVector);
    static void listProducts(OrderBook* orderBook);
    static void getMinimumBid(std::vector<std::string> tokenVector, OrderBook* orderBook);
    static void getMaximumBid(std::vector<std::string> tokenVector, OrderBook* orderBook);
    static void getAverage(std::vector<std::string> tokenVector, OrderBook* orderBook);
    static void getTime(OrderBook* orderBook);
    static void step(OrderBook* orderBook);
    static void stepBack(OrderBook* orderBook);
    static void predict(std::vector<std::string> tokenVector, OrderBook* orderBook);
    static void stepEarliest(OrderBook* orderBook);
    static void stepLatest(OrderBook* orderBook);
    static void jump(OrderBook* orderBook, std::vector<std::string> tokenVector);

private:
    static void clearScreen();
};