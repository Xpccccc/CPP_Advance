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

// 145. 二叉树的后序遍历
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        stack < TreeNode * > s;
        vector<int> v;

        TreeNode *cur = root;
        TreeNode *pre = nullptr;

        while (cur || !s.empty()) {

            while (cur) {
                s.push(cur);
                cur = cur->left;
            }

            // 左子树已经走完
            TreeNode *top = s.top();

            // 当前结点的右子树为空，可以访问当前结点
            // 或者右子树不空，但是已经访问过，也可以访问当前结点
            // 否则去右子树继续访问
            if (top->right == nullptr || top->right == pre) {
                v.push_back(top->val);
                s.pop();
                pre = top;
            } else {
                // 现在走右子树
                cur = top->right;
            }
        }

        return v;
    }
};