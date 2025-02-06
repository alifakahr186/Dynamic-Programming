#include <iostream>
#include <vector>
#include <climits> // For INT_MAX

void SubsetSum(std::vector<std::vector<int>>& a, const std::vector<int>& array, int sum) {
    int size = array.size();

    // Initialize base case: If sum is 0, we can always have a subset (empty subset) that sums to 0
    for (int i = 0; i <= size; ++i) {
        a[i][0] = 1;
    }

    // Fill the subset sum matrix
    for (size_t i = 1; i <= size; ++i) {
        for (size_t j = 1; j <= sum; ++j) {
            if (array[i - 1] > j) {
                a[i][j] = a[i - 1][j];
            } else {
                a[i][j] = a[i - 1][j] || a[i - 1][j - array[i - 1]];
            }
        }
    }
}

int SubsetSumMemo(std::vector<std::vector<int>>& dp, const std::vector<int>& array, int sum) {
    int size = array.size();
    for (int i = 0; i <= size; ++i) {
        dp[i][0] = 1;
    }

    // Fill the subset sum matrix
    for (size_t i = 1; i <= size; ++i) {
        for (size_t j = 1; j <= sum; ++j) {
            if (array[i - 1] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - array[i - 1]];
            }
        }
    }
    return dp[size][sum];
}

int Subsettable(const std::vector<int>& array, int sum) {
    int size = array.size();
    std::vector<int> dp(sum + 1, 0);
    dp[0] = 1; // Base case: sum 0 can always be formed with an empty subset

    for (size_t i = 0; i < size; ++i) {
        for (int j = sum; j >= array[i]; --j) {
            dp[j] = dp[j] || dp[j - array[i]];
        }
    }
    
    return dp[sum];
}

int main() {
    std::vector<int> array = {2, 3, 5, 7, 10};
    int sum = 14;
    int size = array.size();
    
    // Initialize a 2D array to store intermediate results
    std::vector<std::vector<int>> a(size + 1, std::vector<int>(sum + 1, 0));

    // Using Recursion
    SubsetSum(a, array, sum);
    if (a[size][sum] == 1) {
        std::cout << "There exists a subset of the array that sums to " << sum << std::endl;
    } else {
        std::cout << "No subset of the array sums to " << sum << std::endl;
    }

    // Using Memoization
    std::vector<std::vector<int>> dp(size + 1, std::vector<int>(sum + 1, -1));
    if (SubsetSumMemo(dp, array, sum)) {
        std::cout << "There exists a subset of the array that sums to " << sum << std::endl;
    } else {
        std::cout << "No subset of the array sums to " << sum << std::endl;
    }

    // Using Tabulation
    if (Subsettable(array, sum)) {
        std::cout << "There exists a subset of the array that sums to " << sum << std::endl;
    } else {
        std::cout << "No subset of the array sums to " << sum << std::endl;
    }

    return 0;
}
