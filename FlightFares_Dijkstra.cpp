#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii; // (fare, cityIndex)

class GraphMap {
    map<string, int> cityToIndex;              // Maps city name to index
    vector<string> indexToCity;                // Maps index to city name
    vector<vector<pii> > adjList;              // Adjacency list for graph
    int cityCount;

public:
    GraphMap() : cityCount(0) {}

    // Add city if not already added
    int addCity(const string& city) {
        if (cityToIndex.find(city) == cityToIndex.end()) {
            cityToIndex[city] = cityCount++;
            indexToCity.push_back(city);
            adjList.push_back(vector<pii>());
        }
        return cityToIndex[city];
    }

    // Add bidirectional flight with fare
    void addFlight(const string& cityU, const string& cityV, int fare) {
        int u = addCity(cityU);
        int v = addCity(cityV);
        adjList[u].push_back({v, fare});
        adjList[v].push_back({u, fare});
    }

    // Find minimum fare and route using Dijkstra's algorithm
    void findFare(const string& sourceCity, const string& destCity) {
        if (cityToIndex.find(sourceCity) == cityToIndex.end() || cityToIndex.find(destCity) == cityToIndex.end()) {
            cout << "Source or destination city not found!\n";
            return;
        }

        int src = cityToIndex[sourceCity];
        int dest = cityToIndex[destCity];

        vector<int> dist(cityCount, INT_MAX);   // Minimum fare to each city
        vector<int> maxFare(cityCount, 0);      // Max fare on the path
        vector<int> parent(cityCount, -1);      // For path reconstruction

        priority_queue<pii, vector<pii>, greater<pii> > pq;
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            // Relaxation
            for (int i = 0; i < adjList[u].size(); ++i) {
                int v = adjList[u][i].first;
                int fare = adjList[u][i].second;

                if (dist[v] > dist[u] + fare) {
                    dist[v] = dist[u] + fare;
                    maxFare[v] = max(maxFare[u], fare);
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No route available from " << sourceCity << " to " << destCity << ".\n";
            return;
        }

        // Output fare details
        cout << "\n--- Flight Fare Summary ---\n";
        cout << "From: " << sourceCity << " -> To: " << destCity << "\n";
        cout << "Minimum Total Fare: Rs." << dist[dest] << endl;
        cout << "Highest Single Ticket Fare in SubPath: Rs." << maxFare[dest] << endl;

        // Build path from parent array
        vector<string> path;
        for (int at = dest; at != -1; at = parent[at])
            path.push_back(indexToCity[at]);
        reverse(path.begin(), path.end());

        // Display path
        cout << "Route: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1)
                cout << " -> ";
        }
        cout << "\n----------------------------\n";
    }
};

int main() {
    GraphMap graph;

    // Sample flights
    graph.addFlight("A", "B", 500);
    graph.addFlight("A", "C", 300);
    graph.addFlight("B", "C", 200);
    graph.addFlight("B", "D", 600);
    graph.addFlight("C", "D", 400);
    graph.addFlight("D", "E", 100);
    graph.addFlight("C", "E", 800);

    string source, destination;
    cout << "Enter source city: ";
    cin >> source;
    cout << "Enter destination city: ";
    cin >> destination;

    graph.findFare(source, destination);  // Calculate and show result

    return 0;
}
