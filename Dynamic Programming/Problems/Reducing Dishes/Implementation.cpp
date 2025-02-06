#include <iostream>
#include <vector>
#include <algorithm>

// Bubble sort function to sort the satisfaction vector
void sortSatisfaction(std::vector<int>& satisfaction) {
    int n = satisfaction.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (satisfaction[j] > satisfaction[j + 1]) {
                // Swap elements
                int temp = satisfaction[j];
                satisfaction[j] = satisfaction[j + 1];
                satisfaction[j + 1] = temp;
            }
        }
    }
}

int maxSatisfaction(std::vector<int>& satisfaction, int index, int time){
    if (index == satisfaction.size()) return 0;

    int include = satisfaction[index] * (time + 1) + maxSatisfaction(satisfaction, index + 1, time + 1);
    int exclude = maxSatisfaction(satisfaction, index + 1, time);
    return std::max(include, exclude);
}

int maxSatisfactionMemo(std::vector<int>& satisfaction, int index, int time, std::vector<std::vector<int>>& dp){
    if (index == satisfaction.size()) return 0;

    if (dp[index][time] != -1) return dp[index][time];

    int include = satisfaction[index] * (time + 1) + maxSatisfactionMemo(satisfaction, index + 1, time + 1, dp);
    int exclude = maxSatisfactionMemo(satisfaction, index + 1, time, dp);
    return dp[index][time] = std::max(include, exclude);
}

int maxSatisfactionTable(std::vector<int>& satisfaction){
    int size = satisfaction.size();
    std::vector<std::vector<int>> dp(size + 1, std::vector<int>(size + 1, 0));

    for (int index = size - 1; index >= 0; index--) {
        for (int time = index; time >= 0; time--) {
            int include = satisfaction[index] * (time + 1) + dp[index + 1][time + 1];
            int exclude = dp[index + 1][time];

            dp[index][time] = std::max(include, exclude);
        }
    }

    return dp[0][0];
}

int maxSatisfactionTable2(std::vector<int>& satisfaction){
    int size = satisfaction.size();

    std::vector<int> curr(size + 1, 0);
    std::vector<int> next(size + 1, 0);

    for (int index = size - 1; index >= 0; index--) {
        for (int time = index; time >= 0; time--) {
            int include = satisfaction[index] * (time + 1) + next[time + 1];
            int exclude = next[time];

            curr[time] = std::max(include, exclude);
        }
        next = curr;
    }

    return next[0];
}

int main(){
    std::vector<int> satisfaction = {-1, -8, 0, 5, -9};
    int size = satisfaction.size();
    sortSatisfaction(satisfaction);

    // Using Recursion
    int result = maxSatisfaction(satisfaction, 0, 0);
    std::cout << "By Reducing Dishes We have Max Satisfaction (Recursion): " << result << std::endl;

    // Using Memoization
    std::vector<std::vector<int>> dp(size + 1, std::vector<int>(size + 1, -1));
    int resultMemo = maxSatisfactionMemo(satisfaction, 0, 0, dp);
    std::cout << "By Reducing Dishes We have Max Satisfaction (Memoization): " << resultMemo << std::endl;

    // Using Tabulation
    int resultTable = maxSatisfactionTable(satisfaction);
    std::cout << "By Reducing Dishes We have Max Satisfaction (Tabulation): " << resultTable << std::endl;

    // Using Tabulation2
    int resultTable2 = maxSatisfactionTable2(satisfaction);
    std::cout << "By Reducing Dishes We have Max Satisfaction (Tabulation2): " << resultTable2 << std::endl;

    return 0;
}
