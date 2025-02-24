cmake_minimum_required(VERSION 3.10)
project(MarketMakerLatencyArbitrage)

set(CMAKE_CXX_STANDARD 17)

# Ensure vcpkg toolchain is set
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Find required packages
find_package(nlohmann_json CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread asio regex)
find_package(websocketpp CONFIG REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/market_data)
include_directories(${CMAKE_SOURCE_DIR}/src/order_book)
include_directories(${CMAKE_SOURCE_DIR}/src/strategy)
include_directories(${CMAKE_SOURCE_DIR}/third_party)
include_directories(${CMAKE_SOURCE_DIR}/vcpkg/installed/arm64-osx/include)

# Add OpenSSL include path manually if needed.
include_directories(/opt/homebrew/opt/openssl/include)

# Source files
set(SRC_FILES
    src/main.cpp
    src/market_data/websocket_client.cpp
    src/market_data/data_handler.cpp
    src/order_book/order_book.cpp
    src/strategy/market_maker.cpp
    src/strategy/latency_arbitrage.cpp
    src/execution/order_executor.cpp
    src/risk/risk_manager.cpp
    src/utils/logger.cpp
    src/profit_tracker/profit_tracker.cpp
)

# Define executable
add_executable(market_maker ${SRC_FILES})

# Link external libraries
target_link_libraries(market_maker PRIVATE
    nlohmann_json::nlohmann_json
    Boost::system
    Boost::thread
    Boost::asio
    Boost::regex
    OpenSSL::SSL
    OpenSSL::Crypto
)
