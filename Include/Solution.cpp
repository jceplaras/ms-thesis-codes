#include "Solution.h"

//constructor
Solution::Solution(int maxFacilityCount) {
    this->maxFacilityCount = maxFacilityCount;
}

//getters
int Solution::getScore() const {
    return score;
}

int Solution::getCurrentFacilityCount() const {
    return facilities.size();
}

int Solution::getFacility(int position) const {
    return facilities[position];
}

//setters
void Solution::setScore(int score) {
    this->score = score;
}

void Solution::setMaxFacilityCount(int maxFacilityCount) {
    this->maxFacilityCount = maxFacilityCount;
}

void Solution::setFacilityAt(int facilityNumber,int index) {
    facilities[index] = facilityNumber;
    std::sort(facilities.begin(),facilities.end());
}

void Solution::addFacility(int facilityNumber) {
    if(this->getCurrentFacilityCount() < this->maxFacilityCount) {
        facilities.push_back(facilityNumber);
        std::sort(facilities.begin(),facilities.end());
    }
}

//helper functions
bool Solution::isFacilityInSolution(int facilityNumber) {
    return (find(facilities.begin(),facilities.end(),facilityNumber) != facilities.end());
}

void Solution::computeScore(Graph & graph) {
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

int Solution::getDifference(Solution & other) {
    int difference = 0;
    FORN(i,other.getCurrentFacilityCount()) {
        if(!this->isFacilityInSolution(other.getFacility(i)))
            difference++;
    }

    return difference;
}

void Solution::clear() {
    score = MIN_VALUE;
    facilities.clear();
}

std::string Solution::toString() {
    std::string returnString;

    returnString += "Facilties: ";
    for(int i: facilities)
        returnString += std::to_string(i) + " ";
    returnString += "Score: ";
    returnString += std::to_string(this->getScore());

    return returnString;
}


bool Solution::operator<(const Solution & rhs) const {
    return (this->getScore() < rhs.getScore());
}
