#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*

CPSC 335 Project 1 

Kristian Losenara
Amanda Chen

*/


vector<pair<int, int>> parseInput(string& coordinates, int numOfCoords) 
{
    vector<pair<int, int>> movements; //store the coordinate pairs
    stringstream coordinateStream(coordinates); //for input processing 
    char ignore;                     //we'll use this char later to ignore paranthesis and commas from our coordinate pairs 
    int x, y;

    coordinateStream >> ignore;                                                     //skip the first parenthesis (

    for (int i = 0; i < numOfCoords; i++)                                           //go through coordinate pairs without the parenthesis and commas
    {
        coordinateStream >> ignore;                                                 //ignore opening parenthesis, read x, ignore comma, read y, ignore parenthesis
        coordinateStream >> x >> ignore >> y >> ignore;

        movements.push_back({x, y});                                                //add our pair to movements

        //TESTING 
        //cout << "Read pair: (" << x << ", " << y << ")" << endl;

        int charactersRead = to_string(x).length() + to_string(y).length() + 6;       //total # of characters read from the original string. erase 'em
        coordinates.erase(0, charactersRead);

        coordinateStream.clear();                                                    //reset stringstream with whats left 
        coordinateStream.str(coordinates);
    }

    return movements;                                                               //return our animal's movements in vector
}

bool hasCycle(int node, int parent, const unordered_map<int, vector<int>>& graph, unordered_set<int>& visited) {  //DFS function, helps us see if there's a repeated node 
    visited.insert(node);                                 //mark current node as visited 

    for (int neighbor : graph.at(node))                    //look at all of its neighbors 
    {
        if (visited.find(neighbor) == visited.end())     // If the neighbor hasn't been visited, recursively check for cycles
        {
            if (hasCycle(neighbor, node, graph, visited)) 
                return true;                             //Cycle is found here 
        } 
        else if (neighbor != parent)                     //If the neighbor has already been visited and it's not the parent
            return true;                                 //Cycle is found here
    }

    return false;
}

bool detectCycleInGraph(const vector<pair<int, int>>& movements)      //main function to detect cycles 
{
    unordered_map<int, vector<int>> graph;          //Use adjaceny list to store our connections

    for (const auto& movement : movements) 
    {
        graph[movement.first].push_back(movement.second);          //from the parseInput function, our movement vector is inputted 
        graph[movement.second].push_back(movement.first);
    }

    unordered_set<int> visited;                                    //visited kept track here


    for (const auto& movement : movements)                      // Loop through all nodes (movements) and check for cycles
    {
        if (visited.find(movement.first) == visited.end())      //DFS starts here from any starting, unvisited node 
        {
            if (hasCycle(movement.first, -1, graph, visited))   //DFS helper function :)
                return true;        //CYCLE FOUND
        }
    }

    return false;                   //CYCLE NOT FOUND 
}

int main()
{
    int numOfCoords;
    cout << "Enter the number of recorded coordinates as n: ";
    cin >> numOfCoords;
    cin.ignore();

    string coordinates;
    cout << "\nEnter the " << numOfCoords << " pairs of coordinates in the format w/o brackets [(0, 1), (1, 2), ...]: ";
    getline(cin, coordinates);


    vector<pair<int, int>> movements = parseInput(coordinates, numOfCoords);

    if (detectCycleInGraph(movements))
        cout << "Loop detected" << endl;
    else
        cout << "No loop detected" << endl;

    return 0;
}