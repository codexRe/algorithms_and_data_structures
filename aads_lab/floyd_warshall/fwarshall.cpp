#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void floyd_warshall(vector<vector<int>>& dist) {
    int n = dist.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == INF) continue;		     // skip if i->k unreachable
            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == INF) continue;	                // skip if k->j unreachable
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter |V| = n, followed by n vectors of size = n (use '-1' for ∞): \n";
    cin >> n;		// number of vertices
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x;
            cin >> x;
            if (x == -1) matrix[i][j] = INF;
            else matrix[i][j] = x;
        }
    }

    for (int i = 0; i < n; ++i) 
        matrix[i][i] = min(matrix[i][i], 0);

    floyd_warshall(matrix);

    cout << "\n Final distance adj matrix: \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == INF) cout << "∞  ";
            else cout << matrix[i][j] << "  ";
        }
        cout << "\n";
    }
    cout << "\n";
    return 0;
}