//
// Created by petrs on 05.12.2023.
//

#include <iostream>
#include "Point.h"

Point::Point(int i, int j) {
    x = i;
    y = j;
}

double Point::length() const {
    return sqrt(x*x + y*y);
}

void Point::computeCosts(Point start, Point finish) {
    gCost = calculateAtoB(*this, start);
    hCost = calculateAtoB(*this, finish);
    fCost = gCost + hCost;
}

double Point::calculateAtoB(Point from, Point to) {
    double res;

    double distX = abs(from.x - to.x);
    double distY = abs(from.y - to.y);

    if (distX > distY) {
        res = sqrt(2) * distY + (distX - distY);
    } else {
        res = sqrt(2) * distX + (distY - distX);
    }
    return res;
}

void Point::toString() const {
    std::cout << "Point [" << x << ";" << y << "], gcost = " << gCost << ", hcost = " << hCost << ", fcost = " << fCost << "\n";
}
