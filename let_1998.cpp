#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent;
    UnionFind(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        UnionFind uf(mx + 1);

        vector<int> minPrime(mx + 1);
        for (int i = 2; i <= mx; i++) minPrime[i] = i;

        for (int i = 2; i * i <= mx; i++) {
            if (minPrime[i] == i) {
                for (int j = i * i; j <= mx; j += i) {
                    minPrime[j] = min(minPrime[j], i);
                }
            }
        }


        for (int x : nums) {
            int v = x;
            while (v > 1) {
                int p = minPrime[v];
                uf.unite(x, p);
                while (v % p == 0) v /= p;
            }
        }

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        for (int i = 0; i < n; i++) {
            if (uf.find(nums[i]) != uf.find(sorted[i]))
                return false;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    Solution s;
    cout << (s.gcdSort(nums) ? "true" : "false") << "\n";

    return 0;
}