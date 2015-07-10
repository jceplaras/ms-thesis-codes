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
#include <random>
int main(int argc, char ** argv) {
    
    int node_size;
    int edge_size; 
    int min_edge_weight, max_edge_weight;
    int graph[N][N];

    node_size = atoi(argv[1]); 
    edge_size = atoi(argv[2]);
    min_edge_weight = atoi(argv[3]);
    max_edge_weight = atoi(argv[4]);

    default_random_engine generator(time(NULL));
    uniform_int_distribution<int> edge_weight_gen(min_edge_weight,max_edge_weight);
    uniform_int_distribution<int> node2gen(1,node_size-1);

    printf("%d %d\n",node_size,edge_size);

    FORN(i,edge_size) {
        int node2 = node2gen(generator);

        uniform_int_distribution<int> node1gen(0,node2-1);
        int node1 = node1gen(generator);

        int edge_weight = edge_weight_gen(generator);

        printf("%d %d %d\n",node1,node2,edge_weight);
    }
    
    return 0;
}

