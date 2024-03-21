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

// 106. 从中序与后序遍历序列构造二叉树
class Solution {
public:

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder, int &posti, int inbegin, int inend) {
        //   中序左右区间不对
        if (inbegin > inend)
            return nullptr;

        // 先创建结点 ，再构建它的左右子树
        TreeNode *root = new TreeNode(postorder[posti--]);

        // 中序序列划分左右区间 先构建右子树
        int rooti = inend;
        while (rooti >= inbegin) {
            if (inorder[rooti] != root->val)
                rooti--;
            else
                break;
        }

        // 再构建右左子树
        // [inbegin,rooti-1]  [rooti+1,inend]
        root->right = _buildTree(inorder, postorder, posti, rooti + 1, inend);
        root->left = _buildTree(inorder, postorder, posti, inbegin, rooti - 1);

        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        int posti = postorder.size() - 1;
        return _buildTree(inorder, postorder, posti, 0, inorder.size() - 1);
    }
};
