//
// Created by petrs on 28.11.2023.
//

#ifndef TERRAIN_CARPATH_H
#define TERRAIN_CARPATH_H


#include <set>
#include "Path.h"

class CarPath : public Path {

public:
    // Constraints
    static const double maxSlope;

    // Constructor
    CarPath(TerrainMap &map, std::string name, Point start, Point finish);

    // Override
    bool find() override;

    // Methods
    std::vector<Point> getNeighbours(Point point, Point start, Point finish);

};


#endif //TERRAIN_CARPATH_H
