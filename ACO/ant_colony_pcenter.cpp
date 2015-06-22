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
#include <ctime>

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

int main() {
    int number_of_ants = 2;
    int number_of_facilities = 2;
    int max_iteration = 100000;
    int number_of_cities;

    int graph[N][N];
    
    int solutions[number_of_ants][number_of_facilities];

    double pheromone_level_city[N];
    int max_distance_city[N];
    double attractive_level_city[N];

    double alpha=1, beta=1;
    
    double probability_select_city[N];
    double probability_accumulated_city[N];    
    //scan input graph
    scanf("%d",&number_of_cities);
    FORN(i,number_of_cities) {
       FORN(j,number_of_cities) {
           scanf("%d",&graph[i][j]);
       }
    }

    //initialize pheromone_level_city
    FORN(i,number_of_cities) {
        pheromone_level_city[i] = 0.01;
    }

    //initialize attractive_level_city 
    FORN(i,number_of_cities) {
        max_distance_city[i] = 0;
        attractive_level_city[i] = 0;
        FORN(j,number_of_cities) {
            max_distance_city[i] = max(max_distance_city[i],graph[i][j]);
        }
        attractive_level_city[i] = 1/(float)max_distance_city[i];
    }
    
    //compute probability of city selection
    double sum_of_numerators = 0;

    FORN(i,number_of_cities) {
        probability_select_city[i] = pow(pheromone_level_city[i],alpha) * pow(attractive_level_city[i],beta);
        sum_of_numerators += probability_select_city[i];
    }
    FORN(i,number_of_cities) {
        probability_select_city[i] = probability_select_city[i]/sum_of_numerators; 
    }
    probability_accumulated_city[0] = probability_select_city[0];
    for(int i=1;i<number_of_cities;i++) {
        probability_accumulated_city[i] = probability_accumulated_city[i-1] + probability_select_city[i];
    }

    //construct ant solutions
    srand(time(NULL));
    FORN(i,number_of_ants) {
        FORN(j,number_of_facilities) {
            bool found = false;
            int candidate = -1;
            while(!found) {
                double probability_selector = ((double) rand() / (RAND_MAX));
                FORN(k,number_of_cities) {
                    if(probability_selector <= probability_accumulated_city[k]) {
                        candidate = k;
                        break;
                    }
                }
                found = true;
                FORN(search,j) {
                    if(solutions[i][search] == candidate) {
                        found = false;
                        break;
                    }
                }
            }
            solutions[i][j] = candidate;
        }
    }

    FORN(i,number_of_ants) {
        printf("Ant %d: ",i);
        FORN(j,number_of_facilities) {
            printf("%d ",solutions[i][j]);
        }
        printf("\n");
    }


    return 0;
}

