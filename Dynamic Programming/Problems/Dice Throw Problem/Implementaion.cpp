#include <iostream>
#include <vector>

long long DiceRolls(long long dice, long long faces, long long target) {
    if (target < 0) return 0;
    if (dice == 0 && target == 0) return 1;
    if (dice == 0) return 0;

    long long ans = 0;
    for (long long i = 1; i <= faces; i++) {
        ans += DiceRolls(dice - 1, faces, target - i);
    }

    return ans;
}

long long DiceRollsMemo(long long dice, long long faces, long long target, std::vector<std::vector<long long>>& dp) {
    if (target < 0) return 0;
    if (dice == 0 && target == 0) return 1;
    if (dice == 0) return 0;

    if (dp[dice][target] != -1) {
        return dp[dice][target];
    }

    long long ans = 0;
    for (long long i = 1; i <= faces; i++) {
        ans += DiceRollsMemo(dice - 1, faces, target - i, dp);
    }

    return dp[dice][target] = ans;
}

long long DiceRollsTable(long long d, long long faces, long long t) {
    std::vector<std::vector<long long>> dp(d + 1, std::vector<long long>(t + 1, 0));
    dp[0][0] = 1;

    for (long long dice = 1; dice <= d; dice++) {
        for (long long target = 1; target <= t; target++) {
            for (long long i = 1; i <= faces; i++) {
                if (target >= i) {
                    dp[dice][target] += dp[dice - 1][target - i];
                }
            }
        }
    }

    return dp[d][t];
}

int main() {
    long long N = 3; // Number of dice
    long long M = 6; // Number of faces on each die
    long long X = 7; // Target sum

    // Using Recursion
    long long resultRec = DiceRolls(N, M, X);
    std::cout << "Number of Dice Rolls with Target Sum Using Recursion: " << resultRec << std::endl;

    // Using Memoization
    std::vector<std::vector<long long>> dp1(N + 1, std::vector<long long>(X + 1, -1));
    long long resultMemo = DiceRollsMemo(N, M, X, dp1);
    std::cout << "Number of Dice Rolls with Target Sum Using Memoization: " << resultMemo << std::endl;

    // Using Tabulation
    long long resultTable = DiceRollsTable(N, M, X);
    std::cout << "Number of Dice Rolls with Target Sum Using Tabulation: " << resultTable << std::endl;

    return 0;
}
