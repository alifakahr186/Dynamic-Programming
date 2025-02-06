#include <iostream>
#include <vector>

int Combination(std::vector<int>& comb, int target) {
    if (target == 0) return 1;
    if (target < 0) return 0;  
    
    int ans = 0;
    for (size_t i = 0; i < comb.size(); i++) {
        ans += Combination(comb, target - comb[i]);
    }

    return ans;
}

int CombinationMemo(std::vector<int>& comb, int target, std::vector<int>& dp) {
    if (target == 0) return 1;
    if (target < 0) return 0;
    if (dp[target] != -1) return dp[target];

    int ans = 0;
    for (size_t i = 0; i < comb.size(); i++) {
        ans += CombinationMemo(comb, target - comb[i], dp);
    }

    dp[target] = ans;
    return dp[target];
}

int CombinationTable(std::vector<int>& comb, int target) {
    std::vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= target; i++) {
        for (size_t j = 0; j < comb.size(); j++) {
            if (i - comb[j] >= 0) {
                dp[i] += dp[i - comb[j]];
            }
        }
    }

    return dp[target];
}

int main() {
    std::vector<int> comb = {1, 5, 8};
    int target = 4;

    // Using Recursion
    int result = Combination(comb, target);
    std::cout << "Combination Sum Using Recursion is: " << result << std::endl;

    // Using Memoization
    std::vector<int> dp(target + 1, -1);
    int resultMemo = CombinationMemo(comb, target, dp);
    std::cout << "Combination Sum Using Memoization is: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTable = CombinationTable(comb, target);
    std::cout << "Combination Sum Using Tabulation is: " << resultTable << std::endl;

    return 0;
}
