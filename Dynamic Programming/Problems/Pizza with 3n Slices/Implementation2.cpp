#include <iostream>
#include <vector>
#include <algorithm> // For std::max

int PizzaSlices(int index, int endIndex, std::vector<int>& slices, int n) {
    if (n == 0 || index > endIndex) {
        return 0;
    }

    int take = slices[index] + PizzaSlices(index + 2, endIndex, slices, n - 1);
    int notake = PizzaSlices(index + 1, endIndex, slices, n);
    return std::max(take, notake);
}

int PizzaSlicesMemo(int index, int endIndex, std::vector<int>& slices, int n, std::vector<std::vector<int>>& dp) {
    if (n == 0 || index > endIndex) {
        return 0;
    }

    if (dp[index][n] != -1) {
        return dp[index][n];
    }

    int take = slices[index] + PizzaSlicesMemo(index + 2, endIndex, slices, n - 1, dp);
    int notake = PizzaSlicesMemo(index + 1, endIndex, slices, n, dp);
    return dp[index][n] = std::max(take, notake);
}

int PizzaSlicesTable(std::vector<int>& slices, int n) {
    int k = slices.size();

    //Solve Using Space Optimization for case1
    std::vector<int> prev1(k + 2, 0);
    std::vector<int> curr1(k + 2, 0);
    std::vector<int> next1(k + 2, 0);

    //for case2
    std::vector<int> prev2(k + 2, 0);
    std::vector<int> curr2(k + 2, 0);
    std::vector<int> next2(k + 2, 0);

    // Case 1: Exclude the last element, consider slices from 0 to k-2
    for (int index = k - 2; index >= 0; index--) {
        for (int j = 1; j <= n; j++) {
            int take = slices[prev1] + (next1 < k ? next1[j - 1] : 0);
            int notake = curr1[j];
            dp1[index][j] = std::max(take, notake);
        }

        next1 = curr1;
        curr1 = prev1;
    }
    int case1 = dp1[0][n];

    // Case 2: Exclude the first element, consider slices from 1 to k-1
    for (int index = k - 1; index >= 1; index--) {
        for (int j = 1; j <= n; j++) {
            int take = slices[prev2] + (next2 < k ? next2[j - 1] : 0);
            int notake = curr2[j];
            dp2[prev2][j] = std::max(take, notake);
        }

        next2 = curr2;
        curr2 = prev2;
    }
    int case2 = dp2[1][n];

    return std::max(case1, case2);
}


int main() {
    std::vector<int> slices = {1, 2, 3, 4, 5, 6}; // Example with 3n = 6, n = 2
    int k = slices.size();
    int n = k / 3;

    // Using Recursion
    int case1 = PizzaSlices(0, k - 2, slices, n);
    int case2 = PizzaSlices(1, k - 1, slices, n);
    std::cout << "Pizza with 3n Slices Using Recursion: " << std::max(case1, case2) << std::endl;

    // Using Memoization
    std::vector<std::vector<int>> dp1(k, std::vector<int>(n + 1, -1));
    case1 = PizzaSlicesMemo(0, k - 2, slices, n, dp1);
    std::vector<std::vector<int>> dp2(k, std::vector<int>(n + 1, -1));
    case2 = PizzaSlicesMemo(1, k - 1, slices, n, dp2);
    std::cout << "Pizza with 3n Slices Using Memoization: " << std::max(case1, case2) << std::endl;

    // Using Tabulation
    int result = PizzaSlicesTable(slices, n);
    std::cout << "Pizza with 3n Slices Using Tabulation: " << result << std::endl;

    return 0;
}
