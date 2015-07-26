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


#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORN(i,N) for (int i = 0; i < N; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

#define MAX_VALUE 999999
#define MIN_VALUE -999999

class Solution {
    private:
        std::vector<int> facilities;
        int score =MIN_VALUE;
        int maxFacilityCount;

    public:
        //constructor
        Solution(int maxFacilityCount) {
            this->maxFacilityCount = maxFacilityCount;
        }

        //getters
        int getScore() const {
            return score;
        }

        int getCurrentFacilityCount() const {
            return facilities.size();
        }

        int getFacility(int position) const {
            return facilities[position];
        }

        //setters
        void setScore(int score) {
            this->score = score;
        }

        void setMaxFacilityCount(int maxFacilityCount) {
            this->maxFacilityCount = maxFacilityCount;
        }
        
        void setFacilityAt(int facilityNumber,int index) {
            facilities[index] = facilityNumber;
            std::sort(facilities.begin(),facilities.end());
        }

        void addFacility(int facilityNumber) {
            if(this->getCurrentFacilityCount() < this->maxFacilityCount) {
                facilities.push_back(facilityNumber);
                std::sort(facilities.begin(),facilities.end());
            }
        }
    
        //helper functions
        bool isFacilityInSolution(int facilityNumber) {
            return (find(facilities.begin(),facilities.end(),facilityNumber) != facilities.end());
        }

        void computeScore(Graph & graph) {
            int tempScore = -999999;
            FORN(currentCity,graph.getNumberOfNodes()) {
               int distanceToNearestFacility = MAX_VALUE;

               FORN(currentFacilityCount,this->getCurrentFacilityCount()) {
                   int facilityNumber = facilities[currentFacilityCount];
                   distanceToNearestFacility = std::min(distanceToNearestFacility,graph.getEdgeWeight(currentCity,facilityNumber));
               }

               tempScore = std::max(tempScore,distanceToNearestFacility);
            }
            this->score = tempScore;
        }

        int getDifference(Solution & other) {
            int difference = 0;
            FORN(i,other.getCurrentFacilityCount()) {
                if(!this->isFacilityInSolution(other.getFacility(i)))
                    difference++;
            }

            return difference;
        }

        void clear() {
            score = MIN_VALUE;
            facilities.clear();
        }

        std::string toString() {
            std::string returnString;

            returnString += "Facilties: ";
            for(int i: facilities)
                returnString += std::to_string(i) + " ";
            returnString += "Score: ";
            returnString += std::to_string(this->getScore());

            return returnString;
        }

};
//overide comparison operators for Solution class
inline bool operator<(const Solution& lhs, const Solution& rhs) {
    return (lhs.getScore() < rhs.getScore());
}
