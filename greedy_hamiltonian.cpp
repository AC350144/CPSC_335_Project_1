#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

/*

CPSC 335 Project 1 

Kristian Losenara
Amanda Chen

*/

int findPreferredStartingCity(const vector<int>& city_distances, const vector<int>& fuel, int mpg) {
    int totalFuel = 0, totalDistance = 0;
    int currentFuel = 0, startCity = 0;

    for (int i = 0; i < city_distances.size(); ++i) 
    {
        totalFuel += fuel[i] * mpg;  // Total fuel from gas stations
        totalDistance += city_distances[i];  // Total distance to be covered
    }

    // If total fuel available is less than total distance, there's no solution (though in this case, a solution is guaranteed)
    if (totalFuel < totalDistance)
        cerr << "ERROR, fuel is somehow less than distance";
        return -1;  //return ERROR, though this shouldnt happen

    for (int i = 0; i < city_distances.size(); ++i) 
    {
        currentFuel += fuel[i] * mpg - city_distances[i];  // Calculate the remaining fuel after traveling to the next city
        
        // If currentFuel becomes negative, it means we can't start from 'startCity', and need to try starting from the next city
        if (currentFuel < 0) 
        {
            startCity = i + 1;  // Change our start to the next city and reset fuel level
            currentFuel = 0;    
        }
    }

    return startCity;  // Return the index of the preferred starting city
}

int main() 
{
    vector<int> city_distances;
    string cityLine;
    vector<int> fuel;
    string fuelLine;
    int mpg; 

    cout << "Input city distances separated by spaces (e.g., x y z): \n";
    getline(cin, cityLine);
    istringstream iss_city(cityLine);     // use our stringstream library to split by spaces
    int numberCity;                      //iterator for storing in vector

    while (iss_city >> numberCity) {     // Read each number and store it in our vector city_distances
        city_distances.push_back(numberCity);  
    }


    cout << ": \n";    //Use the same logic above to get the input for fuel 
    getline(cin, fuelLine);
    istringstream iss_fuel(fuelLine);     
    int numberFuel;                      

    while (iss_fuel >> numberFuel) {
        fuel.push_back(numberFuel);  // Read each number and store it in our vector fuel
    }

    cout << "Lastly, whats the mpg of the car?: \n";  //easy
    cin >> mpg;

    // EXAMPLE TEST CASE FROM HANDOUT
    // vector<int> city_distances = {5, 25, 15, 10, 15};
    // vector<int> fuel = {1, 2, 1, 0, 3};
    // int mpg = 10;
    // "The preferred starting city is: 4"

    int preferredCity = findPreferredStartingCity(city_distances, fuel, mpg);
    cout << "The preferred starting city is: " << preferredCity << endl;

    return 0;
}

