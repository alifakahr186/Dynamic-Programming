#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void solve(int n, int last, int& count) {
        if (n == 0) {
            count++;
            return;
        }
        for (int i = last; i < 5; i++) { // Loop from `last` to 4 to maintain lexicographic order
            solve(n - 1, i, count);      // Recursive call with one less character
        }
    }

    int countVowelStrings(int n) {
        int count = 0;
        solve(n, 0, count); 
        return count;
    }

    int solveMemo(int n, int last, vector<vector<int>>& dp) {
        if (n == 0) return 1;  

        if (dp[n][last] != -1) return dp[n][last]; 

        int count = 0;
        for (int i = last; i < 5; i++) {
            count += solveMemo(n - 1, i, dp);
        }

        return dp[n][last] = count; 
    }

    int countVowelStringsMemo(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(5, -1));
        return solveMemo(n, 0, dp); 
    }

    int countVowelStringsTable(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));

        // Base case: There's 1 way to form strings of length 1 with each vowel
        for (int i = 0; i < 5; i++) {
            dp[1][i] = 1;
        }

        for (int i = 2; i <= n; i++) { // For each string length
            for (int j = 0; j < 5; j++) { // For each vowel
                dp[i][j] = 0;
                for (int k = j; k < 5; k++) { 
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }

        // Sum up all possibilities for strings of length `n`
        int count = 0;
        for (int i = 0; i < 5; i++) {
            count += dp[n][i];
        }

        return count;
    }
};

int main() {
    Solution sol;
    int n = 3;  

    // Using recursion
    int result = sol.countVowelStrings(n);
    cout << "Using recursion: Number of lexicographically sorted vowel strings of length " << n << result << endl;

    // Using memoization
    int resultMemo = sol.countVowelStringsMemo(n);
    cout << "Using memoization: Number of lexicographically sorted vowel strings of length " << n << resultMemo << endl;

    // Using tabulation
    int resultTable = sol.countVowelStringsTable(n);
    cout << "Using tabulation: Number of lexicographically sorted vowel strings of length " << n << resultTable << endl;

    return 0;
}
