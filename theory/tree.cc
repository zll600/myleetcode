#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};

void PreOrderRecur(TreeNode *root) {
    if (root == nullptr) {
        return;
    }

    cout << root->val << endl;
    PreOrderRecur(root->left);
    PreOrderRecur(root->right);
}

void PreOrderIter(TreeNode *root) {
    stack<TreeNode*> sta;
    sta.push(root);

    while (!sta.empty()) {
        TreeNode *node = sta.top();
        sta.pop();

        cout << node->val << endl;

        if (node->right != nullptr) {
            sta.push(node->right);
        }
        if (node->left != nullptr) {
            sta.push(node->left);
        }
    }
}

void InOrderRecur(TreeNode *root) {
    if (root == nullptr) {
        return;
    }

    InOrderRecur(root->left);
    cout << root->val << endl;
    InOrderRecur(root->right);
}

void InOrderIter(TreeNode *root) {
    stack<TreeNode*> sta;
    
    while (!sta.empty() || root != nullptr) {
        if (root != nullptr) {
            sta.push(root);
            root = root->left;
        } else {
            root = sta.top();
            sta.pop();
            cout << root->val << endl;
            root = root->right;
        }
    }
}

void PostOrderRecur(TreeNode *root) {
    if (root == nullptr) {
        return;
    }

    PostOrderRecur(root->left);
    PostOrderRecur(root->right);
    cout << root->val << endl;
}

void PostOrderIter(TreeNode *root) {
    stack<TreeNode*> input;
    stack<TreeNode*> output;

    input.push(root);
    while (!input.empty()) {
        TreeNode *node = input.top();
        input.pop();
        
        output.push(node);

        if (node->left != nullptr) {
            input.push(node->left);
        }
        if (node->right != nullptr) {
            input.push(node->right);
        }
    }

    while (!output.empty()) {
        cout << output.top()->val << endl;
        output.pop();
    }
}

void PostOrderIter2(TreeNode *root) {
    stack<TreeNode*> sta;
    sta.push(root);
    TreeNode *h = root;
    TreeNode *c = nullptr;

    while (!sta.empty()) {
        c = sta.top();

        if (c->left != nullptr && h != c->left && h != c->right) {
            sta.push(c);
        } else if (c->right != nullptr && h != c->right) {
            sta.push(c);
        } else {
            sta.pop();
            cout << c->val << endl;
            h = c;
        }
    }
}
