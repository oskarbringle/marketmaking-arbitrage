#ifndef PROFIT_TRACKER_H
#define PROFIT_TRACKER_H

#include <mutex>
#include <vector>
#include <string>

struct Trade {
    std::string exchange;
    std::string side;
    double price;
    double quantity;
    long latency_us;
};

class ProfitTracker {
public:
    void recordTrade(const Trade& trade);
    double totalProfit() const;
    void printSummary() const;

private:
    mutable std::mutex mtx;
    std::vector<Trade> tradeLog;
};

extern ProfitTracker g_profitTracker;

#endif // PROFIT_TRACKER_H
