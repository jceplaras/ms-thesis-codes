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

#include "Graph.h"

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define MAX_VALUE 999999
#define MIN_VALUE -999999

Graph::Graph(int numberOfNodes) {
    setNumberOfNodes(numberOfNodes);
}

//getters
int Graph::getNumberOfNodes() const {
    return distanceMatrix.size();
}
int Graph::getEdgeWeight(int i, int j) const {
    return distanceMatrix[i][j];
}

int Graph::getMaxCityDistance(int nodeNumber) const {
    int maxCityDistance = MIN_VALUE;
    FORN(i,distanceMatrix[nodeNumber].size()) {
        maxCityDistance = std::max(maxCityDistance,distanceMatrix[nodeNumber][i]);
    }
    return maxCityDistance;
}

//setters
void Graph::setNumberOfNodes(int numberOfNodes) {
    distanceMatrix.resize(numberOfNodes);
    FORN(i,numberOfNodes)
        distanceMatrix[i].resize(numberOfNodes);
}
void Graph::setEdgeWeight(int i, int j, int weight) {
    distanceMatrix[i][j] = distanceMatrix[j][i] = weight;
}

bool Graph::isConnected() const {
    std::vector<bool> isVisited(distanceMatrix.size(),false);

    std::vector<int> explorationQueue;
    explorationQueue.push_back(0);
    while(!explorationQueue.empty()) {
       int vertex = explorationQueue.back();
       explorationQueue.pop_back();

       FORN(i,distanceMatrix.size()) {
            if(distanceMatrix[vertex][i] != 0 && isVisited[i] == false) 
                explorationQueue.push_back(i);
       }
         
       isVisited[vertex] = true;
    }
    
    int countVisited = 0;
    for(bool visited: isVisited)
        if(visited) countVisited++;

    return (countVisited == distanceMatrix.size());

}

void Graph::makeCompleteGraph() {
    int graphSize = distanceMatrix.size();
    FORN(i,graphSize)
        FORN(j,i)
            if(distanceMatrix[i][j] == 0)
                distanceMatrix[i][j]=distanceMatrix[j][i]=MAX_VALUE; 
    FORN(k,graphSize)
        FORN(i,graphSize)
            FORN(j,graphSize)
                distanceMatrix[i][j] = std::min(distanceMatrix[i][j],distanceMatrix[i][k]+distanceMatrix[k][j]);


}

std::string Graph::toString() const {
    std::string returnString ="";

    returnString+=std::to_string(distanceMatrix.size())+"\n";
    FORN(i,distanceMatrix.size()) {
        FORN(j,distanceMatrix.size())
            returnString+=std::to_string(distanceMatrix[i][j])+"\t";
        returnString+="\n";
    }
    return returnString;
}
