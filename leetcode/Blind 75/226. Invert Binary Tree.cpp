// https://leetcode.com/problems/invert-binary-tree
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
    TreeNode* invertTree(TreeNode* root) {
        std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
            if (node != nullptr) {
                swap(node->left, node->right);
                dfs(node->left);
                dfs(node->right);
            }
        };
        dfs(root);
        return root;
    }
};