#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    // Recursive approach (not memoized)
    int solve(int index, int operationNo, int k, std::vector<int>& prices) {
        if (index == prices.size()) return 0;
        if (operationNo == 2*k) return 0;    

        int profit = 0;  

        if (operationNo % 2 == 0) {
            // Buy operation
            int buy = -prices[index] + solve(index + 1, operationNo + 1, k, prices);
            int skip = solve(index + 1, operationNo, k, prices);
            profit = std::max(buy, skip);
        } else {
            // Sell operation
            int sell = prices[index] + solve(index + 1, operationNo + 1, k, prices);
            int skip = solve(index + 1, operationNo, k, prices);
            profit = std::max(sell, skip);
        }
        return profit;
    }

    // Recursive + Memoization approach
    int solveMemo(int index, int operationNo, int k, std::vector<int>& prices, std::vector<std::vector<int>>& dp) {
        if (index == prices.size()) return 0; // Base case: no more prices to process
        if (operationNo == 2*k) return 0;     // Base case: max operations reached
        if (dp[index][operationNo] != -1) return dp[index][operationNo]; // Memoization check

        int profit = 0;  

        if (operationNo % 2 == 0) {
            // Buy operation
            int buy = -prices[index] + solveMemo(index + 1, operationNo + 1, k, prices, dp);
            int skip = solveMemo(index + 1, operationNo, k, prices, dp);
            profit = std::max(buy, skip);
        } else {
            // Sell operation
            int sell = prices[index] + solveMemo(index + 1, operationNo + 1, k, prices, dp);
            int skip = solveMemo(index + 1, operationNo, k, prices, dp);
            profit = std::max(sell, skip);
        }

        // Memoize the result
        return dp[index][operationNo] = profit;
    }

    // Tabulation (bottom-up DP) approach with space optimization
    int solveTable(int k, std::vector<int>& prices) {
        int n = prices.size();
        std::vector<int> curr(2*k + 1, 0);  // Current row
        std::vector<int> next(2*k + 1, 0);  // Next row

        // Bottom-up calculation
        for (int index = n - 1; index >= 0; index--) {
            for (int operationNo = 0; operationNo < 2*k; operationNo++) {
                int profit = 0;
                if (operationNo % 2 == 0) { // Buy operation
                    int buy = -prices[index] + next[operationNo + 1];
                    int skip = next[operationNo];
                    profit = std::max(buy, skip);
                } else { // Sell operation
                    int sell = prices[index] + next[operationNo + 1];
                    int skip = next[operationNo];
                    profit = std::max(sell, skip);
                }
                curr[operationNo] = profit;
            }
            next = curr;  // Move current row to next row for the next iteration
        }

        return next[0];  // Return the profit when starting with no operations
    }

    // Main function to calculate maximum profit
    int maxProfit(int k, std::vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        //Use Recursion approach
        //return solve(0, 0, k, prices);
        
        // Use memoization approach
        std::vector<std::vector<int>> dp(n, std::vector<int>(2*k + 1, -1));
        return solveMemo(0, 0, k, prices, dp);

        // Alternatively, you could use the tabulation approach:
        // return solveTable(k, prices);
    }
};

int main() {
    Solution sol;
    std::vector<int> prices = {52, 53, 28, 10, 9, 15, 5};
    int k = 2;  // Max number of transactions

    int max_profit = sol.maxProfit(k, prices);
    std::cout << "Max Profit: " << max_profit << std::endl;

    return 0;
}
