//
// Created by petrs on 08.12.2023.
//

#ifndef PIA_TERRAIN_BOATPATH_H
#define PIA_TERRAIN_BOATPATH_H


#include "Path.h"

class BoatPath : public Path{

public:
    // Constraints
    static const int maxElevation = 0;

    //nějak zakomponovat že parametr je nejkratší cesta

    // Constructor
    BoatPath(TerrainMap &map, std::string name, Point start, Point finish);

    // Methods
    std::vector<Point> getNeighbours(Point current);

    // Override
    bool find() override;
};


#endif //PIA_TERRAIN_BOATPATH_H
