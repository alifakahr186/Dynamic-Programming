#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int solve(vector<int>& piles, int person, int i, int M) {
        int n = piles.size();

        // Base case: If all piles have been taken
        if (i >= n) return 0;

        int stones = 0;
        int result = (person == 1) ? INT_MIN : INT_MAX; // Alice maximizes, Bob minimizes

        for (int x = 1; x <= min(2 * M, n - i); x++) { //Stopping to go out of bound 2*M that why we min
            stones += piles[i + x - 1];
            if (person == 1) { // Alice's turn: maximize score
                result = max(result, stones + solve(piles, 0, i + x, max(M, x)));
            } else { // Bob's turn: minimize Alice's score
                result = min(result, solve(piles, 1, i + x, max(M, x)));
            }
        }

        return result;
    }

    int stoneGame(vector<int>& piles) {
        return solve(piles, 1, 0, 1);
    }

    int solveMemo(vector<int>& piles, int person, int i, int M, vector<vector<vector<int>>>& dp) {
        int n = piles.size();

        if (i >= n) return 0;

        //dp[1, 0(2)][n+1][n+1]; becaue three values 
        if (dp[person][i][M] != -1) return dp[person][i][M];

        int stones = 0;
        int result = (person == 1) ? INT_MIN : INT_MAX; // Alice maximizes, Bob minimizes

        for (int x = 1; x <= min(2 * M, n - i); x++) {
            stones += piles[i + x - 1];
            if (person == 1) { // Alice's turn: maximize score
                result = max(result, stones + solveMemo(piles, 0, i + x, max(M, x), dp));
            } else { // Bob's turn: minimize Alice's score
                result = min(result, solveMemo(piles, 1, i + x, max(M, x), dp));
            }
        }

        return dp[person][i][M] = result;
    }

    int stoneGameMemo(vector<int>& piles) {
        int n = piles.size();
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(n + 1, vector<int>(n + 1, -1)));
        return solveMemo(piles, 1, 0, 1, dp);
    }

    int stoneGameTable(vector<int>& piles) {
        int n = piles.size();

        // Suffix sum to calculate total stones easily
        vector<int> suffixSum(n + 1, 0);
        
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // DP table: dp[i][M] = maximum stones Alice can get starting from pile i with M
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Iterate from the last pile to the first pile
        for (int i = n - 1; i >= 0; --i) {
            for (int M = 1; M <= n; ++M) {
                int maxStones = 0;

                // Iterate over all possible X values (1 to 2M)
                for (int X = 1; X <= 2 * M && i + X <= n; ++X) {
                    maxStones = max(maxStones, suffixSum[i] - dp[i + X][max(M, X)]);
                }

                dp[i][M] = maxStones;
            }
        }

        return dp[0][1]; // Result for Alice starting from pile 0 with M = 1
    }

};

int main() {
    Solution sol;
    vector<int> piles = {2, 7, 9, 4, 4};

    // Using Recursion
    if (sol.stoneGame(piles)) {
        cout << "Alice wins the game!" << endl;
    } else {
        cout << "Bob wins the game!" << endl;
    }

    // Using Memoization
    if (sol.stoneGameMemo(piles)) {
        cout << "Alice wins the game!" << endl;
    } else {
        cout << "Bob wins the game!" << endl;
    }
    
    // Using Tabulation
    if (sol.stoneGameTable(piles)) {
        cout << "Alice wins the game!" << endl;
    } else {
        cout << "Bob wins the game!" << endl;
    }

    return 0;
}
