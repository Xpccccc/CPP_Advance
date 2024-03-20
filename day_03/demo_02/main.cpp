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

// 606. 根据二叉树创建字符串

class Solution {
public:


    string tree2str(TreeNode *root) {
        if (root == nullptr)
            return "";

        string str = to_string(root->val);

        // 要加括号：1、当前结点的左不空,左为空右不空也要加
        //         2、当前结点的右不空

        // 往左子树找
        if (root->left || root->right) {
            str += '(';
            str += tree2str(root->left);
            str += ')';
        }

        // 往右子树找
        if (root->right) {
            str += '(';
            str += tree2str(root->right);
            str += ')';
        }

        return str;
    }
};