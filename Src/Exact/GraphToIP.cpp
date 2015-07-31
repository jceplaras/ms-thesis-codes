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
        TCLAP::CmdLine cmd("Graph to Integer Program",' ',"1.0");
        TCLAP::ValueArg<int> numberOfFacilitiesArg("p","numberOfFacilities","Number Of Facilities to be placed",true,1,"int",cmd);

        cmd.parse(argc,argv);

        numberOfFacilities = numberOfFacilitiesArg.getValue();
    }catch(TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }
      
    std::cout << "min: z;\n";
    FORN(i,numberOfCities)
        printf("+y%d ",i);
    printf("= %d;\n",numberOfFacilities);

    FORN(i,numberOfCities) {
        FORN(j,numberOfCities) {
            printf("+x%d.%d ",i,j);
        }
        printf("= 1;\n");
    }

    FORN(i,numberOfCities) {
        FORN(j,numberOfCities) {
            printf("x%d.%d <= y%d;\n",i,j,j);
        }
    }

    FORN(i,numberOfCities) {
        printf(" z ");
        FORN(j,numberOfCities) {
            printf("%+dx%d.%d ",graph.getEdgeWeight(j,i)*-1,i,j);
        }
        printf(" >= 0;\n");
    }

    FORN(i,numberOfCities) {
        printf("bin y%d;\n",i);
        FORN(j,numberOfCities)
            printf("bin x%d.%d;\n",i,j);
    }

    return 0;
}

