#include <iostream>
#include <vector>

void coinchange(std::vector<std::vector<int>>& a, const std::vector<int>& coin, int w) {
    // Initialize base cases
    for (size_t i = 0; i < coin.size(); i++) {
        a[i][0] = 1;
    }
    
    // Calculate combinations
    for (size_t i = 0; i < coin.size(); ++i) {
        for (int j = 1; j <= w; ++j) {
            if (coin[i] > j) {
                a[i][j] = (i > 0) ? a[i-1][j] : 0;
            } else {
                a[i][j] = (i > 0 ? a[i-1][j] : 0) + a[i][j - coin[i]];
            }
        }
    }
}

int coinchangememo(const std::vector<int>& coin, int w, std::vector<int>& dp) {
    if (w == 0) return 1;
    if (w < 0) return 0;

    if (dp[w] != -1) return dp[w];

    int result = 0;

    for (size_t i = 0; i < coin.size(); ++i) {
        result += coinchangememo(coin, w - coin[i], dp);
    }

    dp[w] = result;
    return dp[w];
}

int coinchangetable(const std::vector<int>& coin, int w) {
    std::vector<int> dp(w + 1, 0);
    dp[0] = 1;

    for (size_t i = 0; i < coin.size(); ++i) {
        for (int j = coin[i]; j <= w; ++j) {
            dp[j] += dp[j - coin[i]];
        }
    }

    return dp[w];
}

int main() {
    std::vector<int> coin = {2, 3, 5, 10};
    int w = 15;
    int size = coin.size();
    
    //Using Recursion
    std::vector<std::vector<int>> a(size, std::vector<int>(w + 1, 0));
    coinchange(a, coin, w);
    std::cout << "Number of combinations: " << a[size - 1][w] << std::endl;

    //Using Memoization
    std::vector<int> dp = (w + 1, -1);
    int result = coinchangememo(a, coin, w, dp);
    std::cout << "Number of combinations using memoization: " << result << std::endl;

    //Using Table
    std::vector<int> dp = (w + 1, INT_MAX);
    int resulttabulation = coinchangetable(coin, w, dp);
    std::cout << "Number of combinations using tabulation: " << resulttabulation << std::endl;


    return 0;
}
