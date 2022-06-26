#include "commands.h"
#include "OrderBookEntry.h"

int CommandProcessor::processCommands(std::vector<std::string> tokenVector, OrderBook* orderBook)
{
    if(tokenVector.empty())
        return 3; //return value of 3 means user inputted nothing

    else if(tokenVector[0] == "exit")
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
    else if(tokenVector[0] == "stepEarliest")
    {
        CommandProcessor::stepEarliest(orderBook);
    }
    else if(tokenVector[0] == "stepLatest")
    {
        CommandProcessor::stepLatest(orderBook);
    }
    else if(tokenVector[0] == "jump")
    {
        CommandProcessor::jump(orderBook, tokenVector);
    }
    else if(tokenVector[0] == "predict")
    {
        CommandProcessor::predict(tokenVector, orderBook);
    }
    //if no available command is entered, prints a message saying the command does not exist
    else
    {
        std::cout << "\n" << tokenVector[0] << ": command not found, type help for a list of commands\n" << std::endl;
        return 2; // return value of 2 indicates that user inputted invalid command
    }
    // return value of 0 means no errors
    return 0;
}

void CommandProcessor::printHelp(std::vector<std::string> tokenVector)
{
    auto numberOfTokens = tokenVector.size();
    if(numberOfTokens == 1)
        std::cout << "\nThe available commands are help, prod, min, max, avg, predict, time, step, stepBack, clear and exit\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "prod")
        std::cout << "\nThe prod command will show all available products as a list\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "clear")
        std::cout << "\nThe clear command will clear the screen\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "min")
        std::cout << "\nThe min command will find the minimum price of the given product in the current timestep\n"
                  << "Syntax: min [product] [bid/ask]\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "max")
        std::cout << "\nThe max command will find the maximum price of the given product in the current timestep\n"
                  << "Syntax: max [product] [bid/ask]\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "avg")
        std::cout << "\nThe avg command will find the average bid/ask price of the given product over the given timesteps\n"
                  << "Syntax: avg [product] [bid/ask] [timesteps]\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "predict")
        std::cout << "\nThe predict command will attempt to predict the min/max price(ask or bid) of the given product\n"
                  << "Syntax: predict [max/min] [product] [bid/ask]\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "time")
        std::cout << "\nThe time command will print the current timestep in focus\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "step")
        std::cout << "\nThe step command will move focus to the next timestep\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "stepBack")
        std::cout << "\nThe stepBack command will move focus to the previous timestep\n" << std::endl;
    else if(numberOfTokens == 2 && tokenVector[1] == "exit")
        std::cout << "\nThe exit command will exit this program\n" << std::endl;

    else
    {
        if(numberOfTokens == 2)
            std::cout << "\n" <<tokenVector[1] << ": command does not exist, type help for a list of commands\n" << std::endl;
        else
            std::cout << "\nerror: invalid number of arguments, expected 1 but got " << numberOfTokens-1 << "\n" << std::endl;
    }
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
    //makes sure correct number of arguments were passed to function
    auto numberOfTokens = tokenVector.size();
    if(numberOfTokens != 3)
    {
        std::cout << "\nerror: invalid number of arguments, expected 2 but got " << numberOfTokens-1 << "\n" << std::endl;
        return;
    }

    std::string product = tokenVector[1];
    std::string productType = tokenVector[2];

    //put all entries with current timeStep in new vector
    enum OrderBookType type;
    if(productType == "bid")
        type = OrderBookType::bid;
    else if(productType == "ask")
        type = OrderBookType::ask;
    //if user inputted invalid type:
    else
    {
        std::cout << "\n" << productType << ": not a valid product type, expected bid or ask\n" << std::endl;
        return;
    }

    std::vector<OrderBookEntry> latestOrders = orderBook->getOrders(type, product, orderBook->currentTime);

    //since orderType is already verified, if latestOrders is empty, it means that the user inputted an invalid product
    if(latestOrders.empty())
    {
        std::cout << "\n" << product << ": invalid product, use prod command for a list of available products\n" << std::endl;
        return;
    }

    //latestOrders is a vector containing all the correct orders
    OrderBookEntry lowestOrder = latestOrders[0];
    for(int i = 0; i < latestOrders.size(); i ++)
    {
        if(latestOrders[i].price < lowestOrder.price)
            lowestOrder = latestOrders[i];
    }

    //prints the lowest price
    std::cout << "\nThe min " << productType << " for " << product << " is " << lowestOrder.price << "\n" << std::endl;
}

void CommandProcessor::getMaximumBid(std::vector<std::string> tokenVector, OrderBook* orderBook)
{
    //makes sure correct number of arguments were passed to function
    auto numberOfTokens = tokenVector.size();
    if(numberOfTokens != 3)
    {
        std::cout << "\nerror: invalid number of arguments, expected 2 but got " << numberOfTokens-1 << "\n" << std::endl;
        return;
    }

    std::string product = tokenVector[1];
    std::string productType = tokenVector[2];

    enum OrderBookType type;
    if(productType == "bid")
        type = OrderBookType::bid;
    else if(productType == "ask")
        type = OrderBookType::ask;
        //if user inputted invalid type:
    else
    {
        std::cout << "\n" << productType << ": not a valid product type, expected bid or ask\n" << std::endl;
        return;
    }

    //latestOrders is a vector containing all the correct orders
    std::vector<OrderBookEntry> latestOrders = orderBook->getOrders(type, product, orderBook->currentTime);

    //since orderType is already verified, if latestOrders is empty, it means that the user inputted an invalid product
    if(latestOrders.empty())
    {
        std::cout << "\n" << product << ": invalid product, use prod command for a list of available products\n" << std::endl;
        return;
    }

    OrderBookEntry highestOrder = latestOrders[0];
    for(int i = 0; i < latestOrders.size(); i++)
    {
        if(latestOrders[i].price > highestOrder.price)
            highestOrder = latestOrders[i];
    }

    //prints the highest price
    std::cout << "\nThe max " << productType << " for " << product << " is " << highestOrder.price << "\n" << std::endl;
}

void CommandProcessor::getAverage(std::vector<std::string> tokenVector, OrderBook* orderBook)
{
    //tokenVector[1] = product, 2 = bid or ask, 3 = timesteps(int)
    int numberOfTimesteps;
    try {
        numberOfTimesteps = std::stoi(tokenVector[3]);
    }catch (std::exception &e){
        std::cout << "\nerror: invalid input, expected an integer but received: " << tokenVector[3] << "\n" << std::endl;
        return;
    }
    std::string currentTimestep = orderBook->currentTime;
    std::string workingTimestep = currentTimestep;
    std::string productType = tokenVector[2];
    std::string product = tokenVector[1];

    enum OrderBookType type;
    if(productType == "bid")
        type = OrderBookType::bid;
    else if(productType == "ask")
        type = OrderBookType::ask;
        //if user inputted invalid type:
    else
    {
        std::cout << "\n" << productType << ": not a valid product type, expected bid or ask\n" << std::endl;
        return;
    }

    double totalPrice = 0;
    double totalOrders = 0;
    std::vector<OrderBookEntry> orders;

    //prevents going back more timesteps than are available
    if(numberOfTimesteps <= orderBook->indexOfVectorWithMatchingTimestamps) {
        for (int i = 0; i < numberOfTimesteps; i++) {
            orders = orderBook->getOrders(type, product, workingTimestep);
            workingTimestep = orderBook->getPreviousTime(workingTimestep);
            orderBook->indexOfVectorWithMatchingTimestamps--;

            for(int j = 0; j < orders.size(); j++) {
                totalPrice += orders[j].price;
                totalOrders++;
            }
        }
        //sets the indexOfVectorWithMatchingTimestamps back to its original value,
        //as the avg command should not change the current time being looked at by the user
        orderBook->indexOfVectorWithMatchingTimestamps += numberOfTimesteps;

        //if no orders were found, since the only unvalidated input is product name,
        //that implies that user inputted invalid product name
        if(orders.empty())
        {
            std::cout << "\nerror, " << product << " is not a valid product, use the prod command for a list of available products\n" << std::endl;
            return;
        }
        //if everything went well, prints expected output
        std::cout << "The average is: " << totalPrice/totalOrders << std::endl;
    }
    else
    {
        std::cout << "\nerror, cannot go back " << numberOfTimesteps << " timesteps as there are not enough previous timesteps available..." << std::endl;
        std::cout << "There are a total of " << orderBook->totalNumberOfTimesteps << " available timesteps and " << orderBook->indexOfVectorWithMatchingTimestamps << " previous timesteps\n" << std::endl;
    }
}

void CommandProcessor::predict(std::vector<std::string> tokenVector, OrderBook* orderBook)
{
    //tokenVector[1] = max/min, 2 = product, 3 = bid or ask

    // number of timesteps to take into account is set by default to the maximum possible
    int numberOfTimesteps = orderBook->indexOfVectorWithMatchingTimestamps;

    std::string currentTimestep = orderBook->currentTime;
    std::string workingTimestep = currentTimestep;
    OrderBookType type = OrderBookEntry::stringToOrderBookType(tokenVector[3]);

    double totalMaxPrice = 0;
    double totalMinPrice = 0;
    std::vector<OrderBookEntry> orders;

    for(int i = 0; i < numberOfTimesteps; i++)
    {
        orders = orderBook->getOrders(type, tokenVector[2], workingTimestep);
        workingTimestep = orderBook->getPreviousTime(workingTimestep);
        orderBook->indexOfVectorWithMatchingTimestamps--;

        totalMaxPrice += OrderBook::getHighPrice(orders);
        totalMinPrice += OrderBook::getLowPrice(orders);
    }
    //sets the indexOfVectorWithMatchingTimestamps back to its original value,
    //as the avg command should not change the current time being looked at by the user
    orderBook->indexOfVectorWithMatchingTimestamps += numberOfTimesteps;

    if(tokenVector[1] == "max")
        std::cout << "\nThe predicted maximum " << tokenVector[3] << " for " << tokenVector[2] << " is: " << totalMaxPrice/numberOfTimesteps << "\n" << std::endl;
    else if(tokenVector[1] == "min")
        std::cout << "\nThe predicted minimum " << tokenVector[3] << " for " << tokenVector[2] << " is: " << totalMinPrice/numberOfTimesteps << "\n" << std::endl;
}

void CommandProcessor::getTime(OrderBook* orderBook)
{
    std::cout << "\nThe current focused timestep is: " << orderBook->currentTime << "\n" << std::endl;
}

void CommandProcessor::step(OrderBook* orderBook)
{
        std::string oldTime = orderBook->currentTime;
        std::string newTime = orderBook->getNextTime(orderBook->currentTime);

        //if oldTime == newTime, the time was not changed, therefore do not update indexOfVectorWithMatchingTimestamps
        if (oldTime != newTime) {
            orderBook->currentTime = newTime;
            orderBook->indexOfVectorWithMatchingTimestamps++;
        } else
            std::cout << "\nError: cannot step, current timestep is the latest timestep\n" << std::endl;

}

void CommandProcessor::stepBack(OrderBook* orderBook)
{
    std::string oldTime = orderBook->currentTime;
    std::string newTime = orderBook->getPreviousTime(orderBook->currentTime);

    //if oldTime == newTime, the time was not changed, therefore do not update indexOfVectorWithMatchingTimestamps
    if(oldTime != newTime)
    {
        orderBook->currentTime = newTime;
        orderBook->indexOfVectorWithMatchingTimestamps--;
    }
    else
        std::cout << "\nerror: cannot stepBack, current timestep is the earliest timestep\n" << std::endl;
}

void CommandProcessor::stepEarliest(OrderBook *orderBook)
{
    orderBook->currentTime = orderBook->getEarliestTime();
    orderBook->indexOfVectorWithMatchingTimestamps = 0;
}

void CommandProcessor::stepLatest(OrderBook *orderBook)
{
    orderBook->currentTime = orderBook->getLatestTime();
    orderBook->indexOfVectorWithMatchingTimestamps = orderBook->totalNumberOfTimesteps-1;
}

void CommandProcessor::jump(OrderBook* orderBook, std::vector<std::string> tokenVector)
{
    if(tokenVector.size() > 2)
    {
        std::cout << "\nerror: invalid number of arguments, expected 1 but received: " << tokenVector.size()-1 << "\n" << std::endl;
        return;
    }

    int index;
    try{ index = std::stoi(tokenVector[1]);}
    catch(std::exception &e)
    {
        std::cout << "\nerror: invalid argument, expected integer but got: " << tokenVector[1] << "\n" << std::endl;
        return;
    }

    if(index < 0 || index > orderBook->totalNumberOfTimesteps)
    {
        std::cout << "\nerror: invalid index, index cannot be less than 0 or greater than the total number of timesteps-1 which is: "
                  << orderBook->totalNumberOfTimesteps-1 << "\n" << std::endl;
        return;
    }

    //if above checks succeed, the input is validated
    orderBook->currentTime = orderBook->getTimestepAt(index);
    orderBook->indexOfVectorWithMatchingTimestamps = index;
}
