//
// Created by petrs on 08.12.2023.
//

#ifndef PIA_TERRAIN_TRAINPATH_H
#define PIA_TERRAIN_TRAINPATH_H


#include "Path.h"

class TrainPath : public Path {

public:
    constexpr static double maxSlope = 0.04;

    // Constructor
    TrainPath(TerrainMap &map, std::string name, Point start, Point finish);

    // Override
    bool find() override;

    void trainCosts(Point &point);

    std::vector<Point> trainNeighbours(Point current);

    double heightCost(const Point &from, const Point &to);
};


#endif //PIA_TERRAIN_TRAINPATH_H
