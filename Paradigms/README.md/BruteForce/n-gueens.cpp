#include <iostream>
#include <vector>
using namespace std;

int ABS(int x) {
    if (x < 0) return -x;
    return x;
}

void swapInt(int &a, int &b) {
    int t = a; a = b; b = t;
}

void reversePart(vector<int>& a, int l, int r) {
    while (l < r) {
        swapInt(a[l], a[r]);
        l++; r--;
    }
}


bool nextPermutation(vector<int>& a) {
    int n = (int)a.size();


    int i = n - 2;
    while (i >= 0 && a[i] >= a[i + 1]) i--;
    if (i < 0) return false;


    int j = n - 1;
    while (a[j] <= a[i]) j--;


    swapInt(a[i], a[j]);


    reversePart(a, i + 1, n - 1);

    return true;
}

long long countNQueensBruteForce(int n) {
    vector<int> p(n);


    for (int i = 0; i < n; i++) p[i] = i;

    long long cnt = 0;

    while (true) {
        bool ok = true;


        for (int i = 0; i < n && ok; i++) {
            for (int j = i + 1; j < n; j++) {
                if (ABS(i - j) == ABS(p[i] - p[j])) {
                    ok = false;
                    break;
                }
            }
        }

        if (ok) cnt++;


        if (!nextPermutation(p)) break;
    }

    return cnt;
}

int main() {
    int n;
    cin >> n;
    cout << countNQueensBruteForce(n) << "\n";
    return 0;
}
