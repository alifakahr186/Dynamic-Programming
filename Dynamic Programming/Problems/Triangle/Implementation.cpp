#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // for INT_MAX

class Solution {
public:
    // Recursive function
    int minimumTotal(std::vector<std::vector<int>>& triangle, int row, int col) {
        if (row == triangle.size() - 1) return triangle[row][col];

        int left = minimumTotal(triangle, row + 1, col);
        int right = minimumTotal(triangle, row + 1, col + 1);

        return triangle[row][col] + std::min(left, right);
    }

    // Memoization function
    int minimumTotalMemo(std::vector<std::vector<int>>& triangle, int row, int col, std::vector<std::vector<int>>& dp) {
        if (row == triangle.size() - 1) return triangle[row][col];

        if (dp[row][col] != -1) return dp[row][col];

        int left = minimumTotalMemo(triangle, row + 1, col, dp);
        int right = minimumTotalMemo(triangle, row + 1, col + 1, dp);

        dp[row][col] = triangle[row][col] + std::min(left, right);
        return dp[row][col];
    }

    // Tabulation function (Bottom-up DP)
    int minimumTotalTable(std::vector<std::vector<int>>& triangle) {
        int n = triangle.size();
        std::vector<std::vector<int>> dp = triangle; // Start with the same triangle structure

        // Process from bottom to top
        for (int row = n - 2; row >= 0; --row) {
            for (int col = 0; col < triangle[row].size(); ++col) {
                dp[row][col] += std::min(dp[row + 1][col], dp[row + 1][col + 1]);
            }
        }

        return dp[0][0]; // The top of the triangle will have the minimum path sum
    }
};

int main() {
    // Initialize the triangle as a vector of vectors
    std::vector<std::vector<int>> triangle = { {2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3} };
    
    Solution solution;

    // Using Recursion
    int resultRecursion = solution.minimumTotal(triangle, 0, 0);
    std::cout << "Minimum path sum using recursion: " << resultRecursion << std::endl;

    // Using Memoization
    int n = triangle.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
    int resultMemo = solution.minimumTotalMemo(triangle, 0, 0, dp);
    std::cout << "Minimum path sum using memoization: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTabulation = solution.minimumTotalTable(triangle);
    std::cout << "Minimum path sum using tabulation: " << resultTabulation << std::endl;

    return 0;
}
