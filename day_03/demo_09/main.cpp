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

// 144. 二叉树的前序遍历
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        stack < TreeNode * > s;
        vector<int> v;

        TreeNode *cur = root;

        while (cur || !s.empty()) {

            while (cur) {
                v.push_back(cur->val);
                s.push(cur);
                cur = cur->left;
            }

            // 左子树已经走完
            TreeNode *top = s.top();
            s.pop();

            // 现在走右子树
            cur = top->right;
        }

        return v;
    }
};