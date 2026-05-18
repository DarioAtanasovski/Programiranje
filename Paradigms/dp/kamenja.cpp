#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int M[n][m];
    int N[n][m];
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> M[i][j];
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (i==0)  N[i][j]=M[i][j];
            else {
                N[i][j]=N[i-1][j];
                if (j>0)    N[i][j]=max(N[i][j], N[i-1][j-1]);
                if (j<m-1)  N[i][j]=max(N[i][j], N[i-1][j+1]);
                N[i][j]+=M[i][j];
            }
        }
    }
    int rez=-1e8, m1=0;
    for (int j=0; j<m; j++) {
        if (rez<N[n-1][j]) {
            rez=N[n-1][j];
            m1=j;
        }
    }
    cout << rez << '\n';

    int p[n];
    p[n-1]=M[n-1][m1];

    for (int i=n-1; i>0; i--) {
        int best = N[i-1][m1];
        int m2 = m1;

        if (m1>0 && N[i-1][m1-1] > best) {
            best = N[i-1][m1-1];
            m2 = m1-1;
        }

        if (m1<m-1 && N[i-1][m1+1] > best) {
            best = N[i-1][m1+1];
            m2 = m1+1;
        }

        m1 = m2;
        p[i-1] = M[i-1][m1];
    }

    for (int i=0; i<n; i++) {
        cout << p[i] << ' ';
    }

    return 0;
}
