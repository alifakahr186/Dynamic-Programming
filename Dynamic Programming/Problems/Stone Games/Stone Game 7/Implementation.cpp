#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int solve(vector<int>& stones, bool turn, int total_sum, int i, int j) {
        if (i > j) return 0; // Base case: no stones left to pick

        if (turn == 1) { // Player 1 (maximizing score)
            int x = total_sum - stones[i];
            int res1 = solve(stones, 1 - turn, x, i + 1, j) + x;
            int y = total_sum - stones[j];
            int res2 = solve(stones, 1 - turn, y, i, j - 1) + y;
            return max(res1, res2);
        } else { // Player 2 (minimizing score)
            int x = total_sum - stones[i];
            int res1 = solve(stones, 1 - turn, x, i + 1, j) - x;
            int y = total_sum - stones[j];
            int res2 = solve(stones, 1 - turn, y, i, j - 1) - y;
            return min(res1, res2);
        }
    }

    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        int total_sum = 0;

        for (int stone : stones) {
            total_sum += stone;
        }

        return solve(stones, 1, total_sum, 0, n - 1);
    }

    int solveMemo(vector<int>& stones, bool turn, int total_sum, int i, int j, vector<vector<vector<int>>>& dp) {
        if (i > j) return 0; // Base case: no stones left to pick

        if (dp[turn][i][j] != -1) return dp[turn][i][j]; // Return cached result

        if (turn == 1) { // Player 1 (maximizing score)
            int x = total_sum - stones[i];
            int res1 = solveMemo(stones, 1 - turn, x, i + 1, j, dp) + x;
            int y = total_sum - stones[j];
            int res2 = solveMemo(stones, 1 - turn, y, i, j - 1, dp) + y;
            return dp[turn][i][j] = max(res1, res2);
        } else { // Player 2 (minimizing score)
            int x = total_sum - stones[i];
            int res1 = solveMemo(stones, 1 - turn, x, i + 1, j, dp) - x;
            int y = total_sum - stones[j];
            int res2 = solveMemo(stones, 1 - turn, y, i, j - 1, dp) - y;
            return dp[turn][i][j] = min(res1, res2);
        }
    }

    int stoneGameVIIMemo(vector<int>& stones) {
        int n = stones.size();
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(n, vector<int>(n, -1)));
        int total_sum = 0;

        for (int stone : stones) {
            total_sum += stone;
        }

        return solveMemo(stones, 1, total_sum, 0, n - 1, dp);
    }

    int stoneGameVIITable(vector<int>& stones) {
        int n = stones.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        vector<int> prefixSum(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + stones[i];
        }

        for (int len = 2; len <= n; len++) { // Iterate over subarray lengths
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                int total_sum = prefixSum[j + 1] - prefixSum[i];

                int pickLeft = total_sum - stones[i] - dp[i + 1][j];
                int pickRight = total_sum - stones[j] - dp[i][j - 1];

                dp[i][j] = max(pickLeft, pickRight);
            }
        }
        return dp[0][n - 1];
    }

};

int main() {
    Solution sol;

    vector<int> stones = {5, 3, 1, 4, 2};

    // Using Recursion
    int resultRecursion = sol.stoneGameVII(stones);
    cout << "Result (Recursion): " << resultRecursion << endl;

    // Using Memoization
    int resultMemoization = sol.stoneGameVIIMemo(stones);
    cout << "Result (Memoization): " << resultMemoization << endl;

    // Using Tabulation
    int resultTabulation = sol.stoneGameVIITable(stones);
    cout << "Result (Tabulation): " << resultTabulation << endl;

    return 0;
}
