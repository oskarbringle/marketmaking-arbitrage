#include "profit_tracker.h"
#include <iostream>
#include <iomanip>

ProfitTracker g_profitTracker;  // ✅ Definition of global instance

void ProfitTracker::recordTrade(const Trade& trade) {
    std::lock_guard<std::mutex> lock(mtx);
    tradeLog.push_back(trade);
}

double ProfitTracker::totalProfit() const {
    std::lock_guard<std::mutex> lock(mtx);
    double profit = 0.0;
    
    for (const auto& trade : tradeLog) {
        if (trade.side == "BUY") {
            profit -= trade.price * trade.quantity;
        } else if (trade.side == "SELL") {
            profit += trade.price * trade.quantity;
        }
    }
    return profit;
}

void ProfitTracker::printSummary() const {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "----- Profit Tracker Summary -----\n";
    std::cout << "Total Trades: " << tradeLog.size() << "\n";
    }
