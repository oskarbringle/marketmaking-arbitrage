#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <mutex>
#include <iostream>

class OrderBook {
public:
    // Update the order book: if quantity is 0, remove the level; otherwise, update it.
    void update(double price, double quantity, bool is_bid);

    // Print the entire order book (for debugging).
    void print();

    // Get the best (highest) bid price.
    double getBestBid() const;

    // Get the best (lowest) ask price.
    double getBestAsk() const;

private:
    std::map<double, double> bids;  // Sorted ascending by price (so best bid is last)
    std::map<double, double> asks;  // Sorted ascending by price (so best ask is first)
    mutable std::mutex mtx;         // Protects access to bids and asks
};

#endif // ORDER_BOOK_H
