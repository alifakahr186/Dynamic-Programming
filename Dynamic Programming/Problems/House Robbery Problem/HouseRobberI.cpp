#include <iostream>
#include <vector>
#include <algorithm> // For std::max

long long int solve(const std::vector<int>& nums) {
    long long int n = nums.size();

    if (n == 0) return 0;
    if (n == 1) return nums[0];

    long long int prev2 = 0;
    long long int prev1 = nums[0];

    for (int i = 1; i < n; i++) {
        long long int incl = prev2 + nums[i];
        long long int excl = prev1;

        long long int ans = std::max(incl, excl);
        prev2 = prev1;
        prev1 = ans;
    }

    return prev1;
}


long long int houseRob(const std::vector<int>& valueInHouse) {
    int n = valueInHouse.size();

    if (n == 1) return valueInHouse[0];

    std::vector<int> first, second;

    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            first.push_back(valueInHouse[i]);
        }
        
        if (i != 0) {
            second.push_back(valueInHouse[i]);
        }
    }

    return std::max(solve(first), solve(second));
}

long long int solveMemoHelper(const std::vector<int>& nums, int n, std::vector<long long int>& dp) {
    if (n < 0) return 0;
    if (n == 0) return nums[0];

    if (dp[n] != -1) {
        return dp[n];
    }
    
    long long int incl = nums[n] + solveMemoHelper(nums, n - 2, dp);
    long long int excl = solveMemoHelper(nums, n - 1, dp);

    dp[n] = std::max(incl, excl);
    return dp[n];
}

long long int solveMemo(const std::vector<int>& nums) {
    int size = nums.size();
    std::vector<long long int> dp(size, -1);
    return solveMemoHelper(nums, size - 1, dp);
}

long long int solveTab(const std::vector<int>& nums) {
    int size = nums.size();
    if (size == 0) return 0;
    if (size == 1) return nums[0];

    std::vector<long long int> dp(size, 0);
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);

    for (int i = 2; i < size; i++) {
        dp[i] = std::max(dp[i - 1], nums[i] + dp[i - 2]);
    }

    return dp[size - 1];
}

long long int houseRobber(const std::vector<int>& valueInHouse) {
    int n = valueInHouse.size();
    if (n == 0) return 0;
    if (n == 1) return valueInHouse[0];

    // Rob houses from 0 to n-2 (excluding the last house)
    std::vector<int> first(valueInHouse.begin(), valueInHouse.end() - 1);
    // Rob houses from 1 to n-1 (excluding the first house)
    std::vector<int> second(valueInHouse.begin() + 1, valueInHouse.end());

    return std::max(solveMemo(first), solveMemo(second));
}

int main() {
    std::vector<int> houses = {2, 3, 2};

    int resultRec = houseRob(houses);
    std::cout << "Max money that can be robbed Using Recursion: " << resultRec << std::endl;

    int resultMemo = houseRobber(houses);
    std::cout << "Max money that can be robbed Using Memoization: " << resultMemo << std::endl;

    int resultTab = solveTab(houses);
    std::cout << "Max money that can be robbed Using Tabulation: " << resultTab << std::endl;

    return 0;
}
