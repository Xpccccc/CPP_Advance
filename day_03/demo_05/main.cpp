/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//  236. 二叉树的最近公共祖先
class Solution {
public:

    bool GetPath(TreeNode *root, TreeNode *cur, stack<TreeNode *> &v) {

        if (root == nullptr)
            return false;

        v.push(root);

        if (cur == root)
            return true;

        // 去左边找
        if (GetPath(root->left, cur, v))
            return true;

        // 去右边找
        if (GetPath(root->right, cur, v))
            return true;

        // 左右都没找到
        v.pop();
        return false;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {

        stack < TreeNode * > sp;
        stack < TreeNode * > sq;
        GetPath(root, p, sp);
        GetPath(root, q, sq);

        // 两个路径找交点
        while (sp.size() != sq.size()) {
            if (sp.size() > sq.size())
                sp.pop();
            else
                sq.pop();
        }

        while (sp.top() != sq.top()) {
            sp.pop();
            sq.pop();
        }

        return sp.top();
    }
};


//// 另一种解法
//class Solution {
//public:
//    bool IsInTree(TreeNode *root, TreeNode *cur) {
//        if (root == nullptr)
//            return false;
//        return root == cur || IsInTree(root->left, cur) || IsInTree(root->right, cur);
//    }
//
//    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
//
//        if (root == nullptr)
//            return nullptr;
//
//        if (p == root || q == root)
//            return root;
//
//        bool pInLeft, pInRight, qInLeft, qInRight;
//
//        pInLeft = IsInTree(root->left, p);
//        pInRight = !pInLeft; // p肯定在左右子树中的一个
//
//        qInLeft = IsInTree(root->left, q);
//        qInRight = !qInLeft; // q肯定在左右子树中的一个
//
//        if ((pInLeft && qInRight) || (pInRight && qInLeft)) {
//            // 左右子树各一个，那么当前结点就是公共结点
//            return root;
//        } else if ((pInLeft && qInLeft)) {
//            return lowestCommonAncestor(root->left, p, q);// 去左子树找
//        } else
//            return lowestCommonAncestor(root->right, p, q);// 去右子树找
//    }
//};