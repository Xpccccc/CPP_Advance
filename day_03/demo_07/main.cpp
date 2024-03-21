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

// 105. 从前序与中序遍历序列构造二叉树
class Solution {
public:

    TreeNode *_buildTree(vector<int> &preorder, vector<int> &inorder, int &prei, int inbegin, int inend) {
        //   中序左右区间不对
        if (inbegin > inend)
            return nullptr;

        // 先创建结点 ，再构建它的左右子树
        TreeNode *root = new TreeNode(preorder[prei++]);

        // 中序序列划分左右区间
        int rooti = inbegin;
        while (rooti <= inend) {
            if (inorder[rooti] != root->val)
                rooti++;
            else
                break;
        }

        // 再构建左右子树
        // [inbegin,rooti-1]  [rooti+1,inend]
        root->left = _buildTree(preorder, inorder, prei, inbegin, rooti - 1);
        root->right = _buildTree(preorder, inorder, prei, rooti + 1, inend);

        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int prei = 0;
        return _buildTree(preorder, inorder, prei, 0, inorder.size() - 1);
    }
};