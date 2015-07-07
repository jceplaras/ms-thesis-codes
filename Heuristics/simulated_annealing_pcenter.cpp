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
#define INF 999999
int main() {
    int number_of_facilities = 2;
    int number_of_cities;

    int graph[N][N];
    
    scanf("%d",&number_of_cities);
    FORN(i,number_of_cities) {
       FORN(j,number_of_cities) {
           scanf("%d",&graph[i][j]);
       }
    }
    int max_distance_city[N]; 
    FORN(i,number_of_cities) {
        max_distance_city[i] = 0;
        FORN(j,number_of_cities) {
            max_distance_city[i] = max(max_distance_city[i],graph[i][j]);
        }
    }
    printf("Max distnaces: \n");
    FORN(i,number_of_cities) {
        printf("%d ",max_distance_city[i]);
    }
    printf("\n");
    int best_solution[N];
    int best_solution_score = 0;
    int current_solution[N];
    int current_solution_score = 999999;
    
    //initial solution
    srand(time(NULL));
    int current_number_of_facilities = 0;
    while(current_number_of_facilities < number_of_facilities) {
        bool has_match = false;
        int random_city = rand()%number_of_cities;

        FORN(i,current_number_of_facilities) {
                if(random_city == best_solution[i]) {
                    has_match = true;
                    break;
                }
        }

        if(!has_match) {
            best_solution[current_number_of_facilities] = random_city;
            current_number_of_facilities++;
        }
    }
    //initial solution score
    FORN(i,number_of_cities) {
        int min_city_score = 999999;
        FORN(j,number_of_facilities) {
                min_city_score = min(min_city_score,max_distance_city[best_solution[j]]);
                printf("Getting minimum? %d i=%d j=%d\n",max_distance_city[best_solution[j]],i,j);
        }
        best_solution_score = max(best_solution_score,min_city_score);
    }
    FORN(i,number_of_facilities) {
        printf("%d ",best_solution[i]);
    }
    printf("\nSCORE: %d\n",best_solution_score);
    //annealing code
    double temperature = 10000;
    double cooling_rate = 0.003;
    int final_solution[N];
    int final_solution_score = 999999;


    while(temperature > 1) {
        //find neighbor
        bool has_match = true;
        int random_city;
        while(has_match) {
            has_match = false;
            random_city = rand()%number_of_cities;
            FORN(i,number_of_facilities) {
                if(random_city == best_solution[i]) {
                    has_match = true;
                    break;
                }
            }
        }
        int random_position = rand()%number_of_facilities;
        FORN(i,number_of_facilities) {
            if(i == random_position) {
                current_solution[i] = random_city;
            }
            else {
                current_solution[i] = best_solution[i];
            }
        }

        //get score of neighbor
        current_solution_score = 0;
        FORN(i,number_of_cities) {
            int min_city_score = 9999999;
            FORN(j,number_of_facilities) {
                    min_city_score = min(min_city_score,max_distance_city[current_solution[j]]);
            }
            current_solution_score = max(current_solution_score,min_city_score);
        }

        if(current_solution_score < best_solution_score || exp((best_solution_score - current_solution_score)/temperature) > ((double) rand() / (RAND_MAX)) ) {
            best_solution_score = current_solution_score;
            FORN(i,number_of_facilities) {
                best_solution[i] = current_solution[i];
            }
        }

        if(best_solution_score < final_solution_score) {
            final_solution_score = best_solution_score;
            FORN(i,number_of_facilities) {
                final_solution[i] = best_solution[i];
            }
        }

        temperature *= 1-cooling_rate;
        printf("Temperature: %f Best Known: %d\n",temperature,best_solution_score);
    }

    printf("Final Solution: \n");
    FORN(i,number_of_facilities) {
        printf("%d ",final_solution[i]);
    }
    printf("\n Score: %d\n",final_solution_score);

    
    return 0;
}

