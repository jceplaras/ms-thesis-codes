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

#define N 1001
#define INF 274364
int main() {
    int number_of_cities;
    int number_of_edges;
    int graph[N][N];

    scanf("%d %d",&number_of_cities,&number_of_edges);
    int x,y,cost;

    FORN(i,number_of_cities) {
        FORN(j,number_of_cities) {
            graph[i][j] = -1;
            if(i==j) graph[i][j] = 0;
        }
    }

    FORN(i,number_of_edges) {
        scanf("%d %d %d",&x,&y,&cost);

        graph[x][y] = graph[y][x] = cost;
        if(x == y) graph[x][y] = 0;
    }
      


    printf("%d\n",number_of_cities);
    FORN(i,number_of_cities) {
        FORN(j,number_of_cities) {
            printf("%d ",graph[i][j]);   
        }
        printf("\n");
    }

    return 0;
}

