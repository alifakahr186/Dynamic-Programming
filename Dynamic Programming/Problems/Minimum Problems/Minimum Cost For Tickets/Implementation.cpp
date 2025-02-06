#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int MinTickets(int n, std::vector<int>& days, std::vector<int>& cost, int index) {
    if (index >= n) return 0;
    
    // 1-day pass
    int option1 = cost[0] + MinTickets(n, days, cost, index + 1);

    // 7-day pass
    int i;
    for (i = index; i < n && days[i] < days[index] + 7; i++);
    int option2 = cost[1] + MinTickets(n, days, cost, i);

    // 30-day pass
    for (i = index; i < n && days[i] < days[index] + 30; i++);
    int option3 = cost[2] + MinTickets(n, days, cost, i);

    return std::min(option1, std::min(option2, option3));
}

int MinTicketsMemo(int n, std::vector<int>& days, std::vector<int>& cost, int index, std::vector<int>& dp) {
    if (index >= n) return 0;

    if (dp[index] != -1) {
        return dp[index];
    }

    // 1-day pass
    int option1 = cost[0] + MinTicketsMemo(n, days, cost, index + 1, dp);

    // 7-day pass
    int i;
    for (i = index; i < n && days[i] < days[index] + 7; i++);
    int option2 = cost[1] + MinTicketsMemo(n, days, cost, i, dp);

    // 30-day pass
    for (i = index; i < n && days[i] < days[index] + 30; i++);
    int option3 = cost[2] + MinTicketsMemo(n, days, cost, i, dp);

    dp[index] = std::min(option1, std::min(option2, option3));

    return dp[index];
}

int MinTicketsTable(int n, std::vector<int>& days, std::vector<int>& cost) {
    std::vector<int> dp(n + 1, INT_MAX);
    dp[n] = 0;  // Base case

    for (int k = n - 1; k >= 0; k--) {
        // 1-day pass
        int option1 = cost[0] + dp[k + 1];

        // 7-day pass
        int i;
        for (i = k; i < n && days[i] < days[k] + 7; i++);
        int option2 = cost[1] + dp[i];

        // 30-day pass
        for (i = k; i < n && days[i] < days[k] + 30; i++);
        int option3 = cost[2] + dp[i];

        dp[k] = std::min(option1, std::min(option2, option3));
    }

    return dp[0];
}

int main() {
    std::vector<int> days = {1, 4, 6, 7, 8, 20};
    std::vector<int> cost = {2, 7, 15};
    int n = days.size();

    // Using Recursion 
    int result = MinTickets(n, days, cost, 0);
    std::cout << "Minimum Cost for Tickets Using Recursion: " << result << std::endl;

    // Using Memoization
    std::vector<int> dp(n + 1, -1);
    int resultMemo = MinTicketsMemo(n, days, cost, 0, dp);
    std::cout << "Minimum Cost for Tickets Using Memoization: " << resultMemo << std::endl;

    // Using Tabulation
    int resultTable = MinTicketsTable(n, days, cost);
    std::cout << "Minimum Cost for Tickets Using Tabulation: " << resultTable << std::endl;

    return 0;
}
