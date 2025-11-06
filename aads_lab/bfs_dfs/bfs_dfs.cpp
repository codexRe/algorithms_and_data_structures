#include<bits/stdc++.h>
using namespace std;

void bfsConnected(vector<vector<int>>& adj, int src, vector<bool>& visited, vector<int>& res) {
    queue<int> q;
    visited[src] = true;
    q.push(src);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        res.push_back(curr);
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

vector<int> bfs(vector<vector<int>>& adj) { // find all graph components
    vector<bool> visited(adj.size(), false);
    vector<int> res;
    for (long unsigned int i = 0; i < adj.size(); i++)
        if (!visited[i])
            bfsConnected(adj, i, visited, res);
    return res;
}

void dfsRec(vector<vector<int>> &adj, vector<bool> &visited, int s, vector<int> &res) {
    visited[s] = true;
    res.push_back(s);
    for (int i : adj[s])
        if (visited[i] == false)
            dfsRec(adj, visited, i, res);
}

vector<int> dfs(vector<vector<int>> &adj) {
    vector<bool> visited(adj.size(), false);
    vector<int> res;
    for (long unsigned int i = 0; i < adj.size(); i++) {
        if (visited[i] == false) {
            dfsRec(adj, visited, i, res);
        }
    }
    return res;
}

void addEdge(vector<vector<int>>& adj, int u, int v) { // undirected graph
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 5);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 5);

    cout << "\n\nBFS Traversal: ";
    vector<int> bfs_traversal = bfs(adj);
    for (int i : bfs_traversal)
        cout << i << " ";
    
    cout << "\n\nDFS Traversal: ";
    vector<int> dfs_traversal = dfs(adj); 
    for (int i : dfs_traversal)
        cout << i << " ";
    cout << endl ;
}