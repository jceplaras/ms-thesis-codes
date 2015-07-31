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

#include "../Include/Graph.h"
#include "../Include/Solution.h"

#include <tclap/CmdLine.h>
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define MAX_VALUE 999999
#define MIN_VALUE -999999



std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<double> probabilityGenerator(0,1);

//helper functions
void printVector(std::vector<double> & vc) {
    std::cout << "[";
    for(double i: vc) 
        std::cout << i << " ";
    std::cout << "]\n";
}
//ant colony function: returns the candidate city by using the random proportional rule
int selectCityByRandomProportionalRule(std::vector<double> & accumulatedProbabilities,double probabilitySelector) {
    FORN(i,accumulatedProbabilities.size()) {
        if(probabilitySelector < accumulatedProbabilities[i]) return i;
    }
    return accumulatedProbabilities.size()-1;
}
int selectCityByExploitation(std::vector<double> & probabilitySelectCityNumerator) {
    int maxNumerator = 0;
    int candidate = -1;

    FORN(cityNumber,probabilitySelectCityNumerator.size()) {
        if(probabilitySelectCityNumerator[cityNumber] > maxNumerator) {
            maxNumerator = probabilitySelectCityNumerator[cityNumber];
            candidate = cityNumber;
        }
    }
    return candidate;
}

//pheromone update section
void updatePhermoneLocal(std::vector<double> & pheromoneLevelCity, std::vector<int> & recentlyAddedFacilities, double pheromoneEvaporationRate, double pheromoneInitialValue) {
    for(int cityNumber: recentlyAddedFacilities) {
        pheromoneLevelCity[cityNumber] = (1-pheromoneEvaporationRate)*pheromoneLevelCity[cityNumber] + pheromoneEvaporationRate*pheromoneInitialValue;
    }
}
void updatePheromonesGlobal(std::vector<double> & pheromoneLevelCity,Solution & elite) {
    FORN(i,elite.getCurrentFacilityCount()) {
        int cityNumber = elite.getFacility(i);
        pheromoneLevelCity[cityNumber] += 1/(double)elite.getScore();
    }

}

//pheromone evaporate section
void evaporatePheromones(std::vector<double> & pheromoneLevelCity,double pheromoneEvaporationRate) {
   FORN(i,pheromoneLevelCity.size()) 
       pheromoneLevelCity[i] *= (1-pheromoneEvaporationRate);
}

//pheromone mutation section
inline double mutationFunction(int currentIteration, int maxIteration, int resetIteration, double mutationStrength, double averagePheromoneBestToDate) {
    return (currentIteration - resetIteration)/(double)(maxIteration - resetIteration) * mutationStrength * averagePheromoneBestToDate;
}

int main(int argc, char ** argv) {

    int numberOfAnts = 1; 
    int numberOfFacilities = 1;
    int maxIteration = 1000;
    double alpha = 1;
    double beta = 2;
    double pheromoneEvaporationRate = 0.1;
    double pheromoneInitialValue = 0.1;
    int eliteSolutionCount = 1;
    //Pheromone Reset Values
    bool isResetEnabled = false;
    double differenceThreshold = 0.1;
    double resetCounterThreshold = 0.2;
    //Phermone Mutation Values
    bool isMutationEnabled = false;
    double mutationRate = 0.3;
    double addSubtractRate = 0.5;
    double mutationStrength  = 4;
    //Pheromone MinMax Value
    double pheromoneMinimumValue = 0;
    double pheromoneMaximumValue = MAX_VALUE;
    //Ant Colony System Parameters
    double exploitationRate = 0.9;

    std::ofstream fileOutput;
    std::string fileNameOutput;
    bool isOutputFileEnabled = false;
    //HANDLING COMMAND LINE ARGUMENTS
    try {
        TCLAP::CmdLine cmd("Ant System Basic", ' ', "1.0");
        TCLAP::ValueArg<int> numberOfAntsArg("n","numberOfAnts","Number Of Ants in the optimization",true,2,"int",cmd);
        TCLAP::ValueArg<int> numberOfFacilitiesArg("p","numberOfFacilities","Number of Facilities to be placed",true,1,"int",cmd);
        TCLAP::ValueArg<int> maxIterationArgs("i","maxIteration","Maximum Number Of Iterations",true,100,"int",cmd);
        TCLAP::ValueArg<double> alphaArgs("a","alpha","Effect of pheromones in calculating probabilities",false,1,"double",cmd);
        TCLAP::ValueArg<double> betaArgs("b","beta","Effect of heuristic factor in calculating probabilities",false,2,"double",cmd);
        TCLAP::ValueArg<double> pheromoneEvaporationRateArgs("e","pheromoneEvapRate","Pheromone evaporation rate",false,0.2,"double",cmd);
        TCLAP::ValueArg<double> pheromoneInitialValueArgs("I","pheromoneInitVal","Pheromone initial value",false,0.1,"double",cmd);
        TCLAP::SwitchArg isResetEnabledSwitch("R","enablePheromoneReset","Enable Pheromone Resetting", cmd, false);
        TCLAP::ValueArg<double> differenceThresholdArgs("d","differenceThreshold","Percentage difference between worst iteration solution and global best solution needed to increment reset counter",false,0.1,"double",cmd);
        TCLAP::ValueArg<double> resetCounterThresholdArgs("t","resetCounterPercentage","percentage of the number of iterations that reset counter must reach",false,0.2,"double",cmd);
        TCLAP::SwitchArg isMutationEnabledSwitch("M","enableMutation","Enable Pheromone Mutation", cmd, false);
        TCLAP::ValueArg<double> mutationRateArgs("m","pheromoneMutationRate","Pheromone evaporation rate",false,0.3,"double",cmd);
        TCLAP::ValueArg<double> addSubtractRateArgs("S","addSubtractRate","Percentage difference between worst iteration solution and global best solution needed to increment reset counter",false,0.5,"double",cmd);
        TCLAP::ValueArg<double> mutationStrengthArgs("G","mutationStrength","Mutation value factor",false,4,"double",cmd);
        TCLAP::ValueArg<std::string> fileOutputArgs("f","fileOutput","fileOutput",false,"","filename",cmd);

        cmd.parse(argc,argv);
        
        numberOfAnts = numberOfAntsArg.getValue();
        numberOfFacilities = numberOfFacilitiesArg.getValue();
        maxIteration = maxIterationArgs.getValue();
        alpha = alphaArgs.getValue();
        beta = betaArgs.getValue();
        pheromoneEvaporationRate = pheromoneEvaporationRateArgs.getValue();
        pheromoneInitialValue = pheromoneInitialValueArgs.getValue();
        
        isResetEnabled = isResetEnabledSwitch.getValue();
        differenceThreshold = differenceThresholdArgs.getValue();
        resetCounterThreshold = resetCounterThresholdArgs.getValue();

        isMutationEnabled = isMutationEnabledSwitch.getValue();
        mutationRate = mutationRateArgs.getValue();
        addSubtractRate = addSubtractRateArgs.getValue();
        mutationStrength = mutationStrengthArgs.getValue();
    
        fileNameOutput = fileOutputArgs.getValue();
        if(!fileNameOutput.empty()) {
            isOutputFileEnabled = true;
            fileOutput.open(fileNameOutput);

        }
    }catch (TCLAP::ArgException &e)  // catch any exceptions
    { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
    }

    
    //read input graph and create graph instance 
    Graph graph = Graph::createGraphFromStandardInput();
    int numberOfCities = graph.getNumberOfNodes();
   
    //initialize ant solutions
    std::vector<Solution> ants(numberOfAnts,Solution(numberOfFacilities));
    std::vector<Solution> eliteAnts;

    //initialize pheromone level of each city
    std::vector<double> pheromoneLevelCity(numberOfCities,pheromoneInitialValue);

    //initialize attractiveness value of each city
    std::vector<double> attractiveLevelCity(numberOfCities);
    FORN(i,numberOfCities)
        attractiveLevelCity[i] = 1/(double)graph.getMaxCityDistance(i);

    //storage of probability function numerator
    std::vector<double> probabilitySelectCityNumerator(numberOfCities); 
    //storage of probability function denominator
    double probabilitySelectCityDenominator = 0;

    //storage of probability values of selecting a city
    std::vector<double> probabilitySelectCity(numberOfCities);

    //storage of accumulated probabilities
    std::vector<double> accumulatedProbabilities(numberOfCities);
    
    //storage of reset related parameters
    int resetCounter = 0;
    int lastResetIteration = 0;
    resetCounterThreshold = resetCounterThreshold * maxIteration;

    std::vector<int> recentlyAddedFacilities(numberOfAnts);

    /**START ACO**/
    FORN(iterationNumber,maxIteration) {

        //reset solutions
        FORN(i,numberOfAnts)
            ants[i].clear();
       //construct ant solutions
        FORN(currentFacilityCount,numberOfFacilities) {
            FORN(currentAnt,numberOfAnts) {

                //initialize probability values (numerator and denominator)
                probabilitySelectCityDenominator = 0;
                FORN(cityNumber,numberOfCities) {
                    if(ants[currentAnt].isFacilityInSolution(cityNumber))
                        probabilitySelectCityNumerator[cityNumber] = 0;
                    else
                        probabilitySelectCityNumerator[cityNumber] = pow(pheromoneLevelCity[cityNumber],alpha) * pow(attractiveLevelCity[cityNumber],beta);
                    
                    probabilitySelectCityDenominator += probabilitySelectCityNumerator[cityNumber];
                }

                //compute probability values
                FORN(cityNumber,numberOfCities) {
                    probabilitySelectCity[cityNumber] = probabilitySelectCityNumerator[cityNumber]/probabilitySelectCityDenominator;    
                }

                //compute accumulated city probabilities
                accumulatedProbabilities[0] = probabilitySelectCity[0];
                for(int cityNumber=1;cityNumber<numberOfCities;cityNumber++) {
                    accumulatedProbabilities[cityNumber] = accumulatedProbabilities[cityNumber-1] + probabilitySelectCity[cityNumber];
                }
                /**add facility to current ant**/
                 
                //select city based on biased exploration
                int candidate;
                do{
                    double ruleSelector = probabilityGenerator(generator);
                    if(ruleSelector < exploitationRate)
                        candidate = selectCityByExploitation(probabilitySelectCityNumerator);
                    else
                        candidate = selectCityByRandomProportionalRule(accumulatedProbabilities,probabilityGenerator(generator));
                }while(ants[currentAnt].isFacilityInSolution(candidate));

                //add candidate facility to current ant in consideration
                ants[currentAnt].addFacility(candidate);
                recentlyAddedFacilities[currentAnt] = candidate;
            }
            updatePhermoneLocal(pheromoneLevelCity,recentlyAddedFacilities,pheromoneEvaporationRate,pheromoneInitialValue);
            
        }//end construct ant solutions

        //compute score of ants
        FORN(i,numberOfAnts)
            ants[i].computeScore(graph);
        std::sort(ants.begin(),ants.end());

        eliteAnts.insert(eliteAnts.end(),ants.begin(),ants.end());
        std::stable_sort(eliteAnts.begin(),eliteAnts.end());
        eliteAnts.resize(eliteSolutionCount,Solution(numberOfFacilities));

        //print solution
        std::cout << "Iteration " << iterationNumber << "\n";
        FORN(i,numberOfAnts) {
            std::cout << "Ant " << i << " ";
            std::cout << ants[i].toString(); 
            std::cout << "\n";
        }

        std::cout << "Elites\n";
        FORN(i,eliteSolutionCount) {
            std::cout << eliteAnts[i].toString() << "\n";
        }

        std::cout << "Pheromone levels: ";
        printVector(pheromoneLevelCity);


        if(isOutputFileEnabled) {
            fileOutput << "Iteration," << iterationNumber;
            fileOutput << ",AntsCount," << numberOfAnts;
            fileOutput << ",FacilitiesCount," << numberOfFacilities;
            fileOutput << ",CitiesCount," << numberOfCities;
            fileOutput << ",GlobalBest," << eliteAnts[0].getScore();
            fileOutput << ",IterBest," << ants[0].getScore();
            fileOutput << ",IterWorst," << ants[numberOfAnts-1].getScore();
            fileOutput << std::endl;
        }
        //update pheromones
        updatePheromonesGlobal(pheromoneLevelCity,eliteAnts[0]);

        //evaporate pheromones
        evaporatePheromones(pheromoneLevelCity,pheromoneEvaporationRate);
        if(isMutationEnabled) {
            //get average pheromone on best solution facilties
            double averagePheromoneBestToDate = 0;
            FORN(i,numberOfFacilities) {
                averagePheromoneBestToDate += pheromoneLevelCity[eliteAnts[0].getFacility(i)];
            }
            averagePheromoneBestToDate /= numberOfFacilities;

            //mutate pheromones
            FORN(i,numberOfCities) {
                if(probabilityGenerator(generator) < mutationRate) {
                    std::cout << "Mutation happened on city " << i << "\n";
                    if(probabilityGenerator(generator) < addSubtractRate) {
                        //additive mutation
                        pheromoneLevelCity[i] = pheromoneLevelCity[i]+mutationFunction(iterationNumber,maxIteration,lastResetIteration,mutationStrength,averagePheromoneBestToDate); 
                        pheromoneLevelCity[i] = std::min(pheromoneLevelCity[i],pheromoneMaximumValue);
                    }
                    else {
                        pheromoneLevelCity[i] = pheromoneLevelCity[i]-mutationFunction(iterationNumber,maxIteration,lastResetIteration,mutationStrength,averagePheromoneBestToDate); 
                        pheromoneLevelCity[i] = std::max(pheromoneLevelCity[i],pheromoneMinimumValue);

                    }
                }
            }
        }
        if(isResetEnabled) {
                //reset pheromones
                int differenceBestWorstSolution = eliteAnts[0].getDifference(ants[numberOfAnts-1]);
                std::cout << "Difference of BestGlobal and WorstLocal: " << differenceBestWorstSolution << "\n";
                if(differenceBestWorstSolution <= differenceThreshold*numberOfFacilities)
                    resetCounter++;

                std::cout << "Reset Counter: " << resetCounter << " Reset Threshold " << resetCounterThreshold << "\n";
                if(resetCounter >= resetCounterThreshold) {
                    resetCounter = 0;
                    lastResetIteration = iterationNumber;
                    pheromoneLevelCity.assign(numberOfCities,pheromoneInitialValue);
                }
        }

    }

    if(isOutputFileEnabled)
        fileOutput.close();
    return 0;
}

