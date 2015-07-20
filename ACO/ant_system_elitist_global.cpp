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
#include <random>
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
int score[N];
int best_ant_solution[N];
int best_ant_score = 999999;
bool compare_by_score(int i,int j) {
    return score[i] < score[j];
}
int main(int argc, char ** argv) {
    int number_of_ants;
    int number_of_facilities;
    int max_iteration;
    double alpha, beta;
    double pheromone_evaporation_rate;
 
    if(argc < 8) {
        printf("Usage: ant_colony_pcenter <no_of_ants> <p> <iter> <alpha> <beta> <evap> <elitebonus> < <input cgraph>\n");

        return 1;
    }

    number_of_ants = atoi(argv[1]);
    number_of_facilities = atoi(argv[2]);
    max_iteration = atoi(argv[3]);

    alpha = atof(argv[4]);
    beta = atof(argv[5]);
    pheromone_evaporation_rate = atof(argv[6]);

    int number_of_cities;
    int graph[N][N];
    
    int solutions[number_of_ants][number_of_facilities];

    double pheromone_level_city[N];
    int max_distance_city[N];
    double attractive_level_city[N];
    double pheromone_increase_city[N];

       
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
    
    //Start ACO
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> probability_generator(0,1);
    FORN(iter,max_iteration) {
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
        printf("Prob Level:\n");
        FORN(i,number_of_cities) {
            printf("%f ",probability_accumulated_city[i]);    
        }
        printf("\n");

        //construct ant solutions
        FORN(i,number_of_ants) {
            FORN(j,number_of_facilities) {
                bool found = false;
                int candidate = -1;
                while(!found) {
                    //select city based on the probability
                    double probability_selector = probability_generator(generator);
                    FORN(k,number_of_cities) {
                        if(probability_selector <= probability_accumulated_city[k]) {
                            candidate = k;
                            break;
                        }
                    }
                    //reselect if already existent in solution of current ant
                    found = true;
                    FORN(search,j) {
                        if(solutions[i][search] == candidate) {
                            found = false;
                            break;
                        }
                    }
                }
                //assign candidate city to ant i
                solutions[i][j] = candidate;
            }
        }
       /* 
        solutions[0][0] = 3;
        solutions[0][1] = 8;
        solutions[0][2] = 12;
        */
        //get score of ant
        int temp_score[N];
        FORN(i,number_of_ants) {
            int max_score = 0;
            //get maximum distance from all minimum distances of each city n to corresponding nearest facility
            FORN(n,number_of_cities) {
                int min_city_score = 99999999;
                //get minimum distance of city n to nearest facility j
                FORN(j,number_of_facilities) {
                  min_city_score = min(min_city_score,graph[n][solutions[i][j]]);  
                }
                temp_score[n] = min_city_score;
                max_score = max(max_score,min_city_score);
            }
            score[i] = max_score;
        }
        FORN(i,number_of_ants) {
            printf("Ant %d: ",i);
            FORN(j,number_of_facilities) {
                printf("%d ",solutions[i][j]);
            }
            printf("Score: %d\n",score[i]);
        }
        printf("Pheromone Level: (Before) \n");
        FORN(i,number_of_cities) {
            printf("%f ",pheromone_level_city[i]);
        }
        printf("\n");
        
        //update pheromones - NAIVE WAY
        FORN(i,number_of_cities)
            pheromone_increase_city[i] = 0;
        FORN(i,number_of_ants) {
            FORN(j,number_of_facilities) {
                int city_number = solutions[i][j];
                pheromone_increase_city[city_number] += 1/(float)score[i];
            }
        }

        //get ranking of ants
        int ant_rank[N];
        FORN(i,number_of_ants) {
            ant_rank[i] = i;
        }
        sort(ant_rank,ant_rank+number_of_ants,compare_by_score);
        printf("Sorted by rank:\n");
        FORN(i,number_of_ants) {
            printf("%d: ant %d = %d\n",i,ant_rank[i],score[ant_rank[i]]);
        }
        if(score[ant_rank[0]] < best_ant_score) {
            best_ant_score = score[ant_rank[0]];
            FORN(i,number_of_facilities)
                best_ant_solution[i] = solutions[ant_rank[0]][i];
        }
        //add additional pheromone to the elite solution
        int elitist_bonus = atoi(argv[7]);
        FORN(j,number_of_facilities) {
            int city_number = best_ant_solution[j];
            printf("Adding additional pheromone to city %d\n",city_number);
            pheromone_increase_city[city_number] += elitist_bonus * (1/(float)best_ant_score);
        }

        //pheromone evaporation phase
        FORN(i,number_of_cities) {
            pheromone_level_city[i] += pheromone_increase_city[i];
            pheromone_level_city[i] = (1-pheromone_evaporation_rate) * pheromone_level_city[i];
        }

        
        printf("Pheromone Level: (After) \n");
        FORN(i,number_of_cities) {
            printf("%f ",pheromone_level_city[i]);
        }
        printf("\n");

    }


    return 0;
}

