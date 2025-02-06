#include <iostream>
#include <vector>

bool equalPartition(int index, int arr[], int N, int target) {
    if (target == 0) return true;
    if (index >= N || target < 0) return false;

    bool incl = equalPartition(index + 1, arr, N, target - arr[index]);
    bool excl = equalPartition(index + 1, arr, N, target);

    return incl || excl;
}

bool equalPartitionMemo(int index, int arr[], int N, int target, std::vector<std::vector<int>>& dp) {
    if (target == 0) return true;
    if (index >= N || target < 0) return false;

    if (dp[index][target] != -1) return dp[index][target];

    bool incl = equalPartitionMemo(index + 1, arr, N, target - arr[index], dp);
    bool excl = equalPartitionMemo(index + 1, arr, N, target, dp);

    return dp[index][target] = incl || excl;
}

bool equalPartitionTable(int arr[], int N, int total) {
    int target = total / 2;
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(target + 1, 0));

    // Initialize the first column to true (1)
    for (int i = 0; i <= N; i++) {
        dp[i][0] = 1;
    }

    // Fill the DP table
    for (int index = N - 1; index >= 0; index--) {
        for (int targetSum = 0; targetSum <= target; targetSum++) {
            bool incl = 0;
            if (targetSum - arr[index] >= 0) {
                incl = dp[index + 1][targetSum - arr[index]];
            }
            bool excl = dp[index + 1][targetSum];

            dp[index][targetSum] = incl || excl;
        }
    }

    return dp[0][target];
}

int main() {
    int arr[] = {1, 5, 11 ,5}; 
    int N = sizeof(arr) / sizeof(arr[0]);
    int targetSum = 0;

    // Calculate total sum of the array
    for (int i = 0; i < N; i++) {
        targetSum += arr[i];
    }

    // If the sum is odd, partitioning into equal subsets is not possible
    if (targetSum % 2 != 0) {
        std::cout << "The array cannot be partitioned into two subsets with equal sum." << std::endl;
        return 0;
    }

    int target = targetSum / 2;

    // Using Recursion
    bool result = equalPartition(0, arr, N, target);
    std::cout << "Equal Partition Using Recursion: " << (result ? "Possible" : "Not Possible") << std::endl;

    // Using Memoization
    std::vector<std::vector<int>> dpMemo(N, std::vector<int>(target + 1, -1));
    bool resultMemo = equalPartitionMemo(0, arr, N, target, dpMemo);
    std::cout << "Equal Partition Using Memoization: "  << (resultMemo ? "Possible" : "Not Possible") << std::endl;

    // Using Tabulation
    bool resultTable = equalPartitionTable(arr, N, targetSum);
    std::cout << "Equal Partition Using Tabulation: " << (resultTable ? "Possible" : "Not Possible") << std::endl;

    return 0;
}
