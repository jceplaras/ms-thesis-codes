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
    int solution[N];

    int number_of_placed_facilities = 0;
    int current_minimum_city = 1;
    int current_minimum_distance = INF;
    while (number_of_placed_facilities < number_of_facilities) {
        current_minimum_city = -1;
        current_minimum_distance = INF;

        FORN(i,number_of_cities) {
            max_distance_city[i] = 0;
            FORN(j,number_of_cities) {
                max_distance_city[i] = max(max_distance_city[i],graph[i][j]);   
            }
            FORN(j,number_of_placed_facilities) {
                if(i == solution[j]) {
                    max_distance_city[i] = INF;
                    break;
                }
            }
            if(max_distance_city[i] < current_minimum_distance) {
                current_minimum_city = i;
                current_minimum_distance = max_distance_city[i];
            }
        }

        solution[number_of_placed_facilities]  = current_minimum_city;
        
        printf("Selection %d: %d\n",number_of_placed_facilities,solution[number_of_placed_facilities]); 
        number_of_placed_facilities++;

    }

    int temp_score[N];
    int score;
    FORN(i,number_of_cities){
        max_distance_city[i] = 0;
        FORN(j,number_of_cities) {
            max_distance_city[i] = max(max_distance_city[i],graph[i][j]);
        }
    }
    FORN(i,number_of_cities) {
        int min_city_score = 9999999;
        FORN(j,number_of_facilities) {
                min_city_score = min(min_city_score,max_distance_city[solution[j]]);
        }
        score = max(score,min_city_score);

    }
    printf("Score: %d\n",score);


    
    return 0;
}

