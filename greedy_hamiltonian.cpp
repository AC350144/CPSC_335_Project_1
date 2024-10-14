#include <iostream>
#include <vector>
using namespace std;

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
        return -1;  // This case should not happen based on problem guarantee

    for (int i = 0; i < city_distances.size(); ++i) 
    {
        currentFuel += fuel[i] * mpg - city_distances[i];  // Calculate the remaining fuel after traveling to the next city
        
        // If currentFuel becomes negative, it means we can't start from 'startCity', and need to try starting from the next city
        if (currentFuel < 0) 
        {
            startCity = i + 1;  // Move to the next city as the starting point
            currentFuel = 0;    // Reset the fuel level
        }
    }

    return startCity;  // Return the index of the preferred starting city
}

int main() 
{
    vector<int> city_distances = {5, 25, 15, 10, 15};
    vector<int> fuel = {1, 2, 1, 0, 3};
    int mpg = 10;

    int preferredCity = findPreferredStartingCity(city_distances, fuel, mpg);
    cout << "The preferred starting city is: " << preferredCity << endl;

    return 0;
}