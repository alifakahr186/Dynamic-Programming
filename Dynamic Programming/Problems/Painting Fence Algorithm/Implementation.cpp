#include <iostream>
#include <vector>
#include <string>

int paintingfence(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    if (n == 2) return k + k * (k - 1);

    return paintingfence(n - 2, k) * (k - 1) + paintingfence(n - 1, k) * (k - 1);
}

int paintingfencememo(int n, int k, std::vector<int>& dp) {
    if (n == 0) return 0;
    if (n == 1) return k;
    if (n == 2) return k + k * (k - 1);

    if (dp[n] != -1) return dp[n];

    dp[n] = paintingfencememo(n - 2, k, dp) * (k - 1) + paintingfencememo(n - 1, k, dp) * (k - 1);
    return dp[n];
}

int paintingfencetable(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    if (n == 2) return k + k * (k - 1);

    std::vector<int> dp(n + 1, 0);
    dp[1] = k;
    dp[2] = k + k * (k - 1);

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 2] * (k - 1) + dp[i - 1] * (k - 1);
    }

    return dp[n];
}

int main() {
    int n = 4; // Number of posts
    int k = 3; // Number of colors

    // Using Recursion
    int result = paintingfence(n, k);
    std::cout << "We can paint the fence in " << result << " ways using recursion." << std::endl;

    // Using Memoization
    std::vector<int> dp(n + 1, -1);
    int resultmemo = paintingfencememo(n, k, dp);
    std::cout << "We can paint the fence in " << resultmemo << " ways using memoization." << std::endl;

    // Using Tabulation
    int resulttable = paintingfencetable(n, k);
    std::cout << "We can paint the fence in " << resulttable << " ways using tabulation." << std::endl;

    return 0;
}
