#include <iostream>
#include <vector>
using namespace std;

int uniquePathsRecursive(int m, int n) {
    if (m == 1 || n == 1) return 1; 
    return uniquePathsRecursive(m - 1, n) + uniquePathsRecursive(m, n - 1); // Move down or right.
}

int uniquePathsMemo(int m, int n, vector<vector<int>>& dp) {
    if (m == 1 || n == 1) return 1; // Base case.
    
    if (dp[m][n] != -1) return dp[m][n];
    
    if (dp[m][n] != -1) {
        return dp[m][n];
    }

    dp[m][n] = uniquePathsMemo(m - 1, n, dp) + uniquePathsMemo(m, n - 1, dp);
    return dp[m][n];
}

int uniquePathsTabulation(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1)); 

    // Fill the DP table.
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; 
        }
    }

    return dp[m - 1][n - 1]; // Bottom-right corner.
}

int uniquePathsOptimized(int m, int n) {
    vector<int> prev(n, 1); // Initialize 1D DP array with 1s.

    for (int i = 1; i < m; ++i) {
        vector<int> temp(n, 1); 
        for (int j = 1; j < n; ++j) {
            temp[j] = prev[j] + temp[j - 1]; 
        }
        prev = temp; 
    }

    return prev[n - 1]; 
}


int main() {
    int m = 3, n = 7; 

    cout << "Unique Paths (Recursive): " << uniquePathsRecursive(m, n) << endl;

    // Memoization Solution
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    cout << "Unique Paths (Memoization): " << uniquePathsMemo(m, n, dp) << endl;

    // Tabulation Solution
    cout << "Unique Paths (Tabulation): " << uniquePathsTabulation(m, n) << endl;

    // Optimized Solution
    cout << "Unique Paths (Optimized Space): " << uniquePathsOptimized(m, n) << endl;

    return 0;
}
