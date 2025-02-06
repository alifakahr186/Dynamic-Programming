#include<iostream>
#include<vector>
#include<string>
#include<climits>

using namespace std;

class Vertex {
public:
    int state_id;
    string state_name;

    Vertex() : state_id(0), state_name("") {}
    Vertex(int id, string sname) : state_id(id), state_name(sname) {}

    int getStateID() { return state_id; }
    string getStateName() { return state_name; }
};

class Graph {
    vector<Vertex> vertices;
    vector<vector<int>> adjMatrix; // Adjacency Matrix
    vector<vector<int>> memo; // DP table for memoization
    int n; // Number of vertices

public:
    Graph() : n(0) {}

    void addVertex(const Vertex& newVertex) {
        for (auto& vertex : vertices) {
            if (vertex.getStateID() == newVertex.getStateID()) {
                cout << "Vertex with this ID already exists" << endl;
                return;
            }
        }
        vertices.push_back(newVertex);
        n = vertices.size();
        adjMatrix.resize(n, vector<int>(n, INT_MAX)); // Use INT_MAX for no path
        memo.resize(n, vector<int>(1 << n, -1)); // Initialize memoization table
        cout << "New Vertex Added Successfully" << endl;
    }

    void addEdgeByID(int from, int to, int weight) {
        if (from < 0 || to < 0 || from >= n || to >= n) {
            cout << "Invalid index for vertices." << endl;
            return;
        }
        adjMatrix[from][to] = weight;
    }

    int tsp(int pos, int mask) {
        if (mask == ((1 << n) - 1)) {
            return adjMatrix[pos][0];
        }
 
        if (memo[pos][mask] != -1) {
            return memo[pos][mask];
        }

        int answer = INT_MAX;
        
        for (int city = 0; city <  n; city++) {
            if (!(mask & (1 << city)) && adjMatrix[pos][city] != INT_MAX) {
                int newAnswer = adjMatrix[pos][city] + tsp (city, mask | (1 << city));
                answer = min(answer,  newAnswer);
            }
        }

        return memo[pos][mask] =  answer;
    }

    void solveTSP() {
        cout << "The cost of the most efficient tour is " << tsp(0, 1) << endl;
    }

    void printGraph() {  
        cout << "Graph: (Adjacency Matrix Representation)" << endl;
        for (int i = 0; i < n; ++i) {
            cout << vertices[i].getStateName() << " (" << vertices[i].getStateID() << ") --> ";
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << adjMatrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;
    g.addVertex(Vertex(0, "A"));
    g.addVertex(Vertex(1, "B"));
    g.addVertex(Vertex(2, "C"));
    g.addVertex(Vertex(3, "D"));

    // Setup edges according to the matrix you provided
    g.addEdgeByID(0, 1, 16);
    g.addEdgeByID(1, 0, 8);
    g.addEdgeByID(0, 2, 11);
    g.addEdgeByID(2, 0, 4);
    g.addEdgeByID(2, 3, 9);
    g.addEdgeByID(3, 2, 2);
    g.addEdgeByID(1, 3, 16);
    g.addEdgeByID(3, 1, 12);
    g.addEdgeByID(1, 2, 13);
    g.addEdgeByID(2, 1, 7);
    g.addEdgeByID(0, 3, 6);
    g.addEdgeByID(3, 0, 5);

    /*	{0, 16, 11, 6}
        {8, 0 ,13,16}
        {4, 7, 0, 9}
        {5, 12, 2, 0} */
    
    g.printGraph();
    g.solveTSP();

    return 0;
}
