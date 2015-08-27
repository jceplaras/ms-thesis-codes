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
    int facilityCount;
    int edgeWeight;
    int x,y;

    std::cin >> nodeCount;
    std::cin >> edgeCount;
    std::cin >> facilityCount;
    
    Graph graph(nodeCount);
    FORN(edgeCounter,edgeCount) {
        std::cin >> x;
        std::cin >> y;
        std::cin >> edgeWeight;

        graph.setEdgeWeight(x-1,y-1,edgeWeight);
    }
        
    graph.makeCompleteGraph();

    std::cout << facilityCount << std::endl;
    std::cout << graph.toString();

    return 0;
}

