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

// 102. 二叉树的层序遍历
class Solution {
public:
    vector <vector<int>> levelOrder(TreeNode *root) {
        vector <vector<int>> vv;
        if (root == nullptr)
            return vv;

        queue < TreeNode * > q;
        q.push(root);

        while (!q.empty()) {
            vector<int> v; // 用来每次尾插vv
            int size = q.size();// 当前层的元素个数
            for (int i = 0; i < size; ++i) {
                TreeNode *cur = q.front();
                v.push_back(cur->val);
                q.pop();
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            vv.push_back(v);
        }

        return vv;
    }
};