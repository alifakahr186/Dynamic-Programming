#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int solve(int l, int h, vector<int>& piles) {
        // Base case: no piles left
        if (l > h) return 0;

        // Maximize stones for the current player
        return max(
            piles[l] - solve(l + 1, h, piles),  // Pick the left pile
            piles[h] - solve(l, h - 1, piles)  // Pick the right pile
        );
    }

    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        return solve(0, n - 1, piles) > 0;
    }

    int solveMemo(int l, int h, vector<int>& piles, vector<vector<int>>& dp) {
        if (l > h) return 0;

        if (dp[l][h] != -1) return dp[l][h];

        dp[l][h] = max(
            piles[l] - solveMemo(l + 1, h, piles, dp), 
            piles[h] - solveMemo(l, h - 1, piles, dp)  
        );
        return dp[l][h];
    }

    bool stoneGameMemo(vector<int>& piles) {
        int n = piles.size();
        // Initialize DP table with -1 for memoization
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solveMemo(0, n - 1, piles, dp) > 0;
    }

    bool stoneGameTable(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: when only one pile is left
        for (int i = 0; i < n; ++i) {
            dp[i][i] = piles[i];
        }

        // Fill the DP table
        for (int len = 2; len <= n; ++len) { // length of the subarray
            for (int l = 0; l <= n - len; ++l) {
                int h = l + len - 1;
                dp[l][h] = max(
                    piles[l] - dp[l+1][h], 
                    piles[h] - dp[l][h-1]  
                );
            }
        }

        return dp[0][n-1] > 0;
    }
};

int main() {
    Solution sol;
    vector<int> piles = {5, 3, 4, 5};

    // Using Recursion
    if (sol.stoneGame(piles)) {
        cout << "Alice wins the game!" << endl;
    } else {
        cout << "Bob wins the game!" << endl;
    }

    // Using Memoization
    if (sol.stoneGameMemo(piles)) {
        cout << "Alice wins the game!" << endl;
    } else {
        cout << "Bob wins the game!" << endl;
    }
    
    // Using Tabulation
    if (sol.stoneGameTable(piles)) {
        cout << "Alice wins the game!" << endl;
    } else {
        cout << "Bob wins the game!" << endl;
    }

    return 0;
}
