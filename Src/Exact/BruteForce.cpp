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

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#include <Graph.h>
#include <Solution.h>
#include <tclap/CmdLine.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

int main(int argc, char ** argv) {
    int numberOfCities;
    int numberOfFacilities;

    Graph graph = Graph::createGraphFromStandardInput();
    numberOfCities = graph.getNumberOfNodes();

    try {
        TCLAP::CmdLine cmd("BruteForce Program",' ',"1.0");
        TCLAP::ValueArg<int> numberOfFacilitiesArg("p","numberOfFacilities","Number Of Facilities to be placed",true,1,"int",cmd);

        cmd.parse(argc,argv);

        numberOfFacilities = numberOfFacilitiesArg.getValue();
    }catch(TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

    std::vector<bool> bitset(numberOfCities);
    std::fill(bitset.begin() + numberOfFacilities, bitset.end(), true);
    int MIN = std::numeric_limits<int>::max();
    Solution s(numberOfFacilities);
    Solution best(numberOfFacilities);
    do{
        s.clear();

        FORN(i,numberOfCities)
            if(!bitset[i])
                s.addFacility(i);
        
        s.computeScore(graph);

        if(s.getScore() < MIN) {
            best = s;
            std::cout << best.toString() << std::endl;
            MIN = s.getScore();
        }

    }while(std::next_permutation(bitset.begin(),bitset.end()));

    std::cout << best.toString() << std::endl;

    return 0;
}

