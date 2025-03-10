#include "dijkstras.h"

using namespace std;

/**
 * @brief Dijkstra’s algorithm:
 *        - G is a vector of adjacency-lists, each storing edges Edge(src, dst, weight).
 *        - 'source' is the vertex from which we want the shortest paths.
 *        - 'previous[v]' will store the predecessor of v in the shortest path from source to v.
 *        - returns a vector<int> 'distances' where distances[v] is cost of shortest path source->v
 */
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> dist(n, INF);         // distance from source
    vector<bool> visited(n, false);   // track visited set

    dist[source] = 0;
    previous.assign(n, -1);

    // Min-heap storing pairs (distance, vertex)
    // Use a lambda or custom struct for the priority queue compare
    using Pii = pair<int,int>; // (dist, vertex)
    priority_queue<Pii, vector<Pii>, greater<Pii>> pq;

    pq.push({0, source});

    while (!pq.empty()) {
        auto [curDist, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        // For each edge (u->v) with weight w
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

/**
 * @brief Reconstruct the path from the 'previous' array 
 *        by going from 'destination' back to source
 *        using the chain of predecessors.
 *        Return the path in forward order (source->...->destination).
 *
 * @param distances (not strictly needed for reconstruction, 
 *                  but we keep it in case you want to confirm dist[destination])
 * @param previous
 * @param destination
 * @return vector<int> the path from (source) to (destination), or empty if unreachable
 */
vector<int> extract_shortest_path(const vector<int>& distances, 
                                  const vector<int>& previous,
                                  int destination)
{
    // If distances[destination] == INF, no path
    if (destination < 0 || destination >= (int)distances.size() 
        || distances[destination] == INF) {
        return {};
    }

    // Reconstruct by going backward from 'destination'
    stack<int> st;
    int current = destination;
    while (current != -1) {
        st.push(current);
        current = previous[current];
    }

    // Now st has path in reverse, pop into a vector
    vector<int> path;
    while (!st.empty()) {
        path.push_back(st.top());
        st.pop();
    }
    return path;
}

/**
 * @brief Print the path, then the total cost on a new line
 * @param v the path
 * @param total cost of that path
 */
void print_path(const vector<int>& v, int total)
{
    // If the path is truly unreachable => cost is INF
    if (v.empty() && total == INT_MAX) {
        cout << "(No path)\nTotal cost is INF\n";
        return;
    }

    // If the path is empty but cost is finite,
    // the test wants a blank line, then "Total cost is X"
    if (v.empty() && total != INT_MAX) {
        // Print just a blank line for the path
        cout << "\n";
        cout << "Total cost is " << total << "\n";
        return;
    }

    // Otherwise, path is not empty
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) {
            cout << " ";
        }
    }
    cout << " \n";

    cout << "Total cost is " << total << "\n";
}
