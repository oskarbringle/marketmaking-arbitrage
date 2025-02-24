#include "latency_arbitrage.h"
#include "../execution/order_executor.h"
#include <iostream>

LatencyArbitrage::LatencyArbitrage(const OrderBook& exchange1, const OrderBook& exchange2, double tradeQuantity)
    : m_exchange1(exchange1), m_exchange2(exchange2), m_tradeQuantity(tradeQuantity) {}

void LatencyArbitrage::checkArbitrage() {
    // Assume m_exchange1 is Binance and m_exchange2 is Coinbase.
    double binanceBid = m_exchange1.getBestBid();  // Highest bid on Binance
    double coinbaseAsk = m_exchange2.getBestAsk();   // Lowest ask on Coinbase

    // Check if there is an arbitrage opportunity.
    if (binanceBid > coinbaseAsk && binanceBid > 0 && coinbaseAsk > 0) {
        std::cout << "\nArbitrage Opportunity Detected:" << std::endl;
        std::cout << "  Buy on Coinbase at " << coinbaseAsk << std::endl;
        std::cout << "  Sell on Binance at " << binanceBid << std::endl;

        // Execute simulated trades.
        execute_trade("COINBASE", "BUY", coinbaseAsk, m_tradeQuantity);
        execute_trade("BINANCE", "SELL", binanceBid, m_tradeQuantity);
    }
}
