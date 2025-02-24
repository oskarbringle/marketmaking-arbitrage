#include "order_book.h"
#include <iostream>
#include <mutex>
#include <iomanip>

void OrderBook::update(double price, double quantity, bool is_bid) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& book = is_bid ? bids : asks;
    if (quantity == 0)
        book.erase(price);
    else
        book[price] = quantity;
}

void OrderBook::print() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Order Book:\nBids:\n";
    // bids are stored in ascending order so the best (highest) bid is at the end.
    for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
        std::cout << std::fixed << std::setprecision(8) << it->first << " : " << it->second << "\n";
    }
    std::cout << "Asks:\n";
    for (const auto& ask : asks) {
        std::cout << std::fixed << std::setprecision(8) << ask.first << " : " << ask.second << "\n";
    }
}

double OrderBook::getBestBid() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (bids.empty()) return 0.0;
    return bids.rbegin()->first;  // Highest bid
}

double OrderBook::getBestAsk() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (asks.empty()) return 0.0;
    return asks.begin()->first;  // Lowest ask
}
