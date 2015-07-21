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
double alpha;
double beta;
double pheromoneEvaporationRate;
double pheromoneInitialValue;


random_device rd;
mt19937 generator(rd());
uniform_real_distribution<double> probabilityGenerator(0,1);
bool isFacilityInAntSolution(vector<vi> solution, int antNumber,int facilityCount, int facility) {
    FORN(i,facilityCount) {
        if(solution[antNumber][i] == facility)
            return true;
    }
    return false;
}


int getCandidateFacilityByRandomProportionalRule(double * accumulatedProbabilityOfCity,int numberOfCities) {
    double probabilitySelector = probabilityGenerator(generator);
    FORN(i,numberOfCities) {
        if(probabilitySelector <= accumulatedProbabilityOfCity[i])
            return i;
    }
    return numberOfCities-1; 
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
    vector<vi> solution(numberOfAnts);
    FORN(i,numberOfAnts)
        solution[i].resize(numberOfFacilities);

    double probabilityOfCitySelectionNumerator[numberOfCities];
    double probabilityOfCitySelection[numberOfCities];
    double accumulatedProbabilityOfCity[numberOfCities];

    FORN(iteration,maxIteration) {


        //construct ant solutions
        FORN(currentFacility,numberOfFacilities) {
            FORN(currentAnt,numberOfAnts) {

                //compute numerator of probability function
                double probabilityOfCitySelectionDenominator = 0;
                FORN(i,numberOfCities) {
                    //check if is already part of solution and remove its chances
                    if(isFacilityInAntSolution(solution,currentAnt,currentFacility,i)){
                        probabilityOfCitySelectionNumerator[i] = 0; 
                    }
                    //computer numberator of probability function
                    else {
                        probabilityOfCitySelectionNumerator[i] = pow(pheromoneLevelOfCity[i],alpha) * pow(attractivenessLevelOfCity[i],beta);
                    }
                    
                    probabilityOfCitySelectionDenominator+= probabilityOfCitySelectionNumerator[i];
                }

                //compute of probability function
                FORN(i,numberOfCities)
                    probabilityOfCitySelection[i] = probabilityOfCitySelectionNumerator[i]/probabilityOfCitySelectionDenominator;
                
                //compute accumulated probability
                accumulatedProbabilityOfCity[0] = probabilityOfCitySelection[0];
                FORN(i,numberOfCities)
                    accumulatedProbabilityOfCity[i] = accumulatedProbabilityOfCity[i-1] + probabilityOfCitySelection[i];
                
                
                int candidateFacility;
                do {
                    //get candidate facility based on probability formula of ant colony optimization (biased exploration)
                    candidateFacility = getCandidateFacilityByRandomProportionalRule(accumulatedProbabilityOfCity,numberOfCities); 
                //repeat process while solution selected is already 
                }while(isFacilityInAntSolution(solution,currentAnt,currentFacility,candidateFacility));
                

            }
        }

    }


    return 0;
}

