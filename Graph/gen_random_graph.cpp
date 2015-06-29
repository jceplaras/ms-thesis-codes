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


using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

#define N 1000
#include <ctime>
int main(int argc, char ** argv) {
    int graph_size;
    int graph[N][N];

    srand(time(NULL));
    //for command line input size
    if(argc < 2) {
        printf("Enter graph size: ");
        scanf("%d",&graph_size);
    }
    else {
        graph_size = atoi(argv[1]); 
    }
   
    //generate random edge weights
    FORN(i,graph_size) {
        FORN(j,i) {
            graph[i][j] = graph[j][i] = rand()%101+1;
            if(graph[i][j] >= 80) {
                graph[i][j] = graph[j][i] = -1;
            }
        }
    }
    
    printf("%d\n",graph_size);
    FORN(i,graph_size) {
        FORN(j,graph_size) {
            printf("%d ",graph[i][j]);
        }
        printf("\n");
    }
    return 0;
}

