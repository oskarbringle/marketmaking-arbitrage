#include "risk_manager.h"
#include <cmath>
#include <iostream>

RiskManager::RiskManager(double maxPosition, double stopLossThreshold)
    : m_maxPosition(maxPosition), m_stopLossThreshold(stopLossThreshold),
      m_currentPosition(0.0), m_entryPrice(0.0) {}

bool RiskManager::canOpenPosition(double quantity) const {
    return (std::abs(m_currentPosition + quantity) <= m_maxPosition);
}

void RiskManager::updatePosition(double quantity, double price) {
    // If no open position, record the entry price.
    if (m_currentPosition == 0.0) {
        m_entryPrice = price;
    }
    m_currentPosition += quantity;
}

bool RiskManager::shouldStopLoss(double currentPrice) const {
    // For a long position, if the price falls too much below the entry price.
    if (m_currentPosition > 0) {
        return ((m_entryPrice - currentPrice) >= m_stopLossThreshold);
    }
    // For a short position, if the price rises too much above the entry price.
    else if (m_currentPosition < 0) {
        return ((currentPrice - m_entryPrice) >= m_stopLossThreshold);
    }
    return false;
}

void RiskManager::resetPosition() {
    m_currentPosition = 0.0;
    m_entryPrice = 0.0;
}

double RiskManager::currentPosition() const {
    return m_currentPosition;
}
