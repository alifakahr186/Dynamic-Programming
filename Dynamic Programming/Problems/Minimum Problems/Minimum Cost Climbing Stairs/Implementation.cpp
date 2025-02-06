#include <iostream>
#include <vector>
#include <algorithm> 

int ClimbingStairs(const std::vector<int>& cost, int size) {

    if (size == 0) {
        return 0; 
    }

    if (size == 1) {
        return cost[0]; 
    }

    std::vector<int> minCost(size);
    minCost[0] = cost[0];
    minCost[1] = cost[1];

    for (int i = 2; i < size; ++i) {
        minCost[i] = cost[i] + std::min(minCost[i - 1], minCost[i - 2]);
    }

    return std::min(minCost[size - 1], minCost[size - 2]);
}

int ClimbingStairsMemo(const std::vector<int>& cost, int size, std::vector<int>& dp) {
    if (size <= 1) {
        return 0;
    }

    if (dp[size] != -1) {
        return dp[size];
    }

    dp[size] = std::min(cost[size - 1] + ClimbingStairsMemo(cost, size - 1, dp), 
                        cost[size - 2] + ClimbingStairsMemo(cost, size - 2, dp));

    return dp[size];
}


int ClimbingStairsTable(const std::vector<int>& cost, int size) {
    if (size == 0) {
        return 0;
    }

    if (size == 1) {
        return cost[0];
    }

    std::vector<int> dp(size);
    dp[0] = cost[0];
    dp[1] = cost[1];

    for (int i = 2; i < size; ++i) {
        dp[i] = cost[i] + std::min(dp[i - 1], dp[i - 2]);
    }

    return std::min(dp[size - 1], dp[size - 2]);
}


int main() {
    std::vector<int> cost = {10, 15, 20, 25, 30, 35};
    int size = cost.size();

    // Using Recursion (tabulation approach)
    int result = ClimbingStairs(cost, size);
    std::cout << "Minimum cost to climb stairs: " << result << std::endl;

    // Using Memoization
    std::vector<int> dp(size + 1, -1);
    int ans = ClimbingStairsMemo(cost, size, dp);
    std::cout << "Minimum cost to climb stairs through Memoization: " << ans << std::endl;

    // Using Tabulation
    int resultTabulation = ClimbingStairsTable(cost, size);
    std::cout << "Minimum cost to climb stairs through Tabulation: " << resultTabulation << std::endl;

    return 0;
}

