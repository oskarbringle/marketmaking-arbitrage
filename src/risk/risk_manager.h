#ifndef RISK_MANAGER_H
#define RISK_MANAGER_H

class RiskManager {
public:
    // maxPosition: maximum absolute position allowed.
    // stopLossThreshold: the adverse price movement (absolute difference) that triggers a stop-loss.
    RiskManager(double maxPosition, double stopLossThreshold);

    // Returns true if a new trade with the given quantity can be opened.
    bool canOpenPosition(double quantity) const;

    // Update the position when a trade is executed. For a BUY trade, quantity is positive; for SELL, negative.
    void updatePosition(double quantity, double price);

    // Check if the current position should be closed based on the current market price.
    bool shouldStopLoss(double currentPrice) const;

    // Reset the position (e.g., after closing out a position).
    void resetPosition();

    // Get the current position.
    double currentPosition() const;

private:
    double m_maxPosition;
    double m_stopLossThreshold;
    double m_currentPosition;
    double m_entryPrice; // price at which the current position was entered
};

#endif // RISK_MANAGER_H
