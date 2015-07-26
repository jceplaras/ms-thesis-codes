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



std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<double> probabilityGenerator(0,1);


int main(int argc, char ** argv) {
    int numberOfFacilities = 1;
    double temperature = 10000;
    double coolingRate = 0.003;
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


    Solution solution(numberOfFacilities);
    

    std::uniform_int_distribution<int> cityGenerator(0,numberOfCities);
    std::uniform_int_distribution<int> facilityGenerator(0,numberOfFacilities);
    //construct initial solution
    while(solution.getCurrentFacilityCount() < numberOfFacilities) {
       int candidate = facilityGenerator(generator);

       if(!solution.isFacilityInSolution(candidate)) {
           solution.addFacility(candidate);
       }
    }
    solution.computeScore(graph);
    
    Solution bestSolution = solution;
    Solution currentSolution = solution;

    std::cout << bestSolution.toString() << std::endl;

    while(temperature > 1) {

        std::cout << "Temperature: " << temperature << std::endl;
        int randomPosition = facilityGenerator(generator);
        int candidateCity;
        do {
            candidateCity = cityGenerator(generator);
        }while(solution.isFacilityInSolution(candidateCity));
        std::cout << "Candidate city " << candidateCity << " placed at " << randomPosition << std::endl; 
        solution.setFacilityAt(candidateCity,randomPosition);
        solution.computeScore(graph);
       
        if(solution.getScore() <= currentSolution.getScore() || std::exp((currentSolution.getScore() - solution.getScore())/ temperature) > probabilityGenerator(generator)) {
            currentSolution = solution;
        }
        if(currentSolution.getScore() < bestSolution.getScore()) {
            bestSolution = currentSolution;
        }

        std::cout << "Candidate: " << solution.toString() << std::endl;
        std::cout << "Current: " << currentSolution.toString() << std::endl;
        std::cout << "Best: " << bestSolution.toString() << std::endl;
        temperature *= 1-coolingRate;
    }
    return 0;
}

