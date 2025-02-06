#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int solve(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<pair<int, int>> v(n);

        // Combine the indices and sorting key (A[i] + B[i])
        for (int i = 0; i < n; i++) {
            v[i] = {A[i] + B[i], i};
        }

        // Sort by the sum of Alice and Bob's values in descending order
        sort(v.rbegin(), v.rend());

        int f = 1; // 1 for Alice's turn, 0 for Bob's turn
        int a = 0, b = 0;

        // Alternate turns picking stones
        for (auto x : v) {
            int idx = x.second; // Get the original index
            if (f == 1) { 
                a += A[idx]; // Alice picks
            } else {
                b += B[idx]; // Bob picks
            }
            f = 1 - f; // Switch turns
        }

        // Determine the result
        if (a > b) return 1;  // Alice wins
        if (a == b) return 0; // Draw
        return -1;            // Bob wins
    }

    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        return solve(aliceValues, bobValues);
    }
};

int main() {
    Solution sol;
    vector<int> aliceValues = {1, 2, 3};
    vector<int> bobValues = {3, 2, 1};

    int result = sol.stoneGameVI(aliceValues, bobValues);
    
    if (result == 1) {
        cout << "Alice wins the game!" << endl;
    } else if (result == -1) {
        cout << "Bob wins the game!" << endl;
    } else {
        cout << "The game is a draw!" << endl;
    }

    return 0;
}
