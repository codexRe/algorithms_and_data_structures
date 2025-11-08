#include <bits/stdc++.h>
using namespace std;

bool bfs(vector<vector<int>>& capacity, int source, int sink, vector<int>& parent) {
    int n = capacity.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (!visited[v] && capacity[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink) return true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>>& capacity, int source, int sink) {
    int n = capacity.size();
    vector<int> parent(n);
    int maxFlow = 0;
    
    while (bfs(capacity, source, sink, parent)) {
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    int V = 6;
    int source = 0, sink = 5;
    vector<vector<int>> capacity(V, vector<int>(V, 0));

    capacity[0][1] = 16;
    capacity[0][2] = 13;
    capacity[1][2] = 10;
    capacity[1][3] = 12;
    capacity[2][1] = 4;
    capacity[2][4] = 14;
    capacity[3][2] = 9;
    capacity[3][5] = 20;
    capacity[4][3] = 7;
    capacity[4][5] = 4;

    int maxFlow = fordFulkerson(capacity, source, sink);
    cout << "Maximum Flow: " << maxFlow << endl;
    
    return 0;
}