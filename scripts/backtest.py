import json
import pandas as pd
import matplotlib.pyplot as plt

def backtest(filename, initial_balance=100000):
    # Load historical data from a JSON file (assumed to be a list of snapshots)
    with open(filename, 'r') as f:
        data = json.load(f)

    balance = initial_balance
    position = 0
    entry_price = None
    trades = []

    # For simplicity, assume each snapshot is a dictionary with keys:
    # 'bids': list of [price, quantity] and 'asks': list of [price, quantity]
    for snapshot in data:
        bids = snapshot.get('bids', [])
        asks = snapshot.get('asks', [])
        if not bids or not asks:
            continue

        best_bid = float(bids[0][0])
        best_ask = float(asks[0][0])
        spread = best_bid - best_ask

        # Example strategy: if spread is positive (arbitrage opportunity) and no open position, buy at ask and sell at bid.
        if spread > 0 and position == 0:
            position = 1  # open a long position (simulate arbitrage)
            entry_price = best_ask
            trades.append({'action': 'buy', 'price': best_ask})
        elif position == 1 and (best_bid - entry_price) > 30:  # threshold for closing the trade
            profit = best_bid - entry_price
            balance += profit
            trades.append({'action': 'sell', 'price': best_bid, 'profit': profit})
            position = 0
            entry_price = None

    print("Final Balance:", balance)
    print("Trades:")
    for trade in trades:
        print(trade)

    # Plot profits per trade if available.
    profits = [t.get('profit', 0) for t in trades if t['action'] == 'sell']
    if profits:
        plt.plot(profits, marker='o')
        plt.title("Profit per Trade")
        plt.xlabel("Trade Number")
        plt.ylabel("Profit")
        plt.show()
    else:
        print("No trades executed in backtest.")

if __name__ == "__main__":
    # Provide the path to your historical data JSON file
    backtest("historical_data.json")
