#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

#include <Graph.h>
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define MAX_VALUE 999999
#define MIN_VALUE -999999

#ifndef SOLUTION_H
#define SOLUTION_H
class Solution {
    private:
        std::vector<int> facilities;
        int score =MIN_VALUE;
        int maxFacilityCount;

    public:
        //constructor
        Solution(int maxFacilityCount) ;

        //getters
        int getScore() const ;
        int getCurrentFacilityCount() const ;
        int getFacility(int position) const ;

        //setters
        void setScore(int score) ;
        void setMaxFacilityCount(int maxFacilityCount) ;
        void setFacilityAt(int facilityNumber,int index) ;
        void addFacility(int facilityNumber) ;
    
        //helper functions
        bool isFacilityInSolution(int facilityNumber) ;
        void computeScore(Graph & graph) ;
        int getDifference(Solution & other) ;
        void clear() ;

        std::string toString() ;
        bool operator<(const Solution & rhs) const;

};
#endif
