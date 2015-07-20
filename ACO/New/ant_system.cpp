#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)


using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

int numberOfAnts;
int numberOfFacilities;
int maxIteration;
double alpha, beta;
double pheromoneEvaporationRate;
double pheromoneInitialValue;

int ** solution;
random_device rd;
mt19937 generator(rd());
uniform_real_distribution<double> probabilityGenerator(0,1);

bool isFacilityInAntSolution(int antNumber,int facilityCount, int facility) {
    FORN(i,facilityCount) {
        if(solution[antNumber][i] == facility)
            return true;
    }
    return false;
}

int main(int argc, char ** argv) {
    
    if(argc < 8) {
        printf("Usage: ant_system <numberOfAnts> <numberOfFacilities> <maxIteration> <alpha> <beta> <pheromoneEvaporationRate> <pheromoneInitialValue> < <input.cgraph>\n");

        return 1;
    }
    

    /**SCAN INPUT GRAPH**/

    //scan number of cities
    int numberOfCities;
    scanf("%d",&numberOfCities);
   
    //scan distance matrix of complete graph
    int graph[numberOfCities][numberOfCities];
    FORN(i,numberOfCities)
        FORN(j,numberOfCities)
            scanf("%d",&graph[i][j]);

    //initialize level of pheromones for each city
    double pheromoneLevelOfCity[numberOfCities];
    FORN(i,numberOfCities)
        pheromoneLevelOfCity[i] = pheromoneInitialValue;

    //initialize level of attractiveness for each city
    double attractivenessLevelOfCity[numberOfCities];
    FORN(i,numberOfCities) {
        attractivenessLevelOfCity[i] = 0;
        FORN(j,numberOfCities)
            attractivenessLevelOfCity[i] = max(attractivenessLevelOfCity[i],(double)graph[i][j]);
        attractivenessLevelOfCity[i] = 1/attractivenessLevelOfCity[i];
    }

    /**START ACO**/


    double probabilityOfCitySelectionNumerator[numberOfCities];
    double probabilityOfCitySelection[numberOfCities];
    double accumulatedProbabilityOfCity[numberOfCities];

    //create solution storage
    solution = new int*[numberOfAnts];
    FORN(i,numberOfAnts)
        solution[i] = new int[numberOfFacilities];

    FORN(iteration,maxIteration) {

        //compute numerator of probability function
        double sumOfNumerators = 0;
        FORN(i,numberOfCities) {
             probabilityOfCitySelectionNumerator[i] = pow(pheromoneLevelOfCity[i],alpha) * pow(attractivenessLevelOfCity[i],beta);
             sumOfNumerators += probabilityOfCitySelectionNumerator[i];
        }
        //compute of probability function
        FORN(i,numberOfCities)
            probabilityOfCitySelection[i] = probabilityOfCitySelectionNumerator[i]/sumOfNumerators;
    
        //compute accumulated probability
        accumulatedProbabilityOfCity[0] = probabilityOfCitySelection[0];
        FORN(i,numberOfCities)
            accumulatedProbabilityOfCity[i] = accumulatedProbabilityOfCity[i-1] + probabilityOfCitySelection[i];

        //construct ant solutions
        FORN(currentFacility,numberOfFacilities) {
            FORN(currentAnt,numberOfAnts) {
                int candidate;
                double probabilitySelector;
                do{
                    probabilitySelector = probabilityGenerator(generator);
                    candidate = selectCityBasedOnProbability(accumulatedProbabilityOfCity,probabilitySelector);
                    solution[currentAnt][currentFacility] = 
                }while(
            }
        }

    }

    //deallocate solution array
    FORN(i,numberOfFacilities)
        delete [] solution[i];
    delete [] solution;

    return 0;
}

