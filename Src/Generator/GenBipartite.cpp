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
    int nodeCount = atoi(argv[1]);
    int bipartite = atoi(argv[2]);


    

    std::random_device rd;
    std::mt19937 generator(rd());
   
    std::vector<int> temp(nodeCount);
    FORN(i,nodeCount)
        temp[i] = i;
    std::shuffle (temp.begin(), temp.end(), generator);
    
    std::uniform_int_distribution<int> partitionGen(1,nodeCount-1);
    int partitionNumber = partitionGen(generator);
    std::uniform_int_distribution<int> nodeTwoGenerator(0,partitionNumber-1);
    std::uniform_int_distribution<int> nodeOneGenerator(partitionNumber,nodeCount-1);
    Graph graph(nodeCount);
    int edgeCounter = 0;
    std::vector<std::string> edges;


    std::uniform_int_distribution<int> arrangeGen(0,1);
    std::stringstream ss;
    while(!graph.isConnected()) {
        int node2 = nodeTwoGenerator(generator);

        int node1 = nodeOneGenerator(generator);

        int edgeWeight = 1; 

        if(graph.getEdgeWeight(node1,node2)==1)
            continue;
        if(arrangeGen(generator) == 1)
            ss << node2 << " " << node1 << std::endl;
        else
            ss << node1 << " " << node2 << std::endl;

        std::string xx = ss.str();
        edges.push_back(xx);
        ss.str("");

        graph.setEdgeWeight(node1,node2,edgeWeight);
        edgeCounter++;
    }


    if(bipartite == 0) {
        if(partitionNumber > 1) {
            int node2 = nodeTwoGenerator(generator);
            int node1;
            do {
                node1 = nodeTwoGenerator(generator);
            }while(node1 == node2);
            ss << node2 << " " << node1 << std::endl;
        }
        else {
        
            int node2 = nodeOneGenerator(generator);
            int node1;
            do {
                node1 = nodeOneGenerator(generator);
            }while(node1 == node2);
            ss << node2 << " " << node1 << std::endl;
        }
        std::string xx = ss.str();
        edges.push_back(xx);
        ss.str("");
        edgeCounter++;
    }
    std::cout << nodeCount << " " << edgeCounter << std::endl;
    std::shuffle (edges.begin(), edges.end(), generator);
    for(std::string s: edges)
        std::cout << s;

    return 0;
}

