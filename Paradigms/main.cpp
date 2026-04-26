#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<int> coins = {1, 3, 11, 21};

int calc_change_bottom_up(int amount, vector<int>& usedCoins) {
    vector<int> dp(amount + 1, INT_MAX / 2);
    vector<int> previousCoin(amount + 1, -1);

    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] + 1 < dp[i]) {
                dp[i] = dp[i - coin] + 1;
                previousCoin[i] = coin;
            }
        }
    }

    int current = amount;
    while (current > 0) {
        usedCoins.push_back(previousCoin[current]);
        current -= previousCoin[current];
    }

    return dp[amount];
}

int main() {
    vector<int> testAmounts = {124, 226, 121};

    for (int amount : testAmounts) {
        vector<int> usedCoins;

        int minCoins = calc_change_bottom_up(amount, usedCoins);

        cout << amount << endl;
        cout << minCoins << endl;
        cout << endl << endl;
    }

    return 0;
}