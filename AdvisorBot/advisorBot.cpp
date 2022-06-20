#include "advisorBot.h"
#include <iostream>

AdvisorBot::AdvisorBot() {

}

void AdvisorBot::startAdvisorBot()
{
    shouldExit = false;
    std::string line;
    char delimiter = ' ';

    while(!shouldExit)
    {
        std::cout << "advisorBot: ";

        std::getline(std::cin, line);
        tokenVector = parser.parseText(line, delimiter);

        // a return value of 1 from processCommands indicates that program should exit
        if(commandProcessor.processCommands(tokenVector) == 1)
        {
            shouldExit = true;
        }
    }
}
