#include "Path.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>

Path::Path(TerrainMap& m, std::string name_in, Point start_in, Point finish_in) : map(m), name(name_in), start(start_in), finish(finish_in) {};

void Path::printStats() const {
    bool land = false;
    bool water = false;
    double length = 0.0;
    double alt = 0.0;
    int max_alt = map.alt(path[0]);

    for (int i=1; i<path.size(); ++i) {
        Point u = path[i];
        Point u_prev = path[i-1];
        if (i < path.size() - 1 && map.alt(u) > 0) land = true;
        if (map.alt(u) < 0) water = true;
        length += (u - u_prev).length();
        alt += std::abs(map.alt(u) - map.alt(u_prev));
        if (map.alt(u) > max_alt) max_alt = map.alt(u);
    }

    if (land) std::cout << "Path from [" << start.x << ", " << start.y << "] to [" << finish.x << ", " << finish.y << "]" << std::endl;
    if (land) std::cout << "Path type: land" << std::endl;
    if (water) std::cout << "Path type: water" << std::endl;
    std::cout << "Path length: " << length << " km" << std::endl;
    std::cout << "Total elevation gain + loss: " << alt << " m" << std::endl;
    std::cout << "Max. elevation: " << max_alt << " m" << std::endl;
}

std::string Path::getName() const {
    return name;
}

void Path::saveToFile() const {
    std::ofstream output(name + ".dat");

    if (!output) throw std::runtime_error("Cannot open file " + name + ".dat");

    for (Point u : path) {
        output << u.x << " " << u.y << std::endl;
    }
}

std::vector<Point> Path::retraceSteps(std::set<Point> closed) {
    std::vector<Point> res{};
    Point current = *closed.find(finish);
    while (current != start) {
        res.push_back(current);
        current = *closed.find(Point(current.xParent, current.yParent));
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::vector<Point> Path::getNeighbours(Point current, bool conditions) {
    std::vector<Point> res;
    for (int j = -1; j <= 1; ++j) {
        for (int i = -1; i <= 1; ++i) {
            if (i == 0 && j == 0) {continue;}
            if (map.validCoords(Point(current.x + i, current.y + j))) {
                Point candidate(current.x + i, current.y + j);
                if (conditions) { //možná bude dělat problémy
                    res.push_back(candidate);
                }
            }
        }
    }
    return res;
}
