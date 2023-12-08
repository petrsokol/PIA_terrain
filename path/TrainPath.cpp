//
// Created by petrs on 08.12.2023.
//

#include <iostream>
#include "TrainPath.h"

TrainPath::TrainPath(TerrainMap &map, std::string name, Point start, Point finish) : Path(map, name, start, finish) {}

bool TrainPath::find() {
    std::set<Point> open; //Green - musí bejt sada, abys neměl duplikáty
    std::set<Point> closed; //Red
    Point current = start;
    trainCosts(current);

    open.insert(current);
    while (!open.empty()) {

        current = *open.begin();
        for (const auto &point: open) {
            if (point.fCost < current.fCost || (point.fCost == current.fCost && point.hCost < current.hCost)) {
                current = point;
            }
        }

        open.erase(current);
        closed.insert(current);

        if (current == finish) {
            closed.insert(current);
            break;
        }

        for (auto &item: trainNeighbours(current)) trainCosts(item);

        for (auto &neighbour: trainNeighbours(current)) {
            if (closed.contains(neighbour)) continue;
            double costToNeighbour = current.gCost + heightCost(current, neighbour);
            if (costToNeighbour < neighbour.gCost || !open.contains(neighbour)) {

                neighbour.gCost = costToNeighbour;
                neighbour.hCost = heightCost(neighbour, finish);
                neighbour.fCost = neighbour.gCost + neighbour.hCost;

                neighbour.xParent = current.x;
                neighbour.yParent = current.y;

                if (!open.contains(neighbour)) {
                    open.insert(neighbour);
                }
            }
        }
    }
    if (open.empty()) {
        std::cout << "PATH NOT POSSIBLE" << std::endl;
        return false;
    }
    path = Path::retraceSteps(closed);
    return true;
}

void TrainPath::trainCosts(Point &point) {
    point.gCost = heightCost(start, point);
    point.hCost = heightCost(point, finish);
    point.fCost = point.gCost + point.hCost;
}

std::vector<Point> TrainPath::trainNeighbours(Point current) {
    std::vector<Point> res{};
    for (int k = 0; k < 9; ++k) {
        int i = k % 3 - 1;
        int j = k / 3 - 1;
        if (i == 0 && j == 0) continue;
        if (map.validCoords(Point(current.x + i, current.y + j))) {
            Point candidate(current.x + i, current.y + j);
            if (map.slope(candidate, current) < maxSlope && map.alt(candidate) >= 0) {
                res.push_back(candidate);
            }
        }
    }
    return res;
}

double TrainPath::heightCost(const Point &from, const Point &to) {
    return abs(map.alt(from) - map.alt(to));
}


