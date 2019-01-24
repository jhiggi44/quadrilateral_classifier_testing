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
        if (yRes == 0 || xRes == 0)
            q.slopes.push_back(0);
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
    if ((!areEvensParallel && areOddsParallel) || (areEvensParallel && !areOddsParallel))
        return true;
    return false;
}

bool isRectangle(const quadrilateral& q) {
    for (int i = 0; i < 2; i++) {
        // assume slopes must equal zero only because one point is guaranteed to be at 0,0
        if (q.lengths[i] != q.lengths[i + 2] || q.slopes[i] != 0 || q.slopes[i+2] != 0)
            return false;
    }
    return true;
}

bool isSquare(const quadrilateral& q) {
    for (int i = 0; i < q.lengths.size(); i++) {
        int j = findNeighborRef(i);
        if (q.lengths[i] != q.lengths[j] || q.slopes[i] != 0 || q.slopes[j] != 0)
            return false;
    }
    return true;
}

void printProperShape(const quadrilateral& q) {
    bool isAParallelogram = isParallelogram(q);
    bool isAKite = isKite(q);
    bool isATrap = isTrapezoid(q);
    if (isAParallelogram && isAKite) {
        // check to see if it is a square, if it isn't then its a rhombus
        if (isSquare(q))
            std::cout << "square\n";
        else
            std::cout << "rhombus\n";
    } else if (isAParallelogram && !isAKite) {
        if (isRectangle(q) && !isSquare(q))
            std::cout << "rectangle\n";
        else if (isSquare(q))
            std::cout << "square\n";
        else
            std::cout << "parallelogram\n";
    } else if (!isAParallelogram && isAKite) {
        std::cout << "kite\n";
    } else if (isATrap) {
        std::cout << "trapezoid\n";
    } else {
        std::cout << "quadrilateral\n";
    }
}

//rhombus
//quad
//trap
//parallelo
//trap
//rectangle
//kite
//square
//kite

int main(int argc, const char * argv[]) {
//    std::ifstream inFile("input.txt");
    std::string line;
//    while (std::getline(inFile, line)) {
    while (std::getline(std::cin, line)) {
        std::vector<int> data = getData(line);
        quadrilateral q;
        sortCoordinates(data, q);
        calculateSideLengths(q);
        calculateSlopes(q);
        printProperShape(q);
    
//        std::cout << q.lengths[0] << " " << q.lengths[1] << " " << q.lengths[2] << " " << q.lengths[3] << std::endl;
//        std::cout << q.slopes[0] << " " << q.slopes[1] << " " << q.slopes[2] << " " << q.slopes[3] << std::endl << std::endl;
    }
//    std::cout << "THE END" << std::endl;
    return 0;
}

