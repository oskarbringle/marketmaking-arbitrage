#include "websocket_client.h"
#include <iostream>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>
#include <boost/asio/ssl/context.hpp>
#include <nlohmann/json.hpp>
#include "order_book/order_book.h"



using client = websocketpp::client<websocketpp::config::asio_tls_client>;

WebSocketClient::WebSocketClient(const std::string& uri) : m_uri(uri) {
    // Initialize the ASIO transport.
    m_client.init_asio();

    // Setup TLS initialization for secure WebSocket connections.
    m_client.set_tls_init_handler([](websocketpp::connection_hdl) {
        auto ctx = websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);
        try {
            ctx->set_options(boost::asio::ssl::context::default_workarounds |
                             boost::asio::ssl::context::no_sslv2 |
                             boost::asio::ssl::context::no_sslv3 |
                             boost::asio::ssl::context::single_dh_use);
        } catch (std::exception& e) {
            std::cout << "TLS initialization error: " << e.what() << std::endl;
        }
        return ctx;
    });

    // Bind the internal onMessage callback.
    m_client.set_message_handler([this](websocketpp::connection_hdl hdl, client::message_ptr msg) {
        this->onMessage(hdl, msg);
    });
}

WebSocketClient::~WebSocketClient() {
    // Add any necessary cleanup here.
}

void WebSocketClient::setMessageHandler(MessageHandler handler) {
    m_messageHandler = handler;
}

void WebSocketClient::connect() {
    websocketpp::lib::error_code ec;
    auto con = m_client.get_connection(m_uri, ec);
    if (ec) {
        std::cout << "Connection error: " << ec.message() << std::endl;
        return;
    }
    m_hdl = con->get_handle();
    m_client.connect(con);
}

void WebSocketClient::run() {
    // Run the client event loop (this will block).
    m_client.run();
}

// OrderBook orderBook;

void WebSocketClient::onMessage(websocketpp::connection_hdl hdl, client::message_ptr msg) {
    std::string payload = msg->get_payload();

    // ✅ Print the raw message to debug
    std::cout << "Raw WebSocket Data: " << payload << std::endl;

    try {
        auto json_data = nlohmann::json::parse(payload);

        // ✅ Ensure that "bids" and "asks" exist and are not empty
        if (json_data.contains("bids") && json_data.contains("asks") &&
            !json_data["bids"].empty() && !json_data["asks"].empty()) {

            // ✅ Extract the best bid (highest bid price)
            double bestBid = std::stod(json_data["bids"][0][0].get<std::string>());

            // ✅ Extract the best ask (lowest ask price)
            double bestAsk = std::stod(json_data["asks"][0][0].get<std::string>());

            // ✅ Calculate the spread
            double spread = bestAsk - bestBid;

            // ✅ Display the spread in a clean format
            std::cout << "\n====================" << std::endl;
            std::cout << " Best Bid: " << bestBid << std::endl;
            std::cout << " Best Ask: " << bestAsk << std::endl;
            std::cout << " Spread  : " << spread << std::endl;
            std::cout << "====================\n" << std::endl;
        } else {
            std::cout << "No depth data received..." << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << "Error parsing JSON: " << e.what() << std::endl;
    }
}
