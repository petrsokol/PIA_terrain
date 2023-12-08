//
// Created by petrs on 14.11.2023.
//

#ifndef TERRAIN_PLANEPATH_H
#define TERRAIN_PLANEPATH_H

#include <iostream>
#include "Path.h"
#include "../structures/Point.h"

class PlanePath : public Path {

public:
    bool find() override;

    PlanePath(TerrainMap &m, std::string name, Point start, Point finish);
};

#endif //TERRAIN_PLANEPATH_H
