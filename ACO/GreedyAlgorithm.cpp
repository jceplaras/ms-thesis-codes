#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "./Objects/Graph.h"
#include "./Objects/Solution.h"

#include <tclap/CmdLine.h>
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define MAX_VALUE 999999
#define MIN_VALUE -999999
template <typename T> void printVector(std::vector<T> & vc) {
        std::cout << "[";
            for(T i: vc) 
                        std::cout << i << " ";
                std::cout << "]\n";
}


std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<double> probabilityGenerator(0,1);


int main(int argc, char ** argv) {
    int numberOfFacilities = 1;
    try {
        TCLAP::CmdLine cmd("Ant System Basic", ' ', "1.0");
        TCLAP::ValueArg<int> numberOfFacilitiesArgs("p","numberOfFacilities","Number Of Facilities in the optimization",true,1,"int",cmd);
        
        cmd.parse(argc,argv);

        numberOfFacilities = numberOfFacilitiesArgs.getValue();
    }
    catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

    //read input graph and create graph instance 
    Graph graph = Graph::createGraphFromStandardInput();
    int numberOfCities = graph.getNumberOfNodes();


    std::vector<int> maxDistanceCity(numberOfCities);
    FORN(i,numberOfCities)
        maxDistanceCity[i] = graph.getMaxCityDistance(i);

    printVector(maxDistanceCity);
    Solution solution(numberOfFacilities);
    
    FORN(i,numberOfFacilities) {
        int minDistanceCity = MAX_VALUE;
        int candidate = -1;
        FORN(j,numberOfCities) {
            if(maxDistanceCity[j] < minDistanceCity) {
               minDistanceCity = maxDistanceCity[j]; 
               candidate = j;
            }
        }
        std::cout << "Final Candidate for position " << i << " is city " << candidate << " with cost of " << minDistanceCity << std::endl;
        solution.addFacility(candidate);
        maxDistanceCity[candidate] = MAX_VALUE;
    }
    solution.computeScore(graph);

    std::cout << "Greedy Solution: " << std::endl;
    std::cout << solution.toString() << std::endl;
    return 0;
}

