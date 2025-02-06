#include <iostream>
#include <vector>
#include <climits> // For INT_MAX

void coinChange(std::vector<std::vector<int>>& a, const std::vector<int>& coins, int w) {
    // Initialize base cases
    for (size_t i = 0; i < coins.size(); i++) {
        a[i][0] = 0; 
    }
    
    for (size_t i = 0; i < coins.size(); ++i) {
        for (int j = 1; j <= w; ++j) {
            if (coins[i] > j) {
                a[i][j] = (i > 0) ? a[i-1][j] : INT_MAX;
            } else {
                if (i > 0) {
                    a[i][j] = std::min(a[i-1][j], 1 + a[i][j - coins[i]]);
                } else {
                    a[i][j] = (j % coins[i] == 0) ? j / coins[i] : INT_MAX;
                }
            }
        }
    }
}

int coinChangeMemo(const std::vector<int>& coins, int w, std::vector<int>& dp) {
    // Base cases
    if (w == 0) return 0;
    if (w < 0) return INT_MAX;
    
    if (dp[w] != -1) return dp[w];
    
    // Compute the minimum coins needed
    int minCoins = INT_MAX;

    for (size_t i = 0; i < coins.size(); ++i) {
        int coin = coins[i];
        int result = coinChangeMemo(coins, w - coin, dp);
        if (result != INT_MAX) {
            minCoins = std::min(minCoins, result + 1);
        }
    }
    
    dp[w] = minCoins;
    return dp[w];
}

int coinChangeTable(const std::vector<int>& coins, int w) {
    std::vector<int> dp(w + 1, INT_MAX);
    dp[0] = 0;

    for (size_t i = 0; i < coins.size(); ++i) {
        for (int j = coins[i]; j <= w; ++j) {
            if (dp[j - coins[i]] != INT_MAX) {
                dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);
            }
        }
    }

    return dp[w];
}

int main() {
    std::vector<int> coins = {1, 5, 6, 9};
    int w = 10;
    int size = coins.size(); 
    
    // Initialize a 2D array to store intermediate results with INT_MAX
    std::vector<std::vector<int>> a(size, std::vector<int>(w + 1, INT_MAX));

    //Using Recursion
    coinChange(a, coins, w);
    int result = a[size - 1][w];

    if (result == INT_MAX) {
        std::cout << "It is not possible to make the amount " << w << " with the given coins." << std::endl;
    } else {
        std::cout << "Minimum number of coins required: " << result << std::endl;
    }

    //Using Memoization
    std::vector<int> dp(w + 1, -1);
    int ans = coinChangeMemo(coins, w, dp);

    if (ans == INT_MAX) {
        std::cout << "It is not possible to make the amount " << w << " with the given coins using memoization." << std::endl;
    } else {
        std::cout << "Minimum number of coins required using memoization: " << ans << std::endl;
    }

    //Using Tabulation
    int ansTabulation = coinChangeTable(coins, w);

    if (ansTabulation == INT_MAX) {
        std::cout << "It is not possible to make the amount " << w << " with the given coins using tabulation." << std::endl;
    } else {
        std::cout << "Minimum number of coins required using tabulation: " << ansTabulation << std::endl;
    }

    return 0;
}
