#include <iostream>
#include <thread>
#include "order_book/order_book.h"
#include "strategy/latency_arbitrage.h"
#include "profit_tracker/profit_tracker.h"

// Simulate order book updates with fluctuating prices.
void simulateOrderBookUpdates(OrderBook& ob, double& bid, double& ask) {
    // Update with current prices (simulate a slight random fluctuation)
    ob.update(bid, 10.0, true);
    ob.update(ask, 10.0, false);

    // Simulate small fluctuations.
    bid += (rand() % 10 - 5) * 0.1;
    ask += (rand() % 10 - 5) * 0.1;
}

int main() {
    // Create two order books for two different exchanges.
    OrderBook binanceOrderBook;  // For Binance
    OrderBook coinbaseOrderBook; // For Coinbase

    // Initial prices for simulation.
    double binanceBid = 95800.0, binanceAsk = 95850.0;
    double coinbaseBid = 95750.0, coinbaseAsk = 95725.0; // Coinbase's best ask is lower

    // Create the arbitrage module with a trade quantity (e.g., 1 unit).
    LatencyArbitrage arbitrage(binanceOrderBook, coinbaseOrderBook, 1.0);

    // Launch simulation threads for both order books.
    std::thread binanceSim([&]() {
        while (true) {
            simulateOrderBookUpdates(binanceOrderBook, binanceBid, binanceAsk);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    std::thread coinbaseSim([&]() {
        while (true) {
            simulateOrderBookUpdates(coinbaseOrderBook, coinbaseBid, coinbaseAsk);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    // Run the arbitrage check periodically.
    std::thread arbitrageThread([&]() {
        while (true) {
            arbitrage.checkArbitrage();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    // Additionally, print the profit summary every few seconds.
    std::thread profitThread([]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            g_profitTracker.printSummary();
            std::cout << "Total Profit: " << g_profitTracker.totalProfit() << std::endl;
        }
    });


    // Join threads.
    binanceSim.join();
    coinbaseSim.join();
    arbitrageThread.join();
    profitThread.join();

    return 0;
}
