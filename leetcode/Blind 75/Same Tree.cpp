// https://leetcode.com/problems/same-tree
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        bool isSame = true;
        std::function<bool(TreeNode*, TreeNode*)> AreNodesSame = [&](TreeNode* p, TreeNode* q) {
            if (p == nullptr && q != nullptr)
                return false;
            if (p != nullptr && q == nullptr)
                return false;
            if (p == nullptr && q == nullptr)
                return true;
            return p->val == q->val;
        };
        std::function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* p, TreeNode* q) {
            if (!AreNodesSame(p, q)) {
                isSame = false;
                return;
            }
            if (p != nullptr) {
                dfs(p->left, q->left);
                dfs(p->right, q->right);
            }
        };
        dfs(p, q);
        return isSame;
    }
};