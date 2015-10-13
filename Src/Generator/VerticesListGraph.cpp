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
#include <random>

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


#define toRadians(x) x*M_PI/180.0
double greatCricleDistance(double lat1,double lon1,double lat2,double lon2) {
  double R = 6378135;

  double sinHalfLat = sin(toRadians(abs(lat2-lat1))/2.0);
  double sinHalfLon = sin(toRadians(abs(lon2-lon1))/2.0);
  double d = 2*R*asin(sqrt(sinHalfLat*sinHalfLat + cos(toRadians(lat1))*cos(toRadians(lat2))*sinHalfLon*sinHalfLon));
  return d;
}

int main(int argc, char ** argv) {
  
  int T;
  double graph[100][100];
  double llat[100];
  double llon[100];
  int V;
  double lat,lon;
  scanf("%d",&T);
  while(T--) {
    scanf("%d",&V);
    scanf("%lf",&llat[V]);
    scanf("%lf",&llon[V]);
  }


  FORN(i,82)
    FORN(j,i) {
      graph[i][j] = graph[j][i] = greatCricleDistance(llat[i],llon[i],llat[j],llon[j]);
    }
  printf("82\n");
  FORN(i,82) {
    FORN(j,82)
      printf("%d ",(int)floor(graph[i][j])/1000);
    printf("\n");
  }

    return 0;
}

