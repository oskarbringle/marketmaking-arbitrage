#ifndef LATENCY_ARBITRAGE_H
#define LATENCY_ARBITRAGE_H

#include "../order_book/order_book.h"

class LatencyArbitrage {
public:
    // Construct with references to two order books.
    LatencyArbitrage(const OrderBook& exchange1, const OrderBook& exchange2, double tradeQuantity);

    // Check for arbitrage opportunities and execute trades if found.
    void checkArbitrage();

private:
    const OrderBook& m_exchange1;  // e.g., Binance
    const OrderBook& m_exchange2;  // e.g., Coinbase
    double m_tradeQuantity;
};

#endif // LATENCY_ARBITRAGE_H
