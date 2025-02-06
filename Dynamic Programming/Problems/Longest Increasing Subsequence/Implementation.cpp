#include <iostream>
#include <vector>
#include <algorithm> // For std::max and std::reverse

int increasingSubsequence(int n, int a[], int curr, int prev) {
    if (curr == n) return 0;

    // For include
    int take = 0;
    if (prev == -1 || a[curr] > a[prev]) {
        take = 1 + increasingSubsequence(n, a, curr + 1, curr); 
    }

    // For exclude
    int notTake = increasingSubsequence(n, a, curr + 1, prev);
    return std::max(take, notTake);
}

int increasingSubsequenceMemo(int n, int a[], int curr, int prev, std::vector<std::vector<int>>& dp) {
    if (curr == n) return 0;

    if (dp[curr][prev + 1] != -1) return dp[curr][prev + 1];
    
    // For include
    int take = 0;
    if (prev == -1 || a[curr] > a[prev]) {
        take = 1 + increasingSubsequenceMemo(n, a, curr + 1, curr, dp); 
    }

    // For exclude
    int notTake = increasingSubsequenceMemo(n, a, curr + 1, prev, dp);
    return dp[curr][prev + 1] = std::max(take, notTake);
}

int increasingSubsequenceTable(int n, int a[]) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0)); 

    for (int curr = n - 1; curr >= 0; curr--) {
        for (int prev = curr - 1; prev >= -1; prev--) {
            // For include
            int take = 0;
            if (prev == -1 || a[curr] > a[prev]) {
                take = 1 + dp[curr + 1][curr + 1]; 
            }

            // For exclude
            int notTake = dp[curr + 1][prev + 1];
            dp[curr][prev + 1] = std::max(take, notTake);
        }
    }
    
    return dp[0][0];
}

//Tabulation method using space optimization
int increasingSubsequenceTable2(int n, int a[]) {
    std::vector<int> currRow(n + 1, 0);
    std::vector<int> nextRow(n + 1, 0);

    for (int curr = n - 1; curr >= 0; curr--) {
        for (int prev = curr - 1; prev >= -1; prev--) {
            // For include
            int take = 0;
            if (prev == -1 || a[curr] > a[prev]) {
                take = 1 + nextRow[curr + 1]; 
            }

            // For exclude
            int notTake = nextRow[prev + 1];
            currRow[prev + 1] = std::max(take, notTake);
        }
        
        nextRow = currRow;
    }
    
    return nextRow[0];
}

int main() {
    int a[] = {2, 8, 3, 7, 9, 1};
    int n = sizeof(a) / sizeof(a[0]);
    
    // Using Recursion
    int result = increasingSubsequence(n, a, 0, -1);
    std::cout << "Length of Longest Increasing Subsequence Using Recursion is: " << result << std::endl;

    // Using Memoization
    std::vector<std::vector<int>> dp(n, std::vector<int>(n + 1, -1)); 
    int resultMemo = increasingSubsequenceMemo(n, a, 0, -1, dp);
    std::cout << "Length of Longest Increasing Subsequence Using Memoization is: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTable = increasingSubsequenceTable(n, a);
    std::cout << "Length of Longest Increasing Subsequence Using Tabulation is: " << resultTable << std::endl;

    // Using Optimized Tabulation
    int resultTable2 = increasingSubsequenceTable2(n, a);
    std::cout << "Length of Longest Increasing Subsequence Using Optimized Tabulation is: " << resultTable2 << std::endl;

    return 0;
}
