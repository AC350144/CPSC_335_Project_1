#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

vector<pair<int, int>> parseInput(string& coordinates, int numOfCoords) 
{
    vector<pair<int, int>> movements;
    stringstream coordinateStream(coordinates);
    char ignore;
    int x, y;

    coordinateStream >> ignore;

    for (int i = 0; i < numOfCoords; i++) 
    {
        coordinateStream >> ignore;
        coordinateStream >> x >> ignore >> y >> ignore;

        movements.push_back({x, y});

        //use this to test if function is working correctly by printing out the vector's contents
        //cout << "Read pair: (" << x << ", " << y << ")" << endl;

        int charactersRead = to_string(x).length() + to_string(y).length() + 6;
        coordinates.erase(0, charactersRead);

        coordinateStream.clear();
        coordinateStream.str(coordinates);
    }

    return movements;
}

bool hasCycle(int node, int parent, const unordered_map<int, vector<int>>& graph, unordered_set<int>& visited) {
    visited.insert(node);

    for (int neighbor : graph.at(node)) 
    {
        if (visited.find(neighbor) == visited.end()) 
        {
            if (hasCycle(neighbor, node, graph, visited)) 
                return true;
        } 
        else if (neighbor != parent)
            return true;
    }

    return false;
}

bool detectCycleInGraph(const vector<pair<int, int>>& movements) 
{
    unordered_map<int, vector<int>> graph;

    for (const auto& movement : movements) 
    {
        graph[movement.first].push_back(movement.second);
        graph[movement.second].push_back(movement.first);
    }

    unordered_set<int> visited;

    for (const auto& movement : movements) 
    {
        if (visited.find(movement.first) == visited.end()) 
        {
            if (hasCycle(movement.first, -1, graph, visited)) 
                return true;
        }
    }

    return false;
}

int main()
{
    int numOfCoords;
    cout << "Enter the number of recorded coordinates as n: ";
    cin >> numOfCoords;
    cin.ignore();

    string coordinates;
    cout << "\nEnter the " << numOfCoords << " pairs of coordinates in the format [(0, 1), (1, 2), ...]: ";
    getline(cin, coordinates);

    vector<pair<int, int>> movements = parseInput(coordinates, numOfCoords);

    if (detectCycleInGraph(movements))
        cout << "Loop detected" << endl;
    else
        cout << "No loop detected" << endl;

    return 0;
}