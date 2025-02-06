#include <iostream>
#include <vector>
#include <algorithm>

bool check(const std::vector<int>& base, const std::vector<int>& newBox) {
    return (newBox[0] <= base[0] && newBox[1] <= base[1] && newBox[2] <= base[2]);
}

int MaxCuboidHeight(int n, std::vector<std::vector<int>>& a) {
    std::vector<int> currRow(n + 1, 0);
    std::vector<int> nextRow(n + 1, 0);

    for (int curr = n - 1; curr >= 0; curr--) {
        for (int prev = curr - 1; prev >= -1; prev--) {
            
            int take = 0;
            if (prev == -1 || check(a[prev], a[curr])) {
                take = a[curr][2] + nextRow[curr + 1];
            }

            int notTake = 0 + nextRow[prev + 1];
            currRow[prev + 1] = std::max(take, notTake);
        }

        nextRow = currRow;
    }

    return nextRow[0];
}

int MaxCuboidHeightMemoization(int curr, int prev, std::vector<std::vector<int>>& cuboids, std::vector<std::vector<int>>& dp) {
    if (curr == cuboids.size()) {
        return 0;
    }

    if (dp[curr][prev + 1] != -1) {
        return dp[curr][prev + 1];
    }

    int take = 0;
    if (prev == -1 || check(cuboids[prev], cuboids[curr])) {
        take = cuboids[curr][2] + MaxCuboidHeightMemoization(curr + 1, curr, cuboids, dp);
    }

    int notTake = MaxCuboidHeightMemoization(curr + 1, prev, cuboids, dp);

    return dp[curr][prev + 1] = std::max(take, notTake);
}

int MaxCuboidHeightTabulation(int n, std::vector<std::vector<int>>& a) {
    std::vector<int> dp(n, 0);

    // Fill the dp array with the height of each cuboid as the starting point
    for (int i = 0; i < n; i++) {
        dp[i] = a[i][2];
    }

    // Build the dp table in a bottom-up manner
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (check(a[j], a[i])) {
                dp[i] = std::max(dp[i], a[i][2] + dp[j]);
            }
        }
    }

    // Find the maximum height from the dp array
    int maxHeight = 0;
    for (int i = 0; i < n; i++) {
        maxHeight = std::max(maxHeight, dp[i]);
    }

    return maxHeight;
}

int main() {
    std::vector<std::vector<int>> Cuboid = {{12, 23, 45}, {20, 45, 50}, {37, 53, 95}};
    int n = Cuboid.size();

    // Sort each cuboid to make sure the dimensions are in non-increasing order
    for (auto& a : Cuboid) {
        std::sort(a.begin(), a.end(), std::greater<int>());
    }

    // Sort cuboids by their base dimensions
    std::sort(Cuboid.begin(), Cuboid.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[0] * a[1] > b[0] * b[1];
    });

    //Using Recursion
    int result = MaxCuboidHeight(Cuboid.size(), Cuboid);
    std::cout << "Maximum Height by Stacking Cuboid Using Recursion is: " << result << std::endl;

    //Using Memoization
    std::vector<std::vector<int>> dp(n, std::vector<int>(n + 1, -1));
    int resultMemo = MaxCuboidHeightMemoization(0, -1, Cuboid, dp);
    std::cout << "Maximum Height by Stacking Cuboid Using Memoization is: " << result << std::endl;

    //Using Tabulation
    int resultTable = MaxCuboidHeightTabulation(Cuboid.size(), Cuboid);
    std::cout << "Maximum Height by Stacking Cuboid Using Tabulation is: " << resultTable << std::endl;

    return 0;
}
