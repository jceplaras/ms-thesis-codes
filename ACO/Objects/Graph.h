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
