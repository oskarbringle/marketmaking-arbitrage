#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <string>
#include "../order_book/order_book.h"

// Handles parsing of exchange data and updating the order book.
class DataHandler {
public:
    // Takes a reference to an order book that will be updated.
    DataHandler(OrderBook& orderBook);
    
    // Process an incoming raw JSON message.
    void processMessage(const std::string& message);

private:
    OrderBook& m_orderBook;
};

#endif // DATA_HANDLER_H
