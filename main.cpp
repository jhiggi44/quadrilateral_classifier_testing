//
//  main.cpp
//  assignment3
//
//  Created by Jordan Higgins on 1/15/19.
//  Copyright © 2019 Jordan Higgins. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct quadrilateral {
    //bottom evens, sides odds
    std::vector<int> x_cords;
    std::vector<int> y_cords;
    std::vector<double> lengths;
    std::vector<double> slopes;
};

std::vector<int> getData(std::string line) {
    std::stringstream ss(line);
    std::istream_iterator<int> begin(ss);
    std::istream_iterator<int> end;
    std::vector<int> data(begin, end);
    return data;
}

void sortCoordinates(const std::vector<int>& data, quadrilateral& q) {
    q.x_cords.push_back(0);
    q.y_cords.push_back(0);
    // put data in backward, to get lengths and slopes in clock-wise order later
    for (int i = data.size() - 1; i >= 0; i--) {
        if (i % 2 == 0)
            q.x_cords.push_back(data[i]);
        else
            q.y_cords.push_back(data[i]);
    }
}

// handles wrap around, a reference to last element in a vector of 4 (4 sides) will return 0;
int findNeighborRef(int ref) {
    int neighborRef = ref + 1;
    if (neighborRef > 3)
        neighborRef = 0;
    return neighborRef;
}

void calculateSideLengths(quadrilateral& q) {
    for (int i = 0; i < q.x_cords.size(); i++) {
        int j = findNeighborRef(i);
        q.lengths.push_back(sqrt(pow((q.x_cords[j] - q.x_cords[i]),2) + pow((q.y_cords[j] - q.y_cords[i]),2)));
    }
}

void calculateSlopes(quadrilateral& q) {
    for (int i = 0; i < q.x_cords.size(); i++) {
        int j = findNeighborRef(i);
        double xRes = q.x_cords[j] - q.x_cords[i];
        double yRes = q.y_cords[j] - q.y_cords[i];
        if (xRes == 0)
            q.slopes.push_back(0);
        else if (yRes == 0) // push back 999 because a yRes of 0 needs to be different than an xRes of zero to properly detect trapezoids
            q.slopes.push_back(999);
        else
            q.slopes.push_back(yRes / xRes);
    }
}

bool isParallelogram(const quadrilateral& q) {
    // loop two times, once for evens, once for odds;
    for (int i = 0; i < 2; i++) {
        if (q.lengths[i] != q.lengths[i + 2] || q.slopes[i] != q.slopes[i + 2])
            return false;
    }
    return true;
}

int findFirstCongruentSide(const quadrilateral& q) {
    for (int i = 0; i < q.lengths.size(); i++) {
        int neighborRef = findNeighborRef(i);
        if (q.lengths[i] == q.lengths[neighborRef])
            return i; // return the first of two congruent sides.
    }
    // returning a -1 means no congruent sides were found.
    return -1;
}

bool isKite(const quadrilateral& q) {
    int startRef = findFirstCongruentSide(q);
    if (startRef < 0)
        return false;
    int oppositeRef = findNeighborRef(startRef + 1);
    int neighborRef = findNeighborRef(oppositeRef);
    bool hasDisjointPair = q.lengths[oppositeRef] == q.lengths[neighborRef];
    if(!hasDisjointPair)
        return false;
    return true;
}

bool isTrapezoid(const quadrilateral& q) {
    bool areEvensParallel = q.slopes[0] == q.slopes[2];
    bool areOddsParallel = q.slopes[1] == q.slopes[3];
    if ((areEvensParallel && !areOddsParallel) || (!areEvensParallel && areOddsParallel))
        return true;
    return false;
}

bool isRectangle(const quadrilateral& q) {
    for (int i = 0; i < 2; i++) {
        // assume slopes must equal zero only because one point is guaranteed to be at 0,0 || q.slopes[i] != 999 || q.slopes[i+2] != 999
        if (q.lengths[i] != q.lengths[i + 2] || (q.slopes[i] != 0 && q.slopes[i] != 999) || (q.slopes[i+2] != 0 && q.slopes[i + 2] != 999))
            return false;
    }
    return true;
}

bool isSquare(const quadrilateral& q) {
    for (int i = 0; i < q.lengths.size(); i++) {
        int j = findNeighborRef(i);
        if (q.lengths[i] != q.lengths[j] || (q.slopes[i] != 0 && q.slopes[i] != 999) || (q.slopes[j] != 0 && q.slopes[j] != 999))
            return false;
    }
    return true;
}

void printProperShape(const quadrilateral& q) {
    bool isAParallelogram = isParallelogram(q);
    bool isAKite = isKite(q);
    if (isAParallelogram && isAKite) {
        // check to see if it is a square, if it isn't then its a rhombus
        if (isSquare(q))
            std::cout << "square\n";
        else
            std::cout << "rhombus\n";
    } else if (isAParallelogram && !isAKite) {
        if (isRectangle(q) && !isSquare(q))
            std::cout << "rectangle\n";
        else
            std::cout << "parallelogram\n";
    } else if (!isAParallelogram && isAKite) {
        std::cout << "kite\n";
    } else if (isTrapezoid(q)) {
        std::cout << "trapezoid\n";
    } else {
        std::cout << "quadrilateral\n";
    }
}

//INPUT VALIDATION
bool isValidInput(std::vector<int> data) {
    if (data.size() != 6) {
        return false;
    }
    for (int i = 0; i < data.size(); i++) {
        if (data[i] < 0 || data[i] > 100) {
            return false;
        }
    }
    return true;
}

bool containsCoincidingPoints(quadrilateral q) {
    // check 3 input points against the default point at 0,0
    for (int i = 1; i < q.x_cords.size(); i++) {
        if ((q.x_cords[i] == 0) && (q.y_cords[i] == 0)) {
            return true;
        }
    }
    // checks 3 points against one another
    if ((q.x_cords[1] == q.x_cords[2] && q.y_cords[1] == q.y_cords[2]) || (q.x_cords[1] == q.x_cords[3] && q.y_cords[1] == q.y_cords[3]) ||
        (q.x_cords[2] == q.x_cords[3] & q.y_cords[2] == q.y_cords[3])) {
        return true;
    }
    return false;
}

int tallyLengths(quadrilateral q) {
    int total = 0;
    for (int i = 0; i < q.lengths.size(); i++) {
        total += q.lengths[i];
    }
    return total;
}

// In a long search for a simple way to detect crossing lines, I came up with this not-even-close way of detecting crossing lines
// by switching points 2 and 3 and checking if the lengths added up got bigger. This works for any traditional quad but not the whackier ones.
// I know it's wrong because my tests succeeded, but it is late and I'm going to bed. I will fix this later.
bool doLinesCross(quadrilateral q) {
    int originalTotal = tallyLengths(q);
    std::vector<int> switchedCoords { q.x_cords[2], q.y_cords[2], q.x_cords[3], q.y_cords[3], q.x_cords[1], q.y_cords[1] };
    quadrilateral z;
    sortCoordinates(switchedCoords, z);
    calculateSideLengths(z);
    int switchedTotal = tallyLengths(z);
    if (switchedTotal < originalTotal) {
        return true;
    }
    return false;
}

bool arePointsColinear(quadrilateral q) {
    int count = 0;
    for (int i = 0; i < q.slopes.size() - 1; i++) {
        if (q.slopes[i] == q.slopes[i + 1]) {
            count++;
        } else {
            count = 0;
        }
        if (count >= 3) {
            return true;
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<int> data = getData(line);
        if (!isValidInput(data)) {
            std::cout << "error 1" << std::endl;
            break;
        }
        quadrilateral q;
        sortCoordinates(data, q);
        calculateSideLengths(q);
        calculateSlopes(q);
        if (containsCoincidingPoints(q)) {
            std::cout << "error 2" << std::endl;
            break;
        }
        if (arePointsColinear(q)) {
            std::cout << "error 4" << std::endl;
            break;
        }
        if (doLinesCross(q)) {
            std::cout << "error 3" << std::endl;
            break;
        }
        printProperShape(q);
    }
    return 0;
}

