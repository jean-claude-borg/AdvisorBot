#pragma once
#include <iostream>
#include <vector>

class CommandProcessor{

public:
    static int processCommands(std::vector<std::string> tokenVector);
    static void printHelp();

private:
    static void clearScreen();
};