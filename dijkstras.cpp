#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to find minimum distance from vertex
int getMinDist(const vector<int>& distance, const vector<bool>& visitedSet, int numVertices) {
    int minimum = INT_MAX, minIndex = -1;
    for (int v = 0; v < numVertices; v++) {
        if (!visitedSet[v] && distance[v] < minimum) {
            minimum = distance[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to print the shortest path from source to a given node
void displayPath(const vector<int>& predecessors, int curNode) {
    if (predecessors[curNode] == -1) {
        return;
    }
    displayPath(predecessors, predecessors[curNode]);
    cout << curNode << " ";
}

// Function to display the final shortest path and its cost
void displayResult(const vector<int>& distance, const vector<int>& predecessors, int numVertices, int start, int end) {
    // Handle case where start and end nodes are the same
    if (start == end) {
        cout << "The source and destination are the same: " << start << endl;
        cout << "Total cost of the path: 0" << endl;
        return;
    }

    // Handle case where no path exists
    if (distance[end] == INT_MAX) {
        cout << "No path exists between node " << start << " and node " << end << endl;
        return;
    }

    // Otherwise, print the shortest path and cost
    cout << "The shortest path from node " << start << " to " << end << " is: " << endl;
    cout << start << " ";
    displayPath(predecessors, end);
    cout << "\nTotal cost of the path: " << distance[end] << endl;
}

// Dijkstra's algorithm
void dijkstra(const vector<vector<int>>& adjMatrix, int startNode, int endNode, int numVertices) {
    vector<int> distance(numVertices, INT_MAX);  // Min distance from startNode
    vector<bool> visitedSet(numVertices, false); // visited nodes
    vector<int> predecessors(numVertices, -1);   // predecessor of each node in the shortest path

    distance[startNode] = 0; // Start node distance is 0

    for (int i = 0; i < numVertices - 1; i++) {
        int curNode = getMinDist(distance, visitedSet, numVertices); // node with smallest distance
        if (curNode == -1) {
            break; // No more reachable nodes
        }
        visitedSet[curNode] = true;

        // Update distance of adjacent nodes
        for (int j = 0; j < numVertices; j++) {
            if (!visitedSet[j] && adjMatrix[curNode][j] > 0 &&
                distance[curNode] + adjMatrix[curNode][j] < distance[j]) {
                predecessors[j] = curNode;
                distance[j] = distance[curNode] + adjMatrix[curNode][j];
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

    dijkstra(adjMatrix, startNode, endNode, numVertices);

    return 0;
}
