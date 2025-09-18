#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
using namespace std;

// Custom structure to hold node and its tentative cost
struct PeculiarPair {
    int oddNode;       // Node number
    int rareDistance;  // Distance from source
    bool operator>(const PeculiarPair& other) const {
        return rareDistance > other.rareDistance;
    }
};

// Dijkstra Algorithm Implementation
void mysticDijkstra(const vector<vector<pair<int,int>>> &curiousGraph, int oddStart, int oddEnd) {
    int spookySize = curiousGraph.size();

    // Store distances, initialize with infinity
    vector<int> strangeDistance(spookySize, INT_MAX);
    vector<int> oddParent(spookySize, -1);

    // Min-heap (priority queue) for selecting shortest distance node
    priority_queue<PeculiarPair, vector<PeculiarPair>, greater<PeculiarPair>> funnyQueue;

    // Distance to start node = 0
    strangeDistance[oddStart] = 0;
    funnyQueue.push({oddStart, 0});

    while (!funnyQueue.empty()) {
        PeculiarPair peculiar = funnyQueue.top();
        funnyQueue.pop();

        int currentNode = peculiar.oddNode;
        int currentDist = peculiar.rareDistance;

        // Skip if outdated distance
        if (currentDist > strangeDistance[currentNode]) continue;

        // Explore neighbors
        for (auto neighbor : curiousGraph[currentNode]) {
            int neighborNode = neighbor.first;
            int edgeWeight = neighbor.second;

            if (strangeDistance[currentNode] + edgeWeight < strangeDistance[neighborNode]) {
                strangeDistance[neighborNode] = strangeDistance[currentNode] + edgeWeight;
                oddParent[neighborNode] = currentNode;
                funnyQueue.push({neighborNode, strangeDistance[neighborNode]});
            }
        }
    }

    // Output result
    if (strangeDistance[oddEnd] == INT_MAX) {
        cout << "No mystical path exists between " << oddStart << " and " << oddEnd << endl;
        return;
    }

    cout << "Lowest cost from " << oddStart << " to " << oddEnd << " is: " 
         << strangeDistance[oddEnd] << endl;

    // Reconstruct path using stack
    stack<int> funkyPath;
    for (int wanderer = oddEnd; wanderer != -1; wanderer = oddParent[wanderer]) {
        funkyPath.push(wanderer);
    }

    cout << "Path: ";
    while (!funkyPath.empty()) {
        cout << funkyPath.top();
        funkyPath.pop();
        if (!funkyPath.empty()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    // Hardcoded graph as adjacency list
    // Each entry: node -> list of {neighbor, weight}
    vector<vector<pair<int,int>>> curiousGraph = {
        { {1, 4}, {2, 1} },        // Node 0 connected to 1(cost4),2(cost1)
        { {3, 1} },                // Node 1 connected to 3(cost1)
        { {1, 2}, {3, 5} },        // Node 2 connected to 1(cost2),3(cost5)
        { {4, 3} },                // Node 3 connected to 4(cost3)
        { }                        // Node 4 (no outgoing edges)
    };

    int oddStart, oddEnd;
    cout << "Enter starting node (0-4): ";
    cin >> oddStart;
    cout << "Enter ending node (0-4): ";
    cin >> oddEnd;

    mysticDijkstra(curiousGraph, oddStart, oddEnd);

    return 0;
}
