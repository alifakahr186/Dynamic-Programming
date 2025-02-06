#include <iostream>
#include <vector>
#include <algorithm>

int squarematrix(std::vector<std::vector<int>>& matrix, int i, int j, int& maxi) {
    if (i >= matrix.size() || j >= matrix[0].size()) return 0;

    int right = squarematrix(matrix, i, j + 1, maxi);
    int diagonal = squarematrix(matrix, i + 1, j + 1, maxi);
    int down = squarematrix(matrix, i + 1, j, maxi);

    if (matrix[i][j] == 1) {
        int ans = 1 + std::min(right, std::min(diagonal, down));
        maxi = std::max(maxi, ans);
        return ans;
    } else {
        return 0;
    }
}

int squarematrixMemo(std::vector<std::vector<int>>& matrix, int i, int j, int& maxi, std::vector<std::vector<int>>& dp) {
    if (i >= matrix.size() || j >= matrix[0].size()) return 0;

    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    
    int right = squarematrixMemo(matrix, i, j + 1, maxi, dp);
    int diagonal = squarematrixMemo(matrix, i + 1, j + 1, maxi, dp);
    int down = squarematrixMemo(matrix, i + 1, j, maxi, dp);

    if (matrix[i][j] == 1) {
        dp[i][j] = 1 + std::min(right, std::min(diagonal, down));
        maxi = std::max(maxi, dp[i][j]);
    } else {
        dp[i][j] = 0;
    }

    return dp[i][j];
}

int squarematrixTable(std::vector<std::vector<int>>& matrix, int& maxi) {
    int row = matrix.size();
    int col = matrix[0].size();

    std::vector<std::vector<int>> dp(row + 1, std::vector<int>(col + 1, 0));

    for (int i = row - 1; i >= 0; --i) {
        for (int j = col - 1; j >= 0; --j) {
            if (matrix[i][j] == 1) {
                dp[i][j] = 1 + std::min({dp[i][j + 1], dp[i + 1][j + 1], dp[i + 1][j]});
                maxi = std::max(maxi, dp[i][j]);
            } else {
                dp[i][j] = 0;
            }
        }
    }

    return dp[0][0];
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {1, 0, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 1, 1},
        {1, 0, 0, 1}
    };

    int maxiRec = 0;
    squarematrix(matrix, 0, 0, maxiRec);
    std::cout << "Largest Square Area In Matrix Using Recursion: " << maxiRec << std::endl;

    int maxiMemo = 0;
    std::vector<std::vector<int>> dp(matrix.size(), std::vector<int>(matrix[0].size(), -1));
    squarematrixMemo(matrix, 0, 0, maxiMemo, dp);
    std::cout << "Largest Square Area In Matrix Using Memoization: " << maxiMemo << std::endl;

    int maxiTable = 0;
    squarematrixTable(matrix, maxiTable);
    std::cout << "Largest Square Area In Matrix Using Tabulation: " << maxiTable << std::endl;

    return 0;
}
