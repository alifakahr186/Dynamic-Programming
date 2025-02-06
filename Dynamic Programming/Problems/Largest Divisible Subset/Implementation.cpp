#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    // Recursive function to find the largest divisible subset
    std::vector<int> solve(std::vector<int>& nums, int curr, int prev) {
        if (curr == nums.size()) return {};

        std::vector<int> include;
        if (prev == -1 || nums[curr] % nums[prev] == 0) {
            include = solve(nums, curr + 1, curr);
            include.push_back(nums[curr]);
        }

        std::vector<int> exclude = solve(nums, curr + 1, prev);

        return (include.size() > exclude.size()) ? include : exclude;
    }

    // Memoized version
    std::vector<int> solveMemo(std::vector<int>& nums, int curr, int prev, std::vector<std::vector<std::vector<int>>>& dp) {
        if (curr == nums.size()) return {};

        if (!dp[curr][prev + 1].empty()) return dp[curr][prev + 1];

        std::vector<int> include;
        if (prev == -1 || nums[curr] % nums[prev] == 0) {
            include = solveMemo(nums, curr + 1, curr, dp);
            include.push_back(nums[curr]);
        }

        std::vector<int> exclude = solveMemo(nums, curr + 1, prev, dp);

        dp[curr][prev + 1] = (include.size() > exclude.size()) ? include : exclude;
        return dp[curr][prev + 1];
    }

    std::vector<int> largestDivisibleSubsetTable(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};

        std::sort(nums.begin(), nums.end());

        std::vector<int> dp(n, 1);  // dp[i]: size of largest subset ending at nums[i]
        std::vector<int> prev(n, -1);  // prev[i]: index of the previous number in the subset
        int maxSize = 1, maxIndex = 0;

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
            if (dp[i] > maxSize) {
                maxSize = dp[i];
                maxIndex = i;
            }
        }

        std::vector<int> result;
        for (int i = maxIndex; i >= 0; i = prev[i]) {
            result.push_back(nums[i]);
            if (prev[i] == -1) break;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        return solve(nums, 0, -1);
    }

    std::vector<int> largestDivisibleSubsetMemo(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(n + 1));
        return solveMemo(nums, 0, -1, dp);
    }
};

int main() {
    std::vector<int> nums = {1, 2, 4, 8};

    Solution solution;

    // Using Recursion
    std::vector<int> result = solution.largestDivisibleSubset(nums);
    std::cout << "Largest Divisible Subset Using Recursion: ";
    for (int num : result) std::cout << num << " ";
    std::cout << std::endl;

    // Using Memoization
    std::vector<int> resultMemo = solution.largestDivisibleSubsetMemo(nums);
    std::cout << "Largest Divisible Subset Using Memoization: ";
    for (int num : resultMemo) std::cout << num << " ";
    std::cout << std::endl;

    // Using Tabulation
    std::vector<int> resultTable = solution.largestDivisibleSubsetTable(nums);
    std::cout << "Largest Divisible Subset Using Tabulation: ";
    for (int num : resultTable) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
