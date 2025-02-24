#include "market_maker.h"
#include <iostream>
#include <thread>
#include <chrono>

MarketMaker::MarketMaker(OrderBook& orderBook, double minSpread)
    : m_orderBook(orderBook), m_minSpread(minSpread) {}

void MarketMaker::run() {
    while (true) {
        double bestBid = m_orderBook.getBestBid();
        double bestAsk = m_orderBook.getBestAsk();
        if (bestBid == 0 || bestAsk == 0) {
            // Skip processing if order book data is not available.
            continue;
        }

        double spread = bestAsk - bestBid;

        // Print the current order book snapshot for strategy debugging.
        std::cout << "\n[MarketMaker] Best Bid: " << bestBid
                  << ", Best Ask: " << bestAsk
                  << ", Spread: " << spread << std::endl;

        if (spread > m_minSpread) {
            std::cout << "[MarketMaker] Spread (" << spread 
                      << ") exceeds threshold (" << m_minSpread << "). Consider placing orders..." << std::endl;
            // Here you would integrate with your order executor to place orders.
        }

        // Wait a bit before checking again.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
