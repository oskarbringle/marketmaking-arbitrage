#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <boost/asio/ssl/context.hpp>
#include <functional>
#include <string>

using client = websocketpp::client<websocketpp::config::asio_tls_client>;

class WebSocketClient {
public:
    using MessageHandler = std::function<void(const std::string&)>;

    explicit WebSocketClient(const std::string& uri);
    ~WebSocketClient();

    void connect();
    void run();
    void setMessageHandler(MessageHandler handler);

private:
    void onMessage(websocketpp::connection_hdl hdl, client::message_ptr msg);

    std::string m_uri;
    client m_client;
    websocketpp::connection_hdl m_hdl;
    MessageHandler m_messageHandler;
};

#endif // WEBSOCKET_CLIENT_H
