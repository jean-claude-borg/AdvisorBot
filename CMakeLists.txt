cmake_minimum_required(VERSION 3.22)
project(AdvisorBot)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AdvisorBot
        CSVReader.cpp
        CSVReader.h
        main.cpp
        MerkelMain.cpp
        MerkelMain.h
        OrderBook.cpp
        OrderBook.h
        OrderBookEntry.cpp
        OrderBookEntry.h
        Wallet.cpp
        Wallet.h AdvisorBot/advisorBot.cpp AdvisorBot/advisorBot.h AdvisorBot/parser.cpp AdvisorBot/parser.h AdvisorBot/commands.cpp AdvisorBot/commands.h)
