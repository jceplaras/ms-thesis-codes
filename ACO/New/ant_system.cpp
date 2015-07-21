#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define MAX_VALUE 999999
#define MIN_VALUE -999999

int numberOfAnts;
int numberOfFacilities;
int maxIteration;
double alpha;
double beta;
double pheromoneEvaporationRate;
double pheromoneInitialValue;

int numberOfCities;

class Graph {
    private:
        std::vector<std::vector<int>> distanceMatrix;
    public:
        Graph(int numberOfNodes = 0) {
            setNumberOfNodes(numberOfNodes);
        }

        //getters
        int getNumberOfNodes() const {
            return distanceMatrix.size();
        }
        int getEdgeWeight(int i, int j) const {
            return distanceMatrix[i][j];
        }

        int getMaxCityDistance(int nodeNumber) const {
            int maxCityDistance = MIN_VALUE;
            FORN(i,distanceMatrix[nodeNumber].size()) {
                maxCityDistance = std::max(maxCityDistance,distanceMatrix[nodeNumber][i]);
            }
            return maxCityDistance;
        }

        //setters
        void setNumberOfNodes(int numberOfNodes) {
            distanceMatrix.resize(numberOfNodes);
            FORN(i,numberOfNodes)
                distanceMatrix[i].resize(numberOfNodes);
        }
        void setEdgeWeight(int i, int j, int weight) {
            distanceMatrix[i][j] = distanceMatrix[j][i] = weight;
        }

        //helper functions
        static Graph createGraphFromStandardInput() {
            Graph g;
            
            int numberOfNodes;
            std::cin >> numberOfNodes;

            g.setNumberOfNodes(numberOfNodes);
            
            int temp;
            FORN(i,numberOfNodes)
                FORN(j,numberOfNodes) {
                    std::cin >> temp;
                    g.setEdgeWeight(i,j,temp);
                }

            return g;
        }

};


class Solution {
    private:
        std::vector<int> facilities;
        int score = MIN_VALUE;
        int maxFacilityCount;

    public:
        //constructor
        Solution(int maxFacilityCount) {
            this->maxFacilityCount = maxFacilityCount;
        }

        //getters
        int getScore() const {
            return score;
        }

        int getCurrentFacilityCount() const {
            return facilities.size();
        }

        int getFacility(int position) const {
            return facilities[position];
        }

        //setters
        void setScore(int score) {
            this->score = score;
        }

        void setMaxFacilityCount(int maxFacilityCount) {
            this->maxFacilityCount = maxFacilityCount;
        }

        void addFacility(int facilityNumber) {
            if(this->getCurrentFacilityCount() < this->maxFacilityCount)
                facilities.push_back(facilityNumber);
        }
    
        //helper functions
        bool isFacilityInSolution(int facilityNumber) {
            return (find(facilities.begin(),facilities.end(),facilityNumber) != facilities.end());
        }

        void computeScore(Graph & graph) {
            FORN(currentCity,numberOfCities) {
               int distanceToNearestFacility = MAX_VALUE;

               FORN(currentFacilityCount,this->getCurrentFacilityCount()) {
                   int facilityNumber = facilities[currentFacilityCount];
                   distanceToNearestFacility = std::min(distanceToNearestFacility,graph.getEdgeWeight(currentCity,facilityNumber));
               }

               this->score = std::max(this->score,distanceToNearestFacility);
            }
        }

        void clear() {
            score = MIN_VALUE;
            facilities.clear();
        }

        std::string toString() {
            std::string returnString;

            returnString += "Facilties: ";
            for(int i: facilities)
                returnString += std::to_string(i) + " ";
            returnString += "Score: ";
            returnString += std::to_string(this->getScore());

            return returnString;
        }

};
//overide comparison operators for Solution class
inline bool operator<(const Solution& lhs, const Solution& rhs) {
    return (lhs.getScore() < rhs.getScore());
}


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
    FORN(i,numberOfCities) {
        if(probabilitySelector < accumulatedProbabilities[i]) return i;
    }
    return numberOfCities-1;
}


//pheromone update section
void updatePheromones(std::vector<double> & pheromoneLevelCity,std::vector<Solution> & ants) {
    std::vector<double> pheromoneIncreaseCity(numberOfCities,0);

    FORN(i,numberOfAnts) {
        FORN(j,numberOfFacilities) {
            int cityNumber = ants[i].getFacility(j);

            pheromoneIncreaseCity[cityNumber] += 1/(double)ants[i].getScore();
        }
    }

    FORN(i,numberOfCities)
        pheromoneLevelCity[i] += pheromoneIncreaseCity[i];
}

//pheromone evaporate section
void evaporatePheromones(std::vector<double> & pheromoneLevelCity) {
   FORN(i,numberOfCities) 
       pheromoneLevelCity[i] *= (1-pheromoneEvaporationRate);
}


int main(int argc, char ** argv) {
    
    if(argc < 8) {
        std::cout << "Usage: "<< argv[0] <<" <numberOfAnts> <numberOfFacilities> <maxIteration> <alpha> <beta> <pheromoneEvaporationRate> <pheromoneInitialValue> < <input.cgraph>\n";
        return 1;
    }

    //set program parameters
    numberOfAnts = atoi(argv[1]);
    numberOfFacilities = atoi(argv[2]);
    maxIteration = atoi(argv[3]);
    alpha = atof(argv[4]);
    beta = atof(argv[5]);
    pheromoneEvaporationRate = atof(argv[6]);
    pheromoneInitialValue = atof(argv[7]);

    
    //read input graph and create graph instance 
    Graph graph = Graph::createGraphFromStandardInput();
    numberOfCities = graph.getNumberOfNodes();
   
    //initialize ant solutions
    std::vector<Solution> ants(numberOfAnts,Solution(numberOfFacilities));
    
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

                printVector(probabilitySelectCity); 
                //compute accumulated city probabilities
                accumulatedProbabilities[0] = probabilitySelectCity[0];
                for(int cityNumber=1;cityNumber<numberOfCities;cityNumber++) {
                    accumulatedProbabilities[cityNumber] = accumulatedProbabilities[cityNumber-1] + probabilitySelectCity[cityNumber];
                }
                printVector(accumulatedProbabilities); 
                /**add facility to current ant**/
                 
                //select city based on biased exploration
                int candidate;
                do{
                    candidate = selectCityByRandomProportionalRule(accumulatedProbabilities,probabilityGenerator(generator));
                }while(ants[currentAnt].isFacilityInSolution(candidate));

                //add candidate facility to current ant in consideration
                ants[currentAnt].addFacility(candidate);

            }
        }//end construct ant solutions

        //compute score of ants
        FORN(i,numberOfAnts)
            ants[i].computeScore(graph);

        //print solution
        std::cout << "Iteration " << iterationNumber << "\n";
        FORN(i,numberOfAnts) {
            std::cout << "Ant " << i << " ";
            std::cout << ants[i].toString(); 
            std::cout << "\n";
        }

        Solution temp(numberOfFacilities);
        temp.addFacility(3);
        temp.addFacility(8);
        temp.addFacility(12);

        temp.computeScore(graph);

        std::cout << "Best: " << temp.toString() << "\n";
        
        std::cout << "Pheromone levels: ";
        printVector(pheromoneLevelCity);

        //update pheromones
        updatePheromones(pheromoneLevelCity,ants);

        //evaporate pheromones
        evaporatePheromones(pheromoneLevelCity);


    }
    return 0;
}

