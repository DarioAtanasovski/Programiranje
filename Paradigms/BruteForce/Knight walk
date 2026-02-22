#include <iostream>
#include <vector>
using namespace std;

const int N = 8;
int board[N][N];

int dr[8] = {-2,-2,-1,-1, 1, 1, 2, 2};
int dc[8] = {-1, 1,-2, 2,-2, 2,-1, 1};

struct Cell {
    int r, c;
};

bool inside(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
}

int onwardDegree(int r, int c) {
    int cnt = 0;
    for (int k = 0; k < 8; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (inside(nr, nc) && board[nr][nc] == 0) cnt++;
    }
    return cnt;
}

void sortCandidates(vector<Cell>& cand) {
    int m = (int)cand.size();
    for (int i = 0; i < m; i++) {
        int best = i;
        int bestDeg = onwardDegree(cand[i].r, cand[i].c);

        for (int j = i + 1; j < m; j++) {
            int d = onwardDegree(cand[j].r, cand[j].c);
            if (d < bestDeg) {
                bestDeg = d;
                best = j;
            }
        }
        if (best != i) {
            Cell tmp = cand[i];
            cand[i] = cand[best];
            cand[best] = tmp;
        }
    }
}

bool dfs(int r, int c, int step) {
    board[r][c] = step;
    if (step == N * N) return true;

    vector<Cell> cand;
    for (int k = 0; k < 8; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (inside(nr, nc) && board[nr][nc] == 0) {
            cand.push_back(Cell{nr, nc});
        }
    }

    sortCandidates(cand);

    for (int i = 0; i < (int)cand.size(); i++) {
        int nr = cand[i].r, nc = cand[i].c;
        if (dfs(nr, nc, step + 1)) return true;
    }

    board[r][c] = 0;
    return false;
}

int main() {
    int row, col; 
    cin >> row >> col;

  
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    int sr = row - 1, sc = col - 1;
    if (!inside(sr, sc)) {
        cout << "Nevalidni koordinati.\n";
        return 0;
    }

    if (!dfs(sr, sc, 1)) {
        cout << "Nema najdeno tura.\n";
        return 0;
    }

   
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int v = board[i][j];
            if (v < 10) cout << ' ';   
            cout << v;
            if (j != N - 1) cout << ' ';
        }
        cout << "\n";
    }

    return 0;
}
