#include <bits/stdc++.h>
using namespace std;

struct AVLNode {
    int key;
    string value;
    AVLNode *left;
    AVLNode *right;
    int height;
    AVLNode(int k, const string &v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

int height(AVLNode* n) {
    if (n != nullptr)
        return n->height;
    else
        return 0;

}

int balanceFactor(AVLNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

void updateHeight(AVLNode* n) {
    if (n) n->height = 1 + max(height(n->left), height(n->right));
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* avlInsert(AVLNode* node, int key, const string &value) {
    if (!node) return new AVLNode(key, value);
    if (key < node->key)
        node->left = avlInsert(node->left, key, value);
    else if (key > node->key)
        node->right = avlInsert(node->right, key, value);
    else {
        node->value = value;
        return node;
    }

    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf > 1 && key < node->left->key)
        return rotateRight(node);
    if (bf < -1 && key > node->right->key)
        return rotateLeft(node);
    if (bf > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left) current = current->left;
    return current;
}

AVLNode* avlRemove(AVLNode* root, int key) {
    if (!root) return root;
    if (key < root->key) root->left = avlRemove(root->left, key);
    else if (key > root->key) root->right = avlRemove(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->value = temp->value;
            root->right = avlRemove(root->right, temp->key);
        }
    }
    if (!root)

    updateHeight(root);
    int bf = balanceFactor(root);

    if (bf > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);
    if (bf > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bf < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);
    if (bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

AVLNode* avlFind(AVLNode* root, int key) {
    while (root) {
        if (key == root->key) return root;
        root = (key < root->key) ? root->left : root->right;
    }
    return nullptr;
}

void avlInorder(AVLNode* root) {
    if (!root) return;
    avlInorder(root->left);
    cout << "(" << root->key << ", " << root->value << ") ";
    avlInorder(root->right);
}
class CBHT {
    vector<list<string>> table;
    size_t m;
public:
    enum HashChoice { BY_LENGTH = 1, BY_SUM = 2, BY_FIRST = 3, BY_FIRST2 = 4 };

    CBHT(size_t m_) : table(m_), m(m_) {}

    static string normalize(const string &s) {
        string t;
        t.reserve(s.size());
        for (char c : s) t.push_back(tolower((unsigned char)c));
        return t;
    }

    size_t hashByLength(const string &s) const {
        return s.size() % m;
    }

    size_t hashBySumLetters(const string &s) const {
        string t = normalize(s);
        long sum = 0;
        for (char c : t) if (isalpha((unsigned char)c)) sum += (c - 'a' + 1);
        return (size_t)(sum % (long)m);
    }

    size_t hashByFirst(const string &s) const {
        string t = normalize(s);
        for (char c : t) if (isalpha((unsigned char)c)) {
            return (size_t)((c - 'a') % (int)m);
        }
        return 0;
    }

    size_t hashByFirst2(const string &s) const {
        string t = normalize(s);
        int val = 0;
        int count = 0;
        for (char c : t) {
            if (isalpha((unsigned char)c)) {
                val = val * 26 + (c - 'a');
                count++;
                if (count == 2) break;
            }
        }
        return (size_t)( (val >= 0 ? val : 0) % (int)m );
    }

    size_t chooseHash(const string &s, HashChoice choice) const {
        switch (choice) {
            case BY_LENGTH: return hashByLength(s);
            case BY_SUM:    return hashBySumLetters(s);
            case BY_FIRST:  return hashByFirst(s);
            case BY_FIRST2: return hashByFirst2(s);
            default: return hashByLength(s);
        }
    }

    void insert(const string &s, HashChoice choice) {
        size_t idx = chooseHash(s, choice);
        for (const auto &x : table[idx]) if (x == s) return;
        table[idx].push_front(s);
    }

    bool remove(const string &s, HashChoice choice) {
        size_t idx = chooseHash(s, choice);
        auto &lst = table[idx];
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            if (*it == s) {
                lst.erase(it);
                return true;
            }
        }
        return false;
    }

    bool contains(const string &s, HashChoice choice) const {
        size_t idx = chooseHash(s, choice);
        for (const auto &x : table[idx]) if (x == s) return true;
        return false;
    }

    void displayStats() const {
        cout << "CBHT stats (m=" << m << "):\n";
        size_t nonEmpty = 0;
        size_t maxChain = 0;
        size_t total = 0;
        for (size_t i = 0; i < m; ++i) {
            size_t sz = table[i].size();
            if (sz > 0) nonEmpty++;
            maxChain = max(maxChain, sz);
            total += sz;
        }
        cout << "  total entries: " << total << "\n";
        cout << "  non-empty buckets: " << nonEmpty << "\n";
        cout << "  max chain length: " << maxChain << "\n";
        cout << "  average chain length (non-empty only): " << (nonEmpty ? (double)total / nonEmpty : 0.0) << "\n";
    }

    void printBuckets() const {
        for (size_t i = 0; i < m; ++i) {
            cout << "[" << i << "]:";
            for (const auto &s : table[i]) cout << " " << s;
            cout << "\n";
        }
    }
};

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "AVL demo:\n";
    AVLNode* root = nullptr;
    vector<pair<int,string>> pairs = {
        {30,"trinta"}, {20,"vinti"}, {40,"cuarenta"}, {10,"diez"}, {25,"veinticinco"},
        {35,"treintaicinco"}, {50,"cincuenta"}, {5,"cinco"}, {15,"quince"}
    };
    for (auto &p : pairs) root = avlInsert(root, p.first, p.second);

    cout << "Inorder (key, value): ";
    avlInorder(root);
    cout << "\n";

    cout << "Insert 22 and 27 to force rotations\n";
    root = avlInsert(root, 22, "veintidos");
    root = avlInsert(root, 27, "veintisiete");
    cout << "Inorder after insertions: ";
    avlInorder(root);
    cout << "\n";

    cout << "Remove key 20\n";
    root = avlRemove(root, 20);
    cout << "Inorder after remove: ";
    avlInorder(root);
    cout << "\n\n";

    cout << "CBHT demo:\n";
    size_t tableSize = 1031;
    CBHT ht(tableSize);
    CBHT::HashChoice choice = CBHT::BY_LENGTH;
    if (argc >= 2) {
        int c = atoi(argv[1]);
        if (c >= 1 && c <= 4) choice = static_cast<CBHT::HashChoice>(c);
    }
    cout << "Using hash function: ";
    switch (choice) {
        case CBHT::BY_LENGTH: cout << "by length\n"; break;
        case CBHT::BY_SUM:    cout << "by sum of letters\n"; break;
        case CBHT::BY_FIRST:  cout << "by first letter\n"; break;
        case CBHT::BY_FIRST2: cout << "by first two letters\n"; break;
    }

    vector<string> words;
    ifstream fin("common1000.txt");
    if (fin) {
        string w;
        while (fin >> w) {
            if (!w.empty()) words.push_back(w);
        }
        fin.close();
        cout << "Loaded " << words.size() << " words from common1000.txt\n";
    } else {
        words = {"the","be","to","of","and","a","in","that","have","I",
                 "it","for","not","on","with","he","as","you","do","at"};
        cout << "common1000.txt not found — using sample " << words.size() << " words\n";
    }

    for (const auto &w : words) ht.insert(w, choice);

    ht.displayStats();

    vector<string> test = {"the", "and", "unknownword", "I"};
    for (const auto &t : test) {
        cout << "Contains \"" << t << "\"? " << (ht.contains(t, choice) ? "yes" : "no") << "\n";
    }
    cout << "Removing \"and\"...\n";
    ht.remove("and", choice);
    cout << "Contains \"and\"? " << (ht.contains("and", choice) ? "yes" : "no") << "\n";
    cout << "\nDone.\n";
    return 0;
}
