#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
        /** construct, reading a csv data file */
        OrderBook(std::string filename);
        /** return vector of all know products in the dataset*/
        std::vector<std::string> getKnownProducts();
        /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

        /** returns the earliest time in the orderbook*/
        std::string getEarliestTime();
        std::string getLatestTime(); //my own function
        /** returns the next time after the sent time in the orderbook * */
        std::string getNextTime(std::string timestamp);
        /** returns the previous time before the sent time in the orderbook * */
        std::string getPreviousTime(std::string timestamp);
        std::string getTimestepAt(int index);

        void insertOrder(OrderBookEntry& order);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

        // currentTime is set by default to the latest time
        std::string currentTime;
        int indexOfVectorWithMatchingTimestamps;
        int totalNumberOfTimesteps;

    private:
        std::vector<OrderBookEntry> orders;
        std::vector<std::vector<OrderBookEntry>> ordersSeparatedByTimestamps;
};
