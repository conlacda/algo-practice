// https://leetcode.com/problems/maximum-depth-of-binary-tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        int ans = 1;
        std::function<void(TreeNode*, int)> dfs = [&](TreeNode* root, int curDep) {
            ans = max(ans, curDep);
            if (root->left != nullptr) {
                dfs(root->left, curDep+1);
            }
            if (root->right != nullptr) {
                dfs(root->right, curDep+1);
            }
        };
        if (root == nullptr)
            return 0;
        dfs(root, 1);
        return ans;
    }
};