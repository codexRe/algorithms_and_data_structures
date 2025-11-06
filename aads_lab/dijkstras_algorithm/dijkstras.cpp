#include<bits/stdc++.h>
using namespace std;

void addEdge(vector<vector<int>>* adj, int u, int v, int w) { // directed graph
        adj[u].push_back({v, w});
    }

vector <int> dijkstra(int V, vector<vector<int>> adj[], int S){
    // Create a set ds for storing the nodes as a pair {dist,node}
    // where dist is the distance from source to the node.
    // set stores the nodes in ascending order of the distances 
    set<pair<int,int>> shortest; 
    // Initialising dist list with a large number to
    // indicate the nodes are unvisited initially.
    // This list contains distance from source to the nodes.
    vector<int> dist(V, 1e9); 
    
    shortest.insert({0, S}); 
    // Source initialised with dist=0
    dist[S] = 0;
    
    // Now, erase the minimum distance node first from the set
    // and traverse for all its adjacent nodes.
    while(!shortest.empty()) {
        auto it = *(shortest.begin()); 
        int node = it.second; 
        int dis = it.first; 
        shortest.erase(it); 
        
        // Check for all adjacent nodes of the erased
        // element whether the prev dist is larger than current or not.
        for(auto i : adj[node]) {
            int adjNode = i[0]; 
            int edgW = i[1]; 
            
            if(dis + edgW < dist[adjNode]) {
                // erase if it was visited previously at 
                // a greater cost.
                if(dist[adjNode] != 1e9) 
                    shortest.erase({dist[adjNode], adjNode}); 
                    
                // If current distance is smaller,
                // push it into the queue
                dist[adjNode] = dis + edgW; 
                shortest.insert({dist[adjNode], adjNode}); 
             }
        }
    }
    // Return the list containing shortest distances
    // from source to all the nodes.
    return dist; 
}
    

int main()
{
    int V = 6, S = 0; // V = Number of Edges, S = Source Node
    vector<vector<int>> adj[V];
    addEdge(adj, 0, 1, 1);
    addEdge(adj, 0, 2, 2);
    addEdge(adj, 1, 2, 4);
    addEdge(adj, 1, 3, 3);
    addEdge(adj, 4, 1, 2);
    addEdge(adj, 2, 5, 3);
    addEdge(adj, 3, 4, 3);
    addEdge(adj, 5, 4, 8);

    vector<int> result = dijkstra(V, adj, S);

    cout << "\nNode:                     ";
    for (int i = 0; i < V; i++)
        cout << i << " | ";
        
    cout << "\nDist (from source = " << S << "):   ";
    for (int i = 0; i < V; i++)
        cout << result[i] << " | ";

    cout << endl;
    return 0;
}
