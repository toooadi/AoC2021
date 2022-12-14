#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;

void tokenize(string &str, char delim, vector<string> &out) {
    stringstream ss(str);
    string s; 
    while (std::getline(ss, s, delim)) { 
        //int put = stoi(s);
        out.push_back(s);
    } 
}

int findIndex(vector<string> &vec, string &str) {
    int i = 0;
    for (i ; i < vec.size() ; i++) {
        if (vec[i] == str) {
            break;
        }
    }
    return i;
}

bool *copyVisited(bool *visited, int n) {
    bool* newvis = new bool[n];
    for (int i = 0 ; i < n ; i++) {
        newvis[i] = visited[i];
    }
    return newvis;
}

int findPaths(bool *visited, bool *isUpper, int curr, vector<string> &nodes, vector<vector<string>> edges, bool twice);

int main() {
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    string input;
    vector<string> nodes;
    vector<vector<string>> edges;

    while (input_file >> input) {
        vector<string> temp;
        tokenize(input, '-', temp);
        //add new nodes if values have not been read
        if (find(nodes.begin(), nodes.end(), temp[0]) == nodes.end()) {
            nodes.push_back(temp[0]);
            vector<string> nv;
            edges.push_back(nv);
        }
        if (find(nodes.begin(), nodes.end(), temp[1]) == nodes.end()) {
            nodes.push_back(temp[1]);
            vector<string> nv;
            edges.push_back(nv);
        }
        //push new edges
        int first = findIndex(nodes, temp[0]);
        int second = findIndex(nodes, temp[1]);

        edges[first].push_back(temp[1]);
        edges[second].push_back(temp[0]);
    }

    bool visited[nodes.size()];
    bool isUpper[nodes.size()];
    for (int i = 0 ; i < nodes.size() ; i++) {
        visited[i] = false;
        isUpper[i] = (isupper(nodes[i][0]) != 0);
    }

    string start = "start";
    int res = findPaths(visited, isUpper, findIndex(nodes, start), nodes, edges, false);

    cout << res << endl;

    return EXIT_SUCCESS;
}

int findPaths(bool *visited, bool *isUpper, int curr, vector<string> &nodes, vector<vector<string>> edges, bool twice) {
    if (nodes[curr] == "end") {
        return 1;
    }
    if (!isUpper[curr]) {
        visited[curr] = true;
    }
    int paths = 0;
    for (int i = 0 ; i < edges[curr].size() ; i++) {
        int next = findIndex(nodes, edges[curr][i]);
        
        if (!visited[next]) {
            bool *newvis = copyVisited(visited, nodes.size());
            paths += findPaths(newvis, isUpper, next, nodes, edges, twice);

        //remove this block to compute Part One    
        } else if (!twice && !(nodes[next] == "start")) {
            bool *newvis = copyVisited(visited, nodes.size());
            paths += findPaths(newvis, isUpper, next, nodes, edges, true);
        }
        
    }

    return paths;

}