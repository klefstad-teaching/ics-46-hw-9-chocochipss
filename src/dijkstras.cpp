#include "dijkstras.h"
#include <climits>  
using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> dist(n, INF);        
    vector<bool> visited(n, false);   

    dist[source] = 0;
    previous.assign(n, -1);

    using Pii = pair<int,int>; 
    priority_queue<Pii, vector<Pii>, greater<Pii>> pq;

    pq.push({0, source});

    while (!pq.empty()) {
        auto [curDist, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;


        for (auto &edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;

            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                previous[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist;
}

vector<int> extract_shortest_path(const vector<int>& distances, 
                                  const vector<int>& previous,
                                  int destination)
{
    if (destination < 0 || destination >= (int)distances.size() 
        || distances[destination] == INF) {
        return {};
    }

    stack<int> st;
    int current = destination;
    while (current != -1) {
        st.push(current);
        current = previous[current];
    }

    vector<int> path;
    while (!st.empty()) {
        path.push_back(st.top());
        st.pop();
    }
    return path;
}


void print_path(const vector<int>& v, int total)
{
    if (v.empty() && total == INT_MAX) {
        cout << "(No path)\nTotal cost is INF\n";
        return;
    }

    if (v.empty() && total != INT_MAX) {
        cout << "\n";
        cout << "Total cost is " << total << "\n";
        return;
    }

    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) {
            cout << " ";
        }
    }
    cout << " \n";

    cout << "Total cost is " << total << "\n";
}
