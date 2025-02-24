#ifndef MARKET_MAKER_H
#define MARKET_MAKER_H

#include "../order_book/order_book.h"

class MarketMaker {
public:
    // Construct with a reference to the shared order book and a minimum spread threshold.
    MarketMaker(OrderBook& orderBook, double minSpread);

    // Run the market-making loop.
    void run();

private:
    OrderBook& m_orderBook;
    double m_minSpread; // Example threshold: only act if the spread exceeds this value.
};

#endif // MARKET_MAKER_H
