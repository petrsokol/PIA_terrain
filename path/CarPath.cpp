//
// Created by petrs on 28.11.2023.
//

#include "CarPath.h"

#include <utility>
#include <cmath>
#include <set>
#include <iostream>
#include <algorithm>

const double CarPath::maxSlope = 0.06;

CarPath::CarPath(TerrainMap &map, std::string name, Point start, Point finish) : Path(map, std::move(name), start, finish) {}

bool CarPath::find() {
    std::set<Point> open; //Green - musí bejt sada, abys neměl duplikáty
    std::set<Point> closed; //Red
    Point current = start;
    current.computeCosts(start, finish);

    open.insert(current);
    while (!open.empty()) {

//        std::cout << "%%%%%%%% NEW ITERATION %%%%%%%%% \nOPEN:" << std::endl;
//        for (const auto &item: open) item.toString();
//        std::cout << "CLOSED: " << std::endl;
//        for (const auto &item: closed) item.toString();

        current = *open.begin();
        for (const auto &point: open) {
            if (point.fCost < current.fCost || (point.fCost == current.fCost && point.hCost < current.hCost)) {
                current = point;
            }
        } // z open máme vybranýho takovýho, že má nejmenší fCost - na nejlepší cestě do cíle

//        std::cout << "current: " << std::endl;
//        current.toString();

        open.erase(current);
        closed.insert(current);

        if (current == finish) {
//            std::cout << "MÁME TO!!!!" << std::endl;
            closed.insert(current);
            break; //jsme v cíli
        }

        std::vector<Point> neighbours = getNeighbours(current);
        for (auto &item: neighbours) item.computeCosts(start, finish);

//        std::cout << "neighbours of [" << current.x << ";" << current.y << "]: " << neighbours.size() << std::endl;
//        for (const auto &item: neighbours) item.toString();
//        std::cout << std::endl;

        for (auto &neighbour: neighbours) {
            if (closed.contains(neighbour)) {
                continue;
            }
            double costToNeighbour = current.gCost + Point::calculateAtoB(current, neighbour);
            if (costToNeighbour < neighbour.gCost || !open.contains(neighbour)) {
                neighbour.gCost = costToNeighbour;
                neighbour.hCost = Point::calculateAtoB(neighbour, finish);
                neighbour.fCost = neighbour.gCost + neighbour.hCost;
                neighbour.xParent = current.x;
                neighbour.yParent = current.y;
                if (!open.contains(neighbour)) {
                    open.insert(neighbour);
                }
            }
        }
    }
    path = Path::retraceSteps(closed);
    return true;
}

std::vector<Point> CarPath::getNeighbours(Point current) {
    std::vector<Point> res;

    for (int j = -1; j <= 1; ++j) {
        for (int i = -1; i <= 1; ++i) {

            if (i == 0 && j == 0) {
                continue;
            }

            if (map.validCoords(Point(current.x + i, current.y + j))) {
                Point candidate(current.x + i, current.y + j);
                double slope = map.slope(current, candidate);
                if (slope <= maxSlope && map.alt(candidate) >= 0) { //možná bude dělat problémy
                    candidate.computeCosts(start, finish);
                    res.push_back(candidate);
                }
            }

        }
    }
    return res;
}
