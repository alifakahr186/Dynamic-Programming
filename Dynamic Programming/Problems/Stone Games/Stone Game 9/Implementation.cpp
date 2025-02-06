#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        // Step 1: Count stones by their modulo 3 value
        int count[3] = {0, 0, 0};
        for (int stone : stones) {
            count[stone % 3]++;
        }

        // Step 2: Analyze the number of Type-0 stones
        if (count[0] % 2 == 0) {
            // Case 1: Even Type-0 stones, winner depends on Type-1 and Type-2
            return count[1] >= 1 && count[2] >= 1;
        } else {
            // Case 2: Odd Type-0 stones, winner flips
            return abs(count[1] - count[2]) > 2;
        }
    }
};

int main() {
    Solution sol;

    // Example Test Case
    vector<int> stones = {12, 9, 5, 33, 6, 10, 55, 2, 71};

    // Using the function to determine the winner
    cout << "Result: " << (sol.stoneGameIX(stones) ? "Alice wins" : "Bob wins") << endl;

    return 0;
}

/*
//We write code in simple implementation
class Solution {
public:
    bool stoneGame(vector<int>& stones) {
        int n = stones.size();
        int sum = 0; // Total sum of the stones picked by Alice and Bob

        // Start the game
        bool turn = true; // Alice's turn = true, Bob's turn = false
        while (!stones.empty()) {
            // Let's remove the last stone for simplicity
            int stone = stones.back();
            stones.pop_back();

            // Alice's turn (turn = true)
            if (turn) {
                sum += stone;
                if (sum % 3 == 0) {
                    // If sum is divisible by 3, Alice loses
                    return false;
                }
            } else {
                // Bob's turn (turn = false)
                sum += stone;
                if (sum % 3 == 0) {
                    // If sum is divisible by 3, Bob loses
                    return true;
                }
            }

            // Switch turns
            turn = !turn;
        }

        // If no one lost and all stones are taken, Bob wins (no stones left)
        return false;
    }
};


*/