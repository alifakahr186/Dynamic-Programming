#include <iostream>
#include <vector>
#include <algorithm>

int knapsack(std::vector<std::vector<int>>& a, const std::vector<int>& weight, const std::vector<int>& profit, int maxWeight, int itemCount) {

    for (int i = 1; i <= itemCount; i++) {
        for (int j = 1; j <= maxWeight; j++) {
            if (weight[i-1] <= j) {
                a[i][j] = std::max(a[i-1][j], a[i-1][j - weight[i-1]] + profit[i-1]);
            } else {
                a[i][j] = a[i-1][j];
            }
        }
    }

    return a[itemCount][maxWeight];
}

int knapsackMemo(const std::vector<int>& weight, const std::vector<int>& profit, int maxWeight, int itemCount, std::vector<int>& dp) {
    if (itemCount == 0 || maxWeight == 0) {
        return 0;
    }

    if (dp[itemCount][maxWeight] != -1) {
        return dp[itemCount][maxWeight];
    }

    if (weight[itemCount-1] <= maxWeight) {
        dp[itemCount][maxWeight] = std::max(
            profit[itemCount-1] + knapsackMemo(weight, profit, maxWeight - weight[itemCount-1], itemCount-1, dp),
            knapsackMemo(weight, profit, maxWeight, itemCount-1, dp)
        );
    } 

    else {
        dp[itemCount][maxWeight] = knapsackMemo(weight, profit, maxWeight, itemCount-1, dp);
    }

    return dp[itemCount][maxWeight];

}

int knapsackTable(const std::vector<int>& weight, const std::vector<int>& profit, int maxWeight, int itemCount) {
    std::vector<int> dp(maxWeight + 1, 0);
    for (int i = 0; i < itemCount; i++) {
        for (int j = maxWeight; j >= weight[i]; j--) {
            dp[j] = std::max(dp[j], dp[j - weight[i]] + profit[i]);
        }
    }
    return dp[maxWeight];
}

int main() {
    std::vector<int> weight = {3, 4, 6, 5};
    std::vector<int> profit = {2, 3, 1, 4};

    int maxWeight = 8;
    int itemCount = weight.size();
    // Create a 2D DP array
    std::vector<std::vector<int>> a(itemCount + 1, std::vector<int>(maxWeight + 1, 0));

    //Using Recursion
    int result = knapsack(a, weight, profit, maxWeight, itemCount);
    std::cout << "Maximum profit Using Recursion: " << result << std::endl;

    //Using Memoization
    std::vector<std::vector<int>> dp(itemCount + 1, std::vector<int>(maxWeight + 1, -1));
    int resultMemo = knapsackMemo(weight, profit, maxWeight, itemCount, dp);
    std::cout << "Maximum profit Using Memoization: " << resultMemo << std::endl;

    //Using Tabulation
    int resultTable = knapsackTable(weight, profit, maxWeight, itemCount);
    std::cout << "Maximum profit Using Tabulation: " << resultTable << std::endl;

    return 0;
}
