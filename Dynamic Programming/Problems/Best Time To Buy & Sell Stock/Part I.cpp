#include <iostream>
#include <vector>
#include <algorithm> 

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) return 0; // handle empty input case
        
        int mini = prices[0];
        int profit = 0;

        for (int i = 1; i < prices.size(); i++) {
            int diff = prices[i] - mini;
            profit = std::max(profit, diff);
            mini = std::min(mini, prices[i]);
        }

        return profit;
    }
};

int main() {
    Solution sol;
    std::vector<int> prices = {1, 4, 6, 7, 3, 1, 10};
    
    int max_profit = sol.maxProfit(prices);
    std::cout << "Max Profit: " << max_profit << std::endl;

    return 0;
}
