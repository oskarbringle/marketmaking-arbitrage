#include "data_handler.h"
#include <iostream>
#include <nlohmann/json.hpp>

// For convenience.
using json = nlohmann::json;

DataHandler::DataHandler(OrderBook& orderBook) : m_orderBook(orderBook) {}

void DataHandler::processMessage(const std::string& message) {
    try {
        // Parse the JSON message.
        auto j = json::parse(message);
        
        // Expecting JSON format with "bids" and "asks" arrays.
        // Each bid/ask is an array: [price, quantity].
        if (j.contains("bids") && j.contains("asks")) {
            // Process bids.
            for (auto& bid : j["bids"]) {
                double price = std::stod(bid[0].get<std::string>());
                double quantity = std::stod(bid[1].get<std::string>());
                m_orderBook.update(price, quantity, true);
            }
            // Process asks.
            for (auto& ask : j["asks"]) {
                double price = std::stod(ask[0].get<std::string>());
                double quantity = std::stod(ask[1].get<std::string>());
                m_orderBook.update(price, quantity, false);
            }
            // Optionally, print the order book snapshot for debugging.
            // m_orderBook.print();
        }
    } catch (std::exception& e) {
        std::cerr << "Error processing message: " << e.what() << std::endl;
    }
}
