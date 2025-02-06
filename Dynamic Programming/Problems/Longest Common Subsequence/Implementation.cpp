#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::max and std::reverse

void isSubsequence(std::vector<std::vector<int>>& a, const std::vector<char>& elementx,  const std::vector<char>& elementy) {
                        
    size_t size_x = elementx.size();
    size_t size_y = elementy.size();

    // Initialize the 2D array
    for (size_t i = 0; i <= size_x; ++i) {
        a[i][0] = 0;
    }
    for (size_t j = 0; j <= size_y; ++j) {
        a[0][j] = 0;
    }

    // Fill the 2D array using dynamic programming
    for (size_t i = 1; i <= size_x; ++i) {
        for (size_t j = 1; j <= size_y; ++j) {
            if (elementx[i-1] == elementy[j-1]) {
                a[i][j] = a[i-1][j-1] + 1;
            } else {
                a[i][j] = std::max(a[i-1][j], a[i][j-1]);
            }
        }
    }
}

std::string reconstructLCS(const std::vector<std::vector<int>>& a, const std::vector<char>& elementx, const std::vector<char>& elementy) {
    std::string lcs;
    size_t i = elementx.size();
    size_t j = elementy.size();

    while (i > 0 && j > 0) {
        if (elementx[i-1] == elementy[j-1]) {
            lcs.push_back(elementx[i-1]);
            --i;
            --j;
        } else if (a[i-1][j] > a[i][j-1]) {
            --i;
        } else {
            --j;
        }
    }

    std::reverse(lcs.begin(), lcs.end()); 
    return lcs;
}

int isSubsequenceMemo(std::vector<std::vector<int>>& dp, const std::vector<char>& elementx, const std::vector<char>& elementy) {
                        
    size_t size_x = elementx.size();
    size_t size_y = elementy.size();

    // Initialize the 2D array
    for (size_t i = 0; i <= size_x; ++i) {
        dp[i][0] = 0;
    }
    for (size_t j = 0; j <= size_y; ++j) {
        dp[0][j] = 0;
    }

    // Fill the 2D array using dynamic programming
    for (size_t i = 1; i <= size_x; ++i) {
        for (size_t j = 1; j <= size_y; ++j) {
            if (elementx[i-1] == elementy[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[size_x][size_y];
}

std::string reconstructLCSMemo(const std::vector<std::vector<int>>& dp, const std::vector<char>& elementx, const std::vector<char>& elementy) {
    std::string lcs;
    size_t i = elementx.size();
    size_t j = elementy.size();

    while (i > 0 && j > 0) {
        if (elementx[i-1] == elementy[j-1]) {
            lcs.push_back(elementx[i-1]);
            --i;
            --j;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            --i;
        } else {
            --j;
        }
    }

    std::reverse(lcs.begin(), lcs.end()); 
    return lcs;
}

int isSubsequenceTable(const std::vector<char>& elementx, const std::vector<char>& elementy) {
    size_t size_x = elementx.size();
    size_t size_y = elementy.size();

    std::vector<int> dp(size_y + 1, 0);

    // Fill the 1D array using dynamic programming
    for (size_t i = 1; i <= size_x; ++i) {
        int prev = 0;
        for (size_t j = 1; j <= size_y; ++j) {
            int temp = dp[j];
            if (elementx[i - 1] == elementy[j - 1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = std::max(dp[j], dp[j - 1]);
            }
            prev = temp;
        }
    }

    return dp[size_y];
}

std::string reconstructLCSTable(const std::vector<std::vector<int>>& dp, const std::vector<char>& elementx, const std::vector<char>& elementy) {
    std::string lcs;
    size_t i = elementx.size();
    size_t j = elementy.size();

    while (i > 0 && j > 0) {
        if (elementx[i-1] == elementy[j-1]) {
            lcs.push_back(elementx[i-1]);
            --i;
            --j;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            --i;
        } else {
            --j;
        }
    }

    std::reverse(lcs.begin(), lcs.end()); 
    return lcs;
}

int main() {
    std::vector<char> x = {'A', 'B', 'A', 'A', 'B', 'A'};
    std::vector<char> y = {'B', 'A', 'B', 'B', 'A', 'B'};
    size_t size_x = x.size();
    size_t size_y = y.size();

    // Initialize a 2D array to store intermediate results
    std::vector<std::vector<int>> a(size_x + 1, std::vector<int>(size_y + 1, 0));

    //Using Recursion
    isSubsequence(a, x, y);
    // Get the length of LCS
    int lcs_length = a[size_x][size_y];
    std::cout << "Length of Longest Common Subsequence Using Recursion is: " << lcs_length << std::endl;
    // Reconstruct the LCS string
    std::string lcs = reconstructLCS(a, x, y);
    std::cout << "Longest Common Subsequence is: " << lcs << std::endl;


    //Using Memoization
    std::vector<std::vector<int>> dp(size_x + 1, std::vector<int>(size_y + 1, -1));
    isSubsequenceMemo(dp, x, y);
    // Get the length of LCS
    int lcs_length_Memo = a[size_x][size_y];
    std::cout << "Length of Longest Common Subsequence Using Memoization is: " << lcs_length_Memo << std::endl;
    // Reconstruct the LCS string
    std::string lcs_Memo = reconstructLCSMemo(dp, x, y);
    std::cout << "Longest Common Subsequence is: " << lcs_Memo << std::endl;


    //Using Tabulation
    isSubsequenceTable(x, y);
    // Get the length of LCS
    int lcs_length_Table = a[size_x][size_y];
    std::cout << "Length of Longest Common Subsequence Using Tabulation is: " << lcs_length_Table << std::endl;
    // Reconstruct the LCS string
    std::string lcs_Table = reconstructLCSTable(a, x, y);
    std::cout << "Longest Common Subsequence is: " << lcs_Table << std::endl;

    return 0;
}
