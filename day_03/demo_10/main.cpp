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

// 94. 二叉树的中序遍历
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        stack < TreeNode * > s;
        vector<int> v;

        TreeNode *cur = root;

        while (cur || !s.empty()) {

            while (cur) {
                s.push(cur);
                cur = cur->left;
            }

            // 左子树已经走完
            TreeNode *top = s.top();
            s.pop();

            // 出栈的时候访问
            v.push_back(top->val);
            // 现在走右子树
            cur = top->right;
        }

        return v;
    }
};