#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    int weight;
    int profit;
    int index;
};

// Comparison function to sort items by profit-to-weight ratio in descending order
bool compare(Item a, Item b) {
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(const std::vector<int>& weight, const std::vector<int>& profit, int maxWeight) {
    int itemCount = weight.size();
    std::vector<Item> items(itemCount);
    
    for (int i = 0; i < itemCount; ++i) {
        items[i] = {weight[i], profit[i], i};
    }

    // Sort items by profit-to-weight ratio
    std::sort(items.begin(), items.end(), compare);

    int currentWeight = 0;
    double totalProfit = 0.0;

    for (int i = 0; i < itemCount; ++i) {
        if (currentWeight + items[i].weight <= maxWeight) {
            currentWeight += items[i].weight;
            totalProfit += items[i].profit;
        } else {
            int remainingWeight = maxWeight - currentWeight;
            totalProfit += items[i].profit * ((double)remainingWeight / items[i].weight);
            break;
        }
    }

    return totalProfit;
}

int main() {
    std::vector<int> weight = {1, 3, 5, 4, 1, 3, 2};
    std::vector<int> profit = {5, 10, 15, 7, 8, 9, 4};

    int maxWeight = 15;
    

    //Using Greedy Appraoch Only
    double result = fractionalKnapsack(weight, profit, maxWeight);
    std::cout << "Maximum profit using Fractional Knapsack: " << result << std::endl;

    return 0;
}
