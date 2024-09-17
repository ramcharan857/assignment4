#include <iostream>
#include <vector>
#include <climits>
#include <set>
using namespace std;

// Function find minimum distance from vertex
int getMinDist(const vector<int>& distance, const vector<bool>& visitedSet, int numVertices) {
    int minimum = INT_MAX, minIndex;
    for (int v = 0; v < numVertices; v++) {
        if (!visitedSet[v] && distance[v] < minimum) {
            minimum = distance[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to print the shortest path from source to a given node
void displayPath(const vector<int>& predecessors, int currentNode) {
    if (predecessors[currentNode] == -1) {
        return;
    }
    displayPath(predecessors, predecessors[currentNode]);
    cout << currentNode << " ";
}

// Function to display the final shortest path and its cost
void displayResult(const vector<int>& distance, const vector<int>& predecessors, int numVertices, int start, int end) {
    cout << "The shortest path from node " << start << " to " << end << " is: " << endl;
    cout << start << " ";
    displayPath(predecessors, end);
    cout << "\nTotal cost of the path: " << distance[end] << endl;
}

// Dijkstra's algorithm
void calculateDijkstra(const vector<vector<int>>& adjMatrix, int startNode, int endNode, int numVertices) {
    vector<int> distance(numVertices, INT_MAX);  // Min distance from startNode
    vector<bool> visitedSet(numVertices, false); // visited nodes
    vector<int> predecessors(numVertices, -1);   // predecessor of each node in the shortest path

    distance[startNode] = 0; // Start node distance 0

    for (int iteration = 0; iteration < numVertices - 1; iteration++) {
        int currentNode = getMinDist(distance, visitedSet, numVertices); // node with smallest distance
        visitedSet[currentNode] = true;

        // Update distance of adjacent nodes
        for (int neighbor = 0; neighbor < numVertices; neighbor++) {
            if (!visitedSet[neighbor] && adjMatrix[currentNode][neighbor] > 0 &&
                distance[currentNode] + adjMatrix[currentNode][neighbor] < distance[neighbor]) {
                predecessors[neighbor] = currentNode;
                distance[neighbor] = distance[currentNode] + adjMatrix[currentNode][neighbor];
            }
        }
    }

    // Display result
    displayResult(distance, predecessors, numVertices, startNode, endNode);
}

int main() {
    int numVertices;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    vector<vector<int>> adjMatrix(numVertices, vector<int>(numVertices, 0));
    cout << "Enter the adjacency matrix (enter 0 for no direct edge between vertices):\n";
    for (int row = 0; row < numVertices; row++) {
        for (int col = 0; col < numVertices; col++) {
            cin >> adjMatrix[row][col];
        }
    }

    int startNode, endNode;
    cout << "Enter the source node: ";
    cin >> startNode;
    cout << "Enter the destination node: ";
    cin >> endNode;

    calculateDijkstra(adjMatrix, startNode, endNode, numVertices);

    return 0;
}
