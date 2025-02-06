#include <vector>
#include <iostream>

// Structure to represent an item with weight, profit, and index
struct Item {
    int weight;
    int profit;
    int index;
};

// Function to compare two items based on their profit-to-weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}

int Partition(std::vector<Item>& items, int low, int high) {
    Item pivot = items[low];
    int start = low;
    int end = high;

    while (start < end) {
        while ((double)items[start].profit / items[start].weight >= (double)pivot.profit / pivot.weight && start < high) {
            start++;
        }
        while ((double)items[end].profit / items[end].weight < (double)pivot.profit / pivot.weight) {
            end--;
        }
        if (start < end) {
            std::swap(items[start], items[end]);
        }
    }
    std::swap(items[low], items[end]);
    return end;
}

void QuickSort(std::vector<Item>& items, int low, int high) {
    if (low < high) {
        int partitionIndex = Partition(items, low, high);
        QuickSort(items, low, partitionIndex - 1);
        QuickSort(items, partitionIndex + 1, high);
    }
}

// Knapsack function using custom QuickSort
double Fractionalknapsack(const std::vector<int>& weight, const std::vector<int>& profit, int maxWeight, int itemCount) {
    std::vector<Item> items(itemCount);

    for (int i = 0; i < itemCount; ++i) {
        items[i] = {weight[i], profit[i], i};
    }

    // Basically we change the in-built sort function into proper logic
    // Sort items by profit-to-weight ratio using custom QuickSort
    QuickSort(items, 0, itemCount - 1);

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
    int itemCount = weight.size();

    //Using Greedy Appraoch Only
    double result = Fractionalknapsack(weight, profit, maxWeight, itemCount);
    std::cout << "Maximum profit using custom QuickSort: " << result << std::endl;

    return 0;
}
