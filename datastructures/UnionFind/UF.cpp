#include <bits/stdc++.h>
using namespace std;

struct UFBasic {
    int n;
    vector<int> parent;
    UFBasic(int n): n(n), parent(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        parent[rb] = ra;
    }
};

struct UFSize {
    int n;
    vector<int> parent, sz;
    UFSize(int n): n(n), parent(n), sz(n,1) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (sz[ra] < sz[rb]) swap(ra, rb);
        parent[rb] = ra;
        sz[ra] += sz[rb];
    }
};

struct UFHeight {
    int n;
    vector<int> parent, height;
    UFHeight(int n): n(n), parent(n), height(n,0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (height[ra] < height[rb]) {
            parent[ra] = rb;
        } else if (height[rb] < height[ra]) {
            parent[rb] = ra;
        } else {
            parent[rb] = ra;
            height[ra] += 1;
        }
    }
};

struct UFRankPC {
    int n;
    vector<int> parent, rankv;
    UFRankPC(int n): n(n), parent(n), rankv(n,0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (rankv[ra] < rankv[rb]) parent[ra] = rb;
        else if (rankv[rb] < rankv[ra]) parent[rb] = ra;
        else {
            parent[rb] = ra;
            rankv[ra] += 1;
        }
    }
};

inline int idx(int r, int c, int cols) {
    return r * cols + c;
}

template <typename UF>
int closedIslandUsingUF(const vector<vector<int>>& grid) {
    int R = grid.size();
    if (R == 0) return 0;
    int C = grid[0].size();
    int N = R * C;
    UF uf(N);

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] != 0) continue;
            int id = idx(r,c,C);
            // right
            if (c+1 < C && grid[r][c+1] == 0) uf.unite(id, idx(r,c+1,C));
            // down
            if (r+1 < R && grid[r+1][c] == 0) uf.unite(id, idx(r+1,c,C));
        }
    }
    vector<char> touches(N, 0);
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] != 0) continue;
            if (r == 0 || r == R-1 || c == 0 || c == C-1) {
                int root = uf.find(idx(r,c,C));
                touches[root] = 1;
            }
        }
    }

    unordered_set<int> counted;
    int ans = 0;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] != 0) continue;
            int root = uf.find(idx(r,c,C));
            if (counted.count(root)) continue;
            counted.insert(root);
            if (!touches[root]) ++ans;
        }
    }
    return ans;
}

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        return closedIslandUsingUF<UFRankPC>(grid);
    }

    // If you want to test other UF variants:
    int closedIsland_basic(vector<vector<int>>& grid) {
        return closedIslandUsingUF<UFBasic>(grid);
    }
    int closedIsland_size(vector<vector<int>>& grid) {
        return closedIslandUsingUF<UFSize>(grid);
    }
    int closedIsland_height(vector<vector<int>>& grid) {
        return closedIslandUsingUF<UFHeight>(grid);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> g = {
        {1,1,1,1,1,1,1,0},
        {1,0,0,0,0,1,1,0},
        {1,0,1,0,1,1,1,0},
        {1,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,0}
    };
    cout << "closedIsland (rank+PC) = " << sol.closedIsland(g) << "\n";
    cout << "closedIsland (basic)   = " << sol.closedIsland_basic(g) << "\n";
    cout << "closedIsland (size)    = " << sol.closedIsland_size(g) << "\n";
    cout << "closedIsland (height)  = " << sol.closedIsland_height(g) << "\n";
    return 0;
}
