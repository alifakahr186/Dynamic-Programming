#include <iostream>
#include <vector>

// Function to count derangements using recursion
int derangements(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }
    return (n - 1) * (derangements(n - 1) + derangements(n - 2));
}

// Function to count derangements using recursion and memoization
int derangementsMemo(int n, std::vector<int>& dp) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }
    if (dp[n] != -1) {
        return dp[n];
    }
    dp[n] = (n - 1) * (derangementsMemo(n - 1, dp) + derangementsMemo(n - 2, dp));
    
    return dp[n];
}

// Function to count derangements using tabulation
int derangementsTable(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }
    std::vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; ++i) {
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
    }
    return dp[n];
}

int main() {
    std::vector<int> arr = {1, 4, 5, 6, 7};  
    int n = arr.size(); 
    
    // Using Recursion
    int result = derangements(n);
    std::cout << "Count derangements using recursion: " << result << std::endl;

    // Using Memoization
    std::vector<int> dp(n + 1, -1);
    int resultMemo = derangementsMemo(n, dp);
    std::cout << "Count derangements using memoization: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTable = derangementsTable(n);
    std::cout << "Count derangements using tabulation: " << resultTable << std::endl;

    return 0;
}
