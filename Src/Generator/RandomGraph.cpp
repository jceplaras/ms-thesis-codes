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
#include <random>

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#include <Graph.h>
#include <tclap/CmdLine.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

int main(int argc, char ** argv) {
    int nodeCount;
    int edgeCount;
    int minEdgeWeight;
    int maxEdgeWeight;

    try {
        TCLAP::CmdLine cmd("Random Graph Generator",' ',"1.0");
        TCLAP::ValueArg<int> nodeCountArg("n","nodeCount","Number of Nodes in the Graph",true,10,"int",cmd);
        TCLAP::ValueArg<int> edgeCountArg("e","edgeCount","Minimum Number of Edges in the Graph",true,-1,"int",cmd);
        TCLAP::ValueArg<int> minEdgeWeightArg("m","minEdgeWeight","Minimum Edge Weight Possible",false,10,"int",cmd);
        TCLAP::ValueArg<int> maxEdgeWeightArg("M","maxEdgeWeight","Maximum Edge Weight Possible",false,100,"int",cmd);

        cmd.parse(argc,argv);

        nodeCount = nodeCountArg.getValue();
        edgeCount = edgeCountArg.getValue();
        if(edgeCount == -1)
            edgeCount = (nodeCount)*(nodeCount-1)/2;
        minEdgeWeight  = minEdgeWeightArg.getValue();
        maxEdgeWeight = maxEdgeWeightArg.getValue();
        
    }catch(TCLAP::ArgException &e)  // catch any exceptions
    { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
    }

    

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> edgeWeightGenerator(minEdgeWeight,maxEdgeWeight);
    std::uniform_int_distribution<int> nodeTwoGenerator(1,nodeCount-1);
    
    Graph graph(nodeCount);
    int edgeCounter = 0;
        
    while(edgeCounter < edgeCount || !graph.isConnected()) {
        int node2 = nodeTwoGenerator(generator);

        std::uniform_int_distribution<int> nodeOneGenerator(0,node2-1);
        int node1 = nodeOneGenerator(generator);

        int edgeWeight = edgeWeightGenerator(generator);

        graph.setEdgeWeight(node1,node2,edgeWeight);
        edgeCounter++;
    }
    graph.makeCompleteGraph();
    std::cout << graph.toString();

    return 0;
}

