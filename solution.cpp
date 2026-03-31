#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    unordered_map<int, int> depth_map;   // node_val -> depth
    unordered_map<int, int> parent_map;  // node_val -> parent_val

    // Build tree from extended preorder traversal
    int idx;
    TreeNode* buildTree(vector<int>& preorder) {
        if (idx >= preorder.size() || preorder[idx] == -1) {
            idx++;
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[idx++]);
        root->left = buildTree(preorder);
        root->right = buildTree(preorder);
        return root;
    }

    // DFS to find depth and parent for each node
    void dfs(TreeNode* node, int depth, int parent) {
        if (!node) return;

        depth_map[node->val] = depth;
        parent_map[node->val] = parent;

        dfs(node->left, depth + 1, node->val);
        dfs(node->right, depth + 1, node->val);
    }

public:
    bool areCousins(TreeNode* root, int x, int y) {
        depth_map.clear();
        parent_map.clear();

        dfs(root, 0, -1);

        // Check if both nodes exist
        if (depth_map.find(x) == depth_map.end() ||
            depth_map.find(y) == depth_map.end()) {
            return false;
        }

        // Cousins: same depth but different parents
        return depth_map[x] == depth_map[y] &&
               parent_map[x] != parent_map[y];
    }

    TreeNode* buildTreeFromPreorder(vector<int>& preorder) {
        idx = 0;
        return buildTree(preorder);
    }
};

int main() {
    int q;
    cin >> q;

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    vector<int> preorder;
    int val;
    while (cin >> val) {
        preorder.push_back(val);
    }

    Solution sol;
    TreeNode* root = sol.buildTreeFromPreorder(preorder);

    for (const auto& query : queries) {
        int result = sol.areCousins(root, query.first, query.second) ? 1 : 0;
        cout << result << endl;
    }

    return 0;
}
