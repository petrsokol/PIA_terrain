//
// Created by petrs on 08.12.2023.
//

#ifndef PIA_TERRAIN_SURFACEPATH_H
#define PIA_TERRAIN_SURFACEPATH_H


#include "Path.h"

class SurfacePath : public Path {

public:
    // Constraints
    constexpr static double maxSlope = 0.06;

    // Constructor
    SurfacePath(TerrainMap &map, std::string name, Point start, Point finish);

    // Override
    bool find() override;

    // Methods
    std::vector<Point> getNeighbours(Point current);

    void surfaceCosts(Point &point);

    double timeCost(const Point &from, const Point &to);
};


#endif //PIA_TERRAIN_SURFACEPATH_H
