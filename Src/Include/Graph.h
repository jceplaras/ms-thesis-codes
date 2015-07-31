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

#ifndef GRAPH_H
#define GRAPH_H
class Graph {
    private:
        std::vector<std::vector<int>> distanceMatrix;
    public:
        Graph(int numberOfNodes = 0);

        //getters
        int getNumberOfNodes() const ;
        int getEdgeWeight(int i, int j) const ;
        int getMaxCityDistance(int nodeNumber) const ;
        //setters
        void setNumberOfNodes(int numberOfNodes) ;
        void setEdgeWeight(int i, int j, int weight) ;
        //helper functions
        //
        bool isConnected() const;
        std::string toString() const;
        void makeCompleteGraph() ;
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
#endif
