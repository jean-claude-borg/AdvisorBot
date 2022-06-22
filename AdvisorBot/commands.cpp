#include "commands.h"

int CommandProcessor::processCommands(std::vector<std::string> tokenVector, OrderBook* orderBook)
{
    if(tokenVector[0] == "exit")
    {
        // return value of 1 means shouldExit
        return 1;
    }
    else if(tokenVector[0] == "help")
    {
        CommandProcessor::printHelp(tokenVector);
    }
    else if(tokenVector[0] == "clear")
    {
        CommandProcessor::clearScreen();
    }
    else if(tokenVector[0] == "prod")
    {
        CommandProcessor::listProducts(orderBook);
    }
    else if(tokenVector[0] == "min")
    {
        CommandProcessor::getMinimumBid(tokenVector, orderBook);
    }
    else if(tokenVector[0] == "max")
    {
        CommandProcessor::getMaximumBid(tokenVector, orderBook);
    }
    else if(tokenVector[0] == "avg")
    {
        CommandProcessor::getAverage(tokenVector, orderBook);
    }
    else if(tokenVector[0] == "time")
    {
        CommandProcessor::getTime(orderBook);
    }
    else if(tokenVector[0] == "step")
    {
        CommandProcessor::step(orderBook);
    }
    else if(tokenVector[0] == "stepBack")
    {
        CommandProcessor::stepBack(orderBook);
    }
    // return value of 0 means no errors
    return 0;
}

void CommandProcessor::printHelp(std::vector<std::string> tokenVector)
{
    auto numberOfTokens = tokenVector.size();
    if(numberOfTokens == 1)
        std::cout << "\nThe available commands are help, help cmd, prod, min, max, avg, predict, time, step and clear\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "prod")
        std::cout << "\nThe prod command will show all available products as a list\n" << std::endl;
}

void CommandProcessor::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void CommandProcessor::listProducts(OrderBook* orderBook)
{
    auto productVector = orderBook->getKnownProducts();
    std::cout << "\n" << std::endl;

    for(int i = 0; i < productVector.size(); i++)
    {
        std::cout << productVector[i] << std::endl;
    }

    std::cout << "\n" << std::endl;
}

void CommandProcessor::getMinimumBid(std::vector<std::string> tokenVector, OrderBook* orderBook)
{
    //put all entries with current timeStep in new vector
    enum OrderBookType type;

    if(tokenVector[2] == "bid")
        type = OrderBookType::bid;
    else if(tokenVector[2] == "ask")
        type = OrderBookType::ask;

    std::vector<OrderBookEntry> latestOrders = orderBook->getOrders(type, tokenVector[1], orderBook->currentTime);

    OrderBookEntry lowestOrder = latestOrders[0];

    for(int i = 0; i < latestOrders.size(); i ++)
    {
        if(latestOrders[i].price < lowestOrder.price)
            lowestOrder = latestOrders[i];
    }

    //print OrderBookEntry
    if(type == OrderBookType::bid)
        std::cout << "\n" << lowestOrder.timestamp << ", " << lowestOrder.product << ", " << "bid, " << lowestOrder.price << ", " << lowestOrder.amount << "\n" << std::endl;
    else if(type == OrderBookType::ask)
        std::cout << "\n" << lowestOrder.timestamp << ", " << lowestOrder.product << ", " << "ask, " << lowestOrder.price << ", " << lowestOrder.amount << "\n" << std::endl;
}

void CommandProcessor::getMaximumBid(std::vector<std::string> tokenVector, OrderBook* orderBook)
{
    //put all entries with current timeStep in new vector
    enum OrderBookType type;

    if(tokenVector[2] == "bid")
        type = OrderBookType::bid;
    else if(tokenVector[2] == "ask")
        type = OrderBookType::ask;

    std::vector<OrderBookEntry> latestOrders = orderBook->getOrders(type, tokenVector[1], orderBook->currentTime);

    OrderBookEntry highestOrder = latestOrders[0];

    for(int i = 0; i < latestOrders.size(); i ++)
    {
        if(latestOrders[i].price > highestOrder.price)
            highestOrder = latestOrders[i];
    }

    //print OrderBookEntry
    if(type == OrderBookType::bid)
        std::cout << "\n" << highestOrder.timestamp << ", " << highestOrder.product << ", " << "bid, " << highestOrder.price << ", " << highestOrder.amount << "\n" << std::endl;
    else if(type == OrderBookType::ask)
        std::cout << "\n" << highestOrder.timestamp << ", " << highestOrder.product << ", " << "ask, " << highestOrder.price << ", " << highestOrder.amount << "\n" << std::endl;
}

void CommandProcessor::getAverage(std::vector<std::string> tokenVector, OrderBook* orderBook)
{
    //tokenVector[1] = product, 2 = bid or ask, 3 = timesteps(int)
    int numberOfTimesteps = std::stoi(tokenVector[3]);

}

void CommandProcessor::getTime(OrderBook* orderBook)
{
    std::cout << "\nThe current focused timestep is: " << orderBook->currentTime << "\n" << std::endl;
}

void CommandProcessor::step(OrderBook* orderBook)
{
    orderBook->currentTime = orderBook->getNextTime(orderBook->currentTime);
}

void CommandProcessor::stepBack(OrderBook* orderBook)
{
    orderBook->currentTime = orderBook->getPreviousTime(orderBook->currentTime);
}
