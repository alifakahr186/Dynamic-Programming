#include <iostream>
#include <vector>
#include <algorithm> // For std::max
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> solve(TreeNode* root) {
        if (root == nullptr) return {0, 0}; // Base case: return 0 for both include and exclude

        vector<int> left = solve(root->left);
        vector<int> right = solve(root->right);

        int incl = root->val + left[1] + right[1]; 

        int excl = max(left[0], left[1]) + max(right[0], right[1]); 

        return {incl, excl}; 
    }

    int houseRob(TreeNode* root) {
        vector<int> result = solve(root);
        return max(result[0], result[1]);
    }

    vector<int> solveMemoHelper(TreeNode* root, vector<int>& dp) {
        if (root == nullptr) return {0, 0}; 

        if (dp[root->val + 10000] != -1) { 
            return {dp[root->val + 10000], dp[root->val + 10000 + 1]};
        }

        vector<int> left = solveMemoHelper(root->left, dp);
        vector<int> right = solveMemoHelper(root->right, dp);

        int incl = root->val + left[1] + right[1]; 
        int excl = max(left[0], left[1]) + max(right[0], right[1]);

        dp[root->val + 10000] = incl;   
        dp[root->val + 10000 + 1] = excl; 

        return {incl, excl}; // Return both results
    }

    int solveMemo(TreeNode* root) {
        vector<int> dp(20000, -1); 
        vector<int> result = solveMemoHelper(root, dp);
        return max(result[0], result[1]);
    }

    int solveTab(TreeNode* root) {
        if (!root) return 0; 

        vector<TreeNode*> nodes;
        vector<int> values;
        inorderTraversal(root, nodes, values);

        int size = values.size();
        vector<int> dp(size, 0);

        dp[0] = values[0]; 
        if (size > 1) {
            dp[1] = max(values[0], values[1]); 
        }

        for (int i = 2; i < size; i++) {
            dp[i] = max(dp[i - 1], values[i] + dp[i - 2]);
        }

        return dp[size - 1];
    }

    void inorderTraversal(TreeNode* root, vector<TreeNode*>& nodes, vector<int>& values) {
        if (!root) return;

        inorderTraversal(root->left, nodes, values); 
        nodes.push_back(root); 
        values.push_back(root->val); 
        inorderTraversal(root->right, nodes, values);
    }

    int houseRobber(TreeNode* root) {
        return solveMemo(root);
    }

};

int main() {
    // Example usage
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);

    Solution solution;
    int resultRec = solution.houseRob(root);
    cout << "Max money that can be robbed using Recursion: " << resultRec << endl;

    int resultMemo = solution.houseRobber(root);
    cout << "Max money that can be robbed using Memoization: " << resultMemo << endl;

    int resultTab = solution.solveTab(root);
    cout << "Max money that can be robbed using Tabulation: " << resultTab << endl;

    // Clean up the tree (to prevent memory leaks)
    delete root->left->right; // delete node with value 3 (right child of left node)
    delete root->left; // delete node with value 2
    delete root->right->right; // delete node with value 1
    delete root->right; // delete node with value 3
    delete root; // delete root node with value 3

    return 0;
}
