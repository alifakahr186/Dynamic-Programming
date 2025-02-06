#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>  // For std::max

// Recursion
int RodCutting(int n, int x, int y, int z) {
    // Base case: If rod length is 0, no segments can be cut
    if (n == 0) {
        return 0;
    }

    // Base case: If rod length becomes negative, return a large negative value indicating no solution
    if (n < 0) {
        return INT_MIN;
    }

    // Recursively cut the rod into segments of lengths x, y, z
    int a = RodCutting(n - x, x, y, z) + 1;
    int b = RodCutting(n - y, x, y, z) + 1;
    int c = RodCutting(n - z, x, y, z) + 1;

    // Find the maximum of the three options
    int ans = std::max(a, std::max(b, c));
    
    // If the maximum is still negative, return 0 indicating no valid segments possible
    if (ans < 0) {
        return 0;
    }

    return ans;
}

// Recursion and Memoization
int RodCuttingMemo(int n, int x, int y, int z, std::vector<int>& dp) {
    // Base case: If rod length is 0, no segments can be cut
    if (n == 0) {
        return 0;
    }

    // Base case: If rod length becomes negative, return a large negative value indicating no solution
    if (n < 0) {
        return INT_MIN;
    }

    // If the value is already computed, return it
    if (dp[n] != -1) {
        return dp[n];
    }
    
    // Recursively cut the rod into segments of lengths x, y, z
    int a = RodCuttingMemo(n - x, x, y, z, dp) + 1;
    int b = RodCuttingMemo(n - y, x, y, z, dp) + 1;
    int c = RodCuttingMemo(n - z, x, y, z, dp) + 1;

    // Find the maximum of the three options
    dp[n] = std::max(a, std::max(b, c));

    // If the maximum is still negative, return 0 indicating no valid segments possible
    if (dp[n] < 0) {
        dp[n] = 0;
    }

    return dp[n];
}

// Tabulation
int RodCuttingTable(int n, int x, int y, int z) {
    std::vector<int> dp(n + 1, INT_MIN);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        if (i >= x && dp[i - x] != INT_MIN) {
            dp[i] = std::max(dp[i], dp[i - x] + 1);
        }
        if (i >= y && dp[i - y] != INT_MIN) {
            dp[i] = std::max(dp[i], dp[i - y] + 1);
        }
        if (i >= z && dp[i - z] != INT_MIN) {
            dp[i] = std::max(dp[i], dp[i - z] + 1);
        }
    }

    return (dp[n] < 0) ? 0 : dp[n];
}

int main() {
    int x = 3, y = 5, z = 2;
    int n = 7;

    // Using Recursion
    int result = RodCutting(n, x, y, z);
    std::cout << "Cut Rod into Segments through Recursion: " << result << std::endl;

    // Using Memoization
    std::vector<int> dp(n + 1, -1);
    int ans = RodCuttingMemo(n, x, y, z, dp);
    std::cout << "Cut Rod into Segments through Memoization: " << ans << std::endl;

    // Using Tabulation
    int resultTabulation = RodCuttingTable(n, x, y, z);
    std::cout << "Cut Rod into Segments through Tabulation: " << resultTabulation << std::endl;

    return 0;
}
 