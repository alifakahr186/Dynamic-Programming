#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int solve(std::vector<int>& num1, std::vector<int>& num2, int index, bool swapped) {
        if (index == num1.size()) return 0;

        int ans = INT_MAX;

        int prev1 = num1[index - 1];
        int prev2 = num2[index - 1];

        if (swapped) {
            std::swap(prev1, prev2);
        }

        // No swap case
        if (num1[index] > prev1 && num2[index] > prev2) {
            ans = solve(num1, num2, index + 1, false);
        }

        // Swap case
        if (num1[index] > prev2 && num2[index] > prev1) {
            ans = std::min(ans, 1 + solve(num1, num2, index + 1, true));
        }

        return ans;
    }

    int solveMemo(std::vector<int>& num1, std::vector<int>& num2, int index, bool swapped, std::vector<std::vector<int>>& dp) {
        if (index == num1.size()) return 0;

        if (dp[index][swapped] != -1) {
            return dp[index][swapped]; // Fixed issue: Return the memoized value
        }

        int ans = INT_MAX;

        int prev1 = num1[index - 1];
        int prev2 = num2[index - 1];

        if (swapped) {
            std::swap(prev1, prev2);
        }

        // No swap case
        if (num1[index] > prev1 && num2[index] > prev2) {
            ans = solveMemo(num1, num2, index + 1, false, dp);
        }

        // Swap case
        if (num1[index] > prev2 && num2[index] > prev1) {
            ans = std::min(ans, 1 + solveMemo(num1, num2, index + 1, true, dp)); // Fixed issue: Use solveMemo
        }

        return dp[index][swapped] = ans;
    }

    int solveTable(std::vector<int>& num1, std::vector<int>& num2) {
        int n = num1.size();
        int swap = 0;
        int noswap = 0;
        int currswapped = 0;
        int currnoswapped = 0;

        dp[n - 1][0] = dp[n - 1][1] = 0; // Base case: no swaps needed at the end

        for (int index = n - 2; index >= 1; --index) {
            for (int swapped = 0; swapped <= 1; ++swapped) {
                int ans = INT_MAX;
                int prev1 = num1[index - 1];
                int prev2 = num2[index - 1];

                if (swapped) {
                    int temp = prev2;
                    prev2 = prev1;
                    prev1 = temp;
                }

                // No swap case
                if (num1[index] > prev1 && num2[index] > prev2) {
                    ans = noswap;
                }

                // Swap case
                if (num1[index] > prev2 && num2[index] > prev1) {
                    ans = std::min(ans, 1 + swap);
                }

                dp[index][swapped] = ans;
                if (swapped)
                {
                    currswapped = ans;
                }
                else
                {
                    currnoswap = ans;
                }
                
            }

            swap = currswap;
            noswap = currnoswap;
        }

        return min(swap, noswap);
    }

    int minSwap(std::vector<int>& num1, std::vector<int>& num2) {
        // Insert dummy elements to simplify indexing
        num1.insert(num1.begin(), -1);
        num2.insert(num2.begin(), -1);

        bool swapped = false;
        return solve(num1, num2, 1, swapped);
    }

    int minSwapMemo(std::vector<int>& num1, std::vector<int>& num2) {
        // Insert dummy elements to simplify indexing
        num1.insert(num1.begin(), -1);
        num2.insert(num2.begin(), -1);
        
        int n = num1.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(2, -1));
        bool swapped = false;
        return solveMemo(num1, num2, 1, swapped, dp);
    }

    int minSwapTable(std::vector<int>& num1, std::vector<int>& num2) {
        // Insert dummy elements to simplify indexing
        num1.insert(num1.begin(), -1);
        num2.insert(num2.begin(), -1);

        return solveTable(num1, num2);
    }
};

int main() {
    Solution sol;
    std::vector<int> num1 = {1, 3, 5, 4};
    std::vector<int> num2 = {1, 2, 3, 7};

    int result = sol.minSwap(num1, num2);
    std::cout << "Minimum Swaps to make Subsequences Increasing Using Recursion: " << result << std::endl;

    int resultMemo = sol.minSwapMemo(num1, num2);
    std::cout << "Minimum Swaps to make Subsequences Increasing Using Memoization: " << resultMemo << std::endl;

    int resultTable = sol.minSwapTable(num1, num2);
    std::cout << "Minimum Swaps to make Subsequences Increasing Using Tabulation: " << resultTable << std::endl;

    return 0;
}
