#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <string>
using namespace std;

const int N = 20;

string towns[N + 1] = {
    "", "Chitipa", "Karonga", "Rumphi", "Mzuzu", "Nkhatabay",
    "Kasungu", "Mchinji", "Lilongwe", "Dowa", "Nkhotakota",
    "Salima", "Dedza", "Ntcheu", "Mangochi", "Balaka",
    "Zomba", "Liwonde", "Blantyre", "Mulanje", "Nsanje"
};

struct Edge {
    int u, v, w;
};

vector<Edge> edges = {
    {1,2,120}, {2,3,180}, {3,4,65}, {4,5,45},
    {4,6,240}, {5,10,190}, {6,9,100}, {6,8,130},
    {6,7,190}, {7,8,110}, {9,8,55}, {9,11,95},
    {10,11,110}, {11,8,110}, {8,12,90}, {12,13,85},
    {13,15,80}, {13,14,145}, {11,14,190}, {14,15,105},
    {14,17,100}, {15,17,35}, {17,16,50}, {16,18,65},
    {18,19,75}, {18,20,190}, {16,19,70}, {15,18,120}
};

vector<pair<int,int>> adj[N + 1];

// Build the undirected graph
void buildGraph() {
    for (auto e : edges) {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }
}

// Dijkstra's Shortest Path Algorithm
void dijkstra(int start, int destination) {
    vector<int> dist(N + 1, INT_MAX);
    vector<int> parent(N + 1, -1);

    priority_queue<pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist[u])
            continue;

        if (u == destination)
            break;

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[destination] == INT_MAX) {
        cout << "No route exists.\n";
        return;
    }

    vector<int> path;

    for (int v = destination; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    cout << "\nSHORTEST ROUTE\n";
    cout << "Starting town: " << towns[start] << endl;
    cout << "Destination: " << towns[destination] << endl;
    cout << "Shortest distance: " << dist[destination] << " km\n";

    cout << "Shortest path: ";

    for (int i = 0; i < path.size(); i++) {
        cout << towns[path[i]];
        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\n";
}

// Disjoint Set Union for Kruskal's Algorithm
int parent[N + 1];

int findSet(int x) {
    if (parent[x] != x)
        parent[x] = findSet(parent[x]);

    return parent[x];
}

bool unite(int a, int b) {
    a = findSet(a);
    b = findSet(b);

    if (a == b)
        return false;

    parent[a] = b;
    return true;
}

// Kruskal's Minimum Spanning Tree
void kruskal() {
    sort(edges.begin(), edges.end(),
        [](Edge a, Edge b) {
            return a.w < b.w;
        });

    for (int i = 1; i <= N; i++)
        parent[i] = i;

    int total = 0, count = 0;

    cout << "\nMINIMUM SPANNING TREE\n";
    cout << "Selected roads:\n";

    for (auto e : edges) {
        if (unite(e.u, e.v)) {
            cout << towns[e.u] << " - "
                 << towns[e.v] << " : "
                 << e.w << " km\n";

            total += e.w;
            count++;
        }
    }

    cout << "\nTotal distance: " << total << " km\n";
    cout << "Connected towns: " << N << endl;
    cout << "Selected roads: " << count << endl;
}

// Main program
int main() {
    buildGraph();

    int choice;

    do {
        cout << "\n================================\n";
        cout << "    MALAWI ROAD NETWORK SYSTEM\n";
        cout << "================================\n";
        cout << "1. Find Shortest Route (Dijkstra)\n";
        cout << "2. Find Minimum Spanning Tree\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            return 0;
        }

        if (choice == 1) {
            int start, destination;

            cout << "Enter starting town (1-20): ";
            if (!(cin >> start)) {
                cout << "Invalid input.\n";
                return 0;
            }

            if (start < 1 || start > N) {
                cout << "Invalid starting town number.\n";
                continue;
            }

            cout << "Enter destination town (1-20): ";
            if (!(cin >> destination)) {
                cout << "Invalid input.\n";
                return 0;
            }

            if (destination < 1 || destination > N) {
                cout << "Invalid destination town number.\n";
                continue;
            }

            dijkstra(start, destination);
        }

        else if (choice == 2) {
            kruskal();
        }

        else if (choice != 0) {
            cout << "Invalid menu option.\n";
        }

    } while (choice != 0);

    cout << "Thank you for using the program!\n";

    return 0;
}