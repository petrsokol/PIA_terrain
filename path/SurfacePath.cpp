//
// Created by petrs on 08.12.2023.
//

#include "SurfacePath.h"

#include <utility>


SurfacePath::SurfacePath(TerrainMap &map, std::string name, Point start, Point finish) : Path(map, std::move(name), start,
                                                                                              finish) {}

bool SurfacePath::find() {
    std::set<Point> open;
    std::set<Point> closed;
    Point current = start;
    current.computeCosts(start, finish);

    open.insert(current);
    while (!open.empty()) {

        current = *open.begin();
        for (const auto &point: open) {
            if (point.fCost < current.fCost || (point.fCost == current.fCost && point.hCost < current.hCost)) {
                current = point;
            }
        } // z open máme vybranýho takovýho, že má nejmenší fCost - na nejlepší cestě do cíle

        open.erase(current);
        closed.insert(current);

        if (current == finish) {
            closed.insert(current);
            break;
        }

        std::vector<Point> neighbours = getNeighbours(current);
        for (auto &neighbour: neighbours) surfaceCosts(neighbour);

        for (auto &neighbour: neighbours) {
            if (closed.contains(neighbour)) {
                continue;
            }
            double costToNeighbour = current.gCost + timeCost(current, neighbour);
            if (costToNeighbour < neighbour.gCost || !open.contains(neighbour)) {
                neighbour.gCost = costToNeighbour;
                neighbour.hCost = timeCost(neighbour, finish);
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

std::vector<Point> SurfacePath::getNeighbours(Point current) {
    std::vector<Point> res{};
    for (int k = 0; k < 9; ++k) {
        int i = k % 3 - 1;
        int j = k / 3 - 1;
        if (i == 0 && j == 0) continue;
        if (map.validCoords(Point(current.x + i, current.y + j))) {
            Point candidate(current.x + i, current.y + j);
            if (map.slope(current, candidate) < maxSlope || (map.alt(candidate) < 0 && map.alt(current) < 0)) {
                res.push_back(candidate);
            }
        }
    }
    return res;
}

void SurfacePath::surfaceCosts(Point &point) {
    point.gCost = timeCost(start, point);
    point.hCost = timeCost(point, finish);
    point.fCost = point.gCost + point.hCost;
}

double SurfacePath::timeCost(const Point &from, const Point &to) {
    double res;
    double distX = abs(from.x - to.x);
    double distY = abs(from.y - to.y);

    if (distX > distY) {
        res = sqrt(2) * distY + (distX - distY);
    } else {
        res = sqrt(2) * distX + (distY - distX);
    }

    if (map.alt(from) < 0 || map.alt(to) < 0) {
        res *= 4;
    }
    return res;
}
