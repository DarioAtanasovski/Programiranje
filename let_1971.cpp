#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    vector<int> parent, size;

    UnionFind(int n) {
        parent.resize(n);
        size.assign(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        UnionFind uf(n);
        for (auto &e : edges) uf.unite(e[0], e[1]);
        return uf.find(source) == uf.find(destination);
    }
};

int main() {
    int n = 6;
    vector<vector<int>> edges = {
        {0,1}, {0,2}, {3,5}, {5,4}, {4,3}
    };
    int source = 0;
    int destination = 5;

    Solution sol;
    bool result = sol.validPath(n, edges, source, destination);

    cout << (result ? "True" : "False") << endl;
    return 0;
}
