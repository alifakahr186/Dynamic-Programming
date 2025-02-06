#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int solve(vector<int>& nums, int i, int j) {
        if (i == j) {
            return nums[i]; 
        }

        int pickFirst = nums[i] - solve(nums, i + 1, j); 
        int pickLast = nums[j] - solve(nums, i, j - 1);  

        return max(pickFirst, pickLast);
    }

    int solveMemo(vector<int>& nums, int i, int j, vector<vector<int>>& dp) {
        if (i == j) {
            return nums[i]; 
        }
        if(dp[i][j] != 0) return dp[i][j];

        int pickFirst = nums[i] - solveMemo(nums, i + 1, j, dp); 
        int pickLast = nums[j] - solveMemo(nums, i, j - 1, dp);   
        
        dp[i][j] = max(pickFirst, pickLast);
        return dp[i][j];
    }

    bool PredictTheWinner(vector<int>& nums) {
        return solve(nums, 0, nums.size() - 1) >= 0;
    }

    bool PredictTheWinnerMemo(vector<int>& nums) {
        int n = nums.size();  
        vector<vector<int>> dp(n, vector<int>(n, 0)); 
        return solveMemo(nums, 0, nums.size() - 1, dp) >= 0;
    }

    bool PredictTheWinnerTable(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (i == j) {
                    dp[i][j] = nums[i];
                } else {
                    dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
                }
            }
        }

        // If player 1's score is greater than or equal to 0, player 1 can win
        return dp[0][n - 1] >= 0;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {1, 5, 233, 7};
    
    // Using Recursion
    if (solution.PredictTheWinner(nums)) {
        cout << "Player 1 can win the game." << endl;
    } else {
        cout << "Player 1 cannot win the game." << endl;
    }
    
    // Using Memoization
    if (solution.PredictTheWinnerMemo(nums)) {
        cout << "Player 1 can win the game." << endl;
    } else {
        cout << "Player 1 cannot win the game." << endl;
    }
    
    // Using Tabulation
    if (solution.PredictTheWinnerTable(nums)) {
        cout << "Player 1 can win the game." << endl;
    } else {
        cout << "Player 1 cannot win the game." << endl;
    }

    return 0;
}
