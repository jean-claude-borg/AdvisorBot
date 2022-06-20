#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "AdvisorBot/advisorBot.h"

class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);

        std::string currentTime;

//        OrderBook orderBook{"20200317.csv"};
    // ../ is required on linux for relative file paths
	OrderBook orderBook{"../20200601.csv"};
        Wallet wallet;

    AdvisorBot advisorBot;
};
