#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int       val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    vector<int> inorderTraversal(TreeNode *root) {
        if (!root) {
            return {};
        }

        stack<int> inorderNodeStack;

        buildInorderNodes(inorderNodeStack, root);

        vector<int> inorderNodes(inorderNodeStack.size(), INT_MAX);

        for (size_t i = 0; i < inorderNodes.size(); i++) {
            inorderNodes[i] = inorderNodeStack.top();
            inorderNodeStack.pop();
        }

        return inorderNodes;
    }

    void buildInorderNodes(stack<int> &inorderNodes, TreeNode *node) {
        if (node->right) {
            buildInorderNodes(inorderNodes, node->right);
        }

        inorderNodes.push(node->val);

        if (node->left) {
            buildInorderNodes(inorderNodes, node->left);
        }
    }
};