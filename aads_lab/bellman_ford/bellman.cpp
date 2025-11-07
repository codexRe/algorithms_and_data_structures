#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<vector<int>>* adj, int u, int v, int w) { // directed graph
        adj[u].push_back({v, w});
}

vector<int> bellman_ford(int V, vector<vector<int>> adj[], int S) {
    vector<int> dist(V, 1e9);
    dist[S] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (auto &edge : adj[u]) {
                int v = edge[0];
                int wt = edge[1];
                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }
    // Check for negative weight cycle (Nth relaxation)
    for (int u = 0; u < V; u++) {
        for (auto &edge : adj[u]) {
            int v = edge[0];
            int wt = edge[1];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return { -1 };     // if cycle detected
            }
        }
    }
    return dist;
}


int main() {
    int V = 4, S = 0;
    vector<vector<int>> adj[V];

    // addEdge(adj, 3, 2, 6);
    // addEdge(adj, 5, 3, 1);
    // addEdge(adj, 0, 1, 5);
    // addEdge(adj, 1, 5, -3);
    // addEdge(adj, 1, 2, -2);
    addEdge(adj, 0, 1, 2);
    addEdge(adj, 0, 3, 1);
    addEdge(adj, 1, 2, -1);
    addEdge(adj, 2, 0, -2);
    addEdge(adj, 3, 2, 3);

    vector<int> dist = bellman_ford(V, adj, S);

    if (dist.size() == 1 && dist[0] == -1) {
        cout << "\nNegative weight cycle detected\n";
    } else {
        cout << "\nDistances from source " << S << ": ";
        for (int d : dist) 
            cout << d << " ";
    }
    cout << endl;
}
