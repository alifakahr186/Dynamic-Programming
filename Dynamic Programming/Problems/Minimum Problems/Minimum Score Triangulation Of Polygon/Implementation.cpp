#include <iostream>
#include <vector>
#include <climits>
#include <limits>

int polygon(std::vector<int>& values, int i, int j) {
    if (i + 1 == j) {
        return 0;
    }

    int ans = INT_MAX;
    for (int k = i + 1; k < j; k++) {
        ans = std::min(ans, values[i] * values[j] * values[k] + polygon(values, i, k) + polygon(values, k, j));
    }
    return ans;
}

int polygonMemo(std::vector<int>& values, int i, int j, std::vector<std::vector<int>>& dp) {
    if (i + 1 == j) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    
    int ans = INT_MAX;
    for (int k = i + 1; k < j; k++) {
        ans = std::min(ans, values[i] * values[j] * values[k] + polygonMemo(values, i, k, dp) + polygonMemo(values, k, j, dp));
    }
    dp[i][j] = ans;
    return dp[i][j];
}

int polygonTable(std::vector<int>& values) {
    int n = values.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    for (int len = 2; len < n; len++) {
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = std::min(dp[i][j], values[i] * values[j] * values[k] + dp[i][k] + dp[k][j]);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    std::vector<int> values = {1, 2, 3, 4, 5};
    int n = values.size();

    // Using Recursion
    int resultRec = polygon(values, 0, n - 1);
    std::cout << "Minimum Score Triangulation Of Polygon Using Recursion: " << resultRec << std::endl;

    // Using Memoization
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
    int resultMemo = polygonMemo(values, 0, n - 1, dp);
    std::cout << "Minimum Score Triangulation Of Polygon Using Memoization: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTable = polygonTable(values);
    std::cout << "Minimum Score Triangulation Of Polygon Using Tabulation: " << resultTable << std::endl;

    return 0;
}
