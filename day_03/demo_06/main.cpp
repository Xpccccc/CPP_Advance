/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/

// JZ36 二叉搜索树与双向链表
class Solution {
public:

    void InOrderConvert(TreeNode *cur, TreeNode *&pre) {
        if (cur == nullptr)
            return;

        InOrderConvert(cur->left, pre);

        // 关键
        cur->left = pre;

        if (pre)
            pre->right = cur;

        pre = cur;

        InOrderConvert(cur->right, pre);

    }

    TreeNode *Convert(TreeNode *pRootOfTree) {
        if (!pRootOfTree)
            return nullptr;
        TreeNode *pre = nullptr;
        InOrderConvert(pRootOfTree, pre);

        TreeNode *head = pRootOfTree;
        while (head->left) {
            head = head->left;
        }

        return head;
    }

};
