#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list>
#include <queue>

using namespace std;
class Graph {
    int V;
    

public:
    list<pair<int, int>> *adj;
    Graph(int n) {
        this->V = n;
        adj = new list<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
    }
    
    vector<int> dijkstra(int src) {
        priority_queue<pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>>> pq;

        vector<int> dist(V, 5000000);
        pq.push(make_pair(0, src));
        dist[src] = 0;

        while (!pq.empty()) {
            // The first item in pq is the minimum distance
            // vertex, extract it from priority queue.
            // vertex label is stored in second of pair (it
            // has to be done this way to keep the vertices
            // sorted distance (distance must be first item
            // in pair)
            int u = pq.top().second;
            pq.pop();
    
            // 'i' is used to get all adjacent vertices of a vertex
            list< pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = (*i).first;
                int weight = (*i).second;
    
                //  If there is shorted path to v through u.
                if (dist[v] > dist[u] + weight)
                {
                    // Updating distance of v
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        return dist;

    }
};

int main() {
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    string input;
    int **cave = new int*[500];
    int row = 0;
    while (input_file >> input) {
        cave[row] = new int[500];
        for (int i = 0 ; i < 100 ; i++) {
            string conv = "";
            conv.push_back(input[i]);
            cave[row][i] = stoi(conv);
        }
        row++;
    }
    for (int i = 100 ; i < 500 ; i++) {
        cave[i] = new int[500];
    }
    //initialise full matrix
    for (int i = 0 ; i < 5 ; i++) {
        for (int j = 0 ; j < 5 ; j++) {
            for (int k = 0 ; k < 100 ; k++) {
                for (int l = 0 ; l < 100 ; l++) {
                    if (i != 0 || j != 0) {
                        int newVal = cave[k][l] + i + j;
                        while (newVal > 9) {
                            newVal -= 9;
                        }
                        cave[i * 100 + k][j * 100 + l] = newVal;
                    }
                }
            }
        }
    }

    Graph graph(500 * 500);
    //create graph
    for (int i = 0 ; i < 500 ; i++) {
        for (int j = 0 ; j < 500 ; j++) {
            if (i != 0) {
                graph.addEdge(i * 500 + j, (i - 1) * 500 + j, cave[i - 1][j]);
            }
            if (j != 0) {
                graph.addEdge(i * 500 + j, i * 500 + j - 1, cave[i][j - 1]);
            }
            if (i != 499) {
                graph.addEdge(i * 500 + j, (i + 1) * 500 + j, cave[i + 1][j]);
            }
            if (j != 499) {
                graph.addEdge(i * 500 + j, i * 500 + j + 1, cave[i][j + 1]);
            }
        }
    }
    vector<int> dist = graph.dijkstra(0);
    cout << graph.adj[800].front().first << " " << graph.adj[800].front().second <<  endl;
    cout << dist[dist.size() - 1] << endl;
}