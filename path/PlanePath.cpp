//
// Created by petrs on 14.11.2023.
//
#include <cmath>
#include <utility>
#include "PlanePath.h"

PlanePath::PlanePath(TerrainMap &m, std::string name, Point start, Point finish) : Path(m, std::move(name), start, finish) {}

bool PlanePath::find() {
    Point pos = start;

    while (pos != finish) {
        Point dist = finish - pos;
        double l = dist.length();
        double ux = dist.x / l;
        double uy = dist.y / l;
        path.push_back(pos);
        pos.x += int(round(ux));
        pos.y += int(round(uy));
    }
    return true;
}



