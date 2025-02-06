#include <iostream>
#include <vector>
#include <algorithm> // For std::max

int NonAdjacent(const std::vector<int>& arr, int size) {
    if (size < 0) {
        return 0;
    }
    
    int incl = NonAdjacent(arr, size - 2) + arr[size];
    int excl = NonAdjacent(arr, size - 1);

    return std::max(incl, excl);
}

int NonAdjacentMemo(const std::vector<int>& arr, int size, std::vector<int>& dp) {
    if (size < 0) {
        return 0;
    }

    if (dp[size] != -1) {
        return dp[size];
    }

    int incl = NonAdjacentMemo(arr, size - 2, dp) + arr[size];
    int excl = NonAdjacentMemo(arr, size - 1, dp);

    dp[size] = std::max(incl, excl);
    return dp[size];
}

int NonAdjacentTable(const std::vector<int>& arr) {
    int size = arr.size();
    if (size == 0) return 0;

    std::vector<int> dp(size, 0);
    dp[0] = arr[0];
    
    if (size > 1) dp[1] = std::max(arr[0], arr[1]);

    for (int i = 2; i < size; i++) {
        dp[i] = std::max(dp[i - 1], arr[i] + dp[i - 2]);
    }

    return dp[size - 1];
}

int main() {
    std::vector<int> arr = {3, 4, 5, 6, 3, 8, 9, 10, 6};
    int size = arr.size();

    //Using Recursion
    int result = NonAdjacent(arr, size - 1);
    std::cout << "Maximum Sum of Non-Adjacent Elements: " << result << std::endl;

    // Using Memoization
    std::vector<int> dp(size, -1);
    int resultMemo = NonAdjacentMemo(arr, size - 1, dp);
    std::cout << "Maximum Sum of Non-Adjacent Elements Using Memoization: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTable = NonAdjacentTable(arr);
    std::cout << "Maximum Sum of Non-Adjacent Elements Using Tabulation: " << resultTable << std::endl;

    return 0;
}
