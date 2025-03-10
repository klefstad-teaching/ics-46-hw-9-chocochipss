#include "dijkstras.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graphfile.txt>\n";
        return 1;
    }

    string filename = argv[1];
    Graph G;
    try {
        file_to_graph(filename, G);
    } catch(const exception& e) {
        cerr << "Error reading graph: " << e.what() << endl;
        return 1;
    }

    
    int source = 0;

    vector<int> previous; 
    vector<int> dist = dijkstra_shortest_path(G, source, previous);
    
    for (int v = 0; v < G.numVertices; v++) {
        vector<int> path = extract_shortest_path(dist, previous, v);
        cout << "Path to " << v << ":\n";
        print_path(path, (dist[v] == INF) ? -1 : dist[v]);
    }

    return 0;
}
