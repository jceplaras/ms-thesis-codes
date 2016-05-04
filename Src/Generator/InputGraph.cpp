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

    int nodeCount=9; 
    Graph graph(nodeCount);
        

    graph.setEdgeWeight(0,1,5);
    graph.setEdgeWeight(1,2,5);
    graph.setEdgeWeight(2,3,2);
    graph.setEdgeWeight(3,4,5);
    graph.setEdgeWeight(4,0,5);
    graph.setEdgeWeight(3,5,5);
    graph.setEdgeWeight(3,6,4);
    graph.setEdgeWeight(2,8,10);
    graph.setEdgeWeight(5,7,5);
    graph.setEdgeWeight(6,7,5);
    graph.setEdgeWeight(6,8,6);
    graph.makeCompleteGraph();
    std::cout << graph.toString();

    return 0;
}

