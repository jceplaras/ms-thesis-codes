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

#define INF 274364
#define  N 1000
int main() {
    int graph_size;
    int graph[N][N];

    //read graph from input
    scanf("%d",&graph_size);
    FORN(i,graph_size){
        FORN(j,graph_size) {
            scanf("%d",&graph[i][j]);

            if(graph[i][j] == -1) {
                graph[i][j] = INF;
            }   
        }
    }


    //perform floyd warshall from input graph
    FORN(k,graph_size) {
        FORN(i,graph_size) {
            FORN(j,graph_size) {
                graph[i][j] = min(graph[i][j],graph[i][k]+graph[k][j]);
            }
        }
    }
    printf("%d\n",graph_size);
    FORN(i,graph_size) {
        FORN(j,graph_size) {
            printf("%4d ",graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}

