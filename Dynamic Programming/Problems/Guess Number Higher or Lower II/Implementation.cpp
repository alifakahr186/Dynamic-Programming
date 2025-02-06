#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int solve(int start, int end) {
        if (start >= end) return 0;
        int mini = INT_MAX;
        for (int i = start; i <= end; i++) {
            mini = std::min(mini, i + std::max(solve(start, i - 1), solve(i + 1, end)));
        }
        return mini;
    }

    int solveMemo(int start, int end, std::vector<std::vector<int>>& dp) {
        if (start >= end) return 0;
        if (dp[start][end] != -1) return dp[start][end];

        int mini = INT_MAX;
        for (int i = start; i <= end; i++) {
            mini = std::min(mini, i + std::max(solveMemo(start, i - 1, dp), solveMemo(i + 1, end, dp)));
        }
        return dp[start][end] = mini;
    }

    int solveTable(int n) {
        std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));

        for (int start = n - 1; start >= 1; start--) {
            for (int end = start + 1; end <= n; end++) {
                int mini = INT_MAX;
                for (int i = start; i <= end; i++) {
                    mini = std::min(mini, i + std::max(dp[start][i - 1], dp[i + 1][end]));
                }
                dp[start][end] = mini;
            }
        }
        return dp[1][n];
    }

    int getMoneyAmount(int n) {
        return solve(1, n);
    }
    
    int getMoneyAmountMemo(int n) {
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, -1));
        return solveMemo(1, n, dp);
    }

    int getMoneyAmountTable(int n) {
        return solveTable(n);
    }
};

int main() {
    Solution solution;
    int n = 22;

    // Using Recursion
    int resultRec = solution.getMoneyAmount(n);
    std::cout << "Get Money Amount Using Recursion: " << resultRec << std::endl;

    // Using Memoization
    int resultMemo = solution.getMoneyAmountMemo(n);
    std::cout << "Get Money Amount Using Memoization: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTab = solution.getMoneyAmountTable(n);
    std::cout << "Get Money Amount Using Tabulation: " << resultTab << std::endl;

    return 0;
}
