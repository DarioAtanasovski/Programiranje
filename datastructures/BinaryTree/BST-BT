#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

Node* insertBST(Node* root, int v) {
    if (!root) return new Node(v);
    if (v < root->val) root->left = insertBST(root->left, v);
    else root->right = insertBST(root->right, v);
    return root;
}

bool find(Node* root, int x) {
    if (!root) return false;
    if (root->val == x) return true;
    return find(root->left, x) || find(root->right, x);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}



void preorderNR(Node* root) {
    if (!root) return;
    vector<Node*> st;
    st.push_back(root);

    while (!st.empty()) {
        Node* cur = st.back();
        st.pop_back();
        cout << cur->val << " ";

        if (cur->right) st.push_back(cur->right);
        if (cur->left) st.push_back(cur->left);
    }
}

void inorderNR(Node* root) {
    vector<Node*> st;
    Node* cur = root;

    while (cur || !st.empty()) {
        while (cur) {
            st.push_back(cur);
            cur = cur->left;
        }

        cur = st.back();
        st.pop_back();

        cout << cur->val << " ";

        cur = cur->right;
    }
}

void postorderNR(Node* root) {
    if (!root) return;

    vector<Node*> st, out;
    st.push_back(root);

    while (!st.empty()) {
        Node* cur = st.back();
        st.pop_back();
        out.push_back(cur);

        if (cur->left) st.push_back(cur->left);
        if (cur->right) st.push_back(cur->right);
    }

    for (int i = out.size() - 1; i >= 0; i--)
        cout << out[i]->val << " ";
}

void bfs(Node* root) {
    if (!root) return;

    vector<Node*> q;
    q.push_back(root);

    int idx = 0;
    while (idx < q.size()) {
        Node* cur = q[idx++];
        cout << cur->val << " ";

        if (cur->left) q.push_back(cur->left);
        if (cur->right) q.push_back(cur->right);
    }
}

int sumTree(Node* root) {
    if (!root) return 0;
    return root->val + sumTree(root->left) + sumTree(root->right);
}


int main() {
    Node* root = nullptr;

    int a[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for (int x : a) root = insertBST(root, x);

    cout << "Preorder: "; preorder(root); cout << endl;
    cout << "Inorder: "; inorder(root); cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;

    cout << "Preorder NR: "; preorderNR(root); cout << endl;
    cout << "Inorder NR: "; inorderNR(root); cout << endl;
    cout << "Postorder NR: "; postorderNR(root); cout << endl;

    cout << "BFS: "; bfs(root); cout << endl;

    cout << "Find 7? " << (find(root,7) ? "YES" : "NO") << endl;
    cout << "Sum = " << sumTree(root) << endl;

    return 0;
}
