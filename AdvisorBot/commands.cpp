#include "commands.h"

int CommandProcessor::processCommands(std::vector<std::string> tokenVector) {

    if(tokenVector[0] == "exit")
    {
        // return value of 1 means shouldExit
        return 1;
    }
    else if(tokenVector[0] == "help")
    {
        CommandProcessor::printHelp();
    }
    else if(tokenVector[0] == "clear")
    {
        CommandProcessor::clearScreen();
    }

    // return value of 0 means no errors
    return 0;
}

void CommandProcessor::printHelp()
{
    std::cout << "\nThe available commands are help, help cmd, prod, min, max, avg, predict, time, step and clear\n" << std::endl;
}

void CommandProcessor::clearScreen() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}