#include "order_executor.h"
#include "../profit_tracker/profit_tracker.h"
#include <iostream>
#include <chrono>
#include <thread>

// Global profit tracker instance (in a production system, manage this more elegantly)
extern ProfitTracker g_profitTracker;

void execute_trade(const std::string& exchange, const std::string& side, double price, double quantity) {
    // Simulate microsecond-level latency.
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::microseconds(50)); // simulate delay
    auto end = std::chrono::high_resolution_clock::now();
    long latency = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Executed " << side << " order on " << exchange 
              << " at price " << price << " with latency " 
              << latency << " µs." << std::endl;
              
    // Record the trade in the profit tracker.
    Trade trade;
    trade.exchange = exchange;
    trade.side = side;
    trade.price = price;
    trade.quantity = quantity;
    trade.latency_us = latency;
    
    g_profitTracker.recordTrade(trade);
}
