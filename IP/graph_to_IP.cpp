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

int main() {
    int number_of_cities;
    int number_of_facilities =3;
    int graph[N][N];


    scanf("%d",&number_of_cities);
    FORN(i,number_of_cities)
        FORN(j,number_of_cities)
            scanf("%d",&graph[i][j]);

    printf("min: z;\n");
    FORN(i,number_of_cities) {
        printf("+y%d ",i);
    }
    printf("= %d;\n",number_of_facilities);
    
    FORN(i,number_of_cities) {
        FORN(j,number_of_cities) {
            printf("+x%d.%d ",i,j);
        }
        printf("= 1;\n");
    }

    FORN(i,number_of_cities)
        FORN(j,number_of_cities) {
            printf("x%d.%d <= y%d;\n",i,j,j);
        }

    FORN(i,number_of_cities) {
        printf(" z ");
        FORN(j,number_of_cities) {
            printf("%+dx%d.%d ",graph[j][i]*-1,i,j);   
        }
        printf(" >= 0;\n");
    }
    
    FORN(i,number_of_cities) {
        printf("bin y%d;\n",i);
        FORN(j,number_of_cities) {
            printf("bin x%d.%d;\n",i,j);
        }
    }
    return 0;
}

