#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int PerfectSquare(int num) {
    if (num == 0) return 0;
 
    int ans = num;
    for (size_t i = 1; i * i <= num; i++) {
        int temp = i * i;
        ans = std::min(ans, 1 + PerfectSquare(num - temp));
    }

    return ans;
}

int PerfectSquareMemo(int num, std::vector<int>& dp) { 
    if (num == 0) return 0;
 
    if (dp[num] != -1) return dp[num];

    int ans = num;
    for (size_t i = 1; i * i <= num; i++) {
        int temp = i * i;
        ans = std::min(ans, 1 + PerfectSquareMemo(num - temp, dp));
    }

    dp[num] = ans;

    return dp[num];
}

int PerfectSquareTable(int num) {
    std::vector<int> dp(num + 1, INT_MAX);
    dp[0] = 0;

    for (size_t i = 1; i <= num; i++) {
        for (size_t j = 1; j * j <= i; j++) {
            int temp = j * j;
            dp[i] = std::min(dp[i], dp[i - temp] + 1);
        }
    }

    return dp[num];
}

int main() {
    int num = 12;

    // Using Recursion
    int result = PerfectSquare(num);
    std::cout << "Perfect Square Using Recursion: " << result << std::endl;

    // Using Memoization
    std::vector<int> dp(num + 1, -1);
    int resultMemo = PerfectSquareMemo(num, dp);
    std::cout << "Perfect Square Using Memoization: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTable = PerfectSquareTable(num);
    std::cout << "Perfect Square Using Tabulation: " << resultTable << std::endl;

    return 0;
}
