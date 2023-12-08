#include "structures/TerrainMap.h"
#include "path/Path.h"
#include "structures/Point.h"
#include "path/CarPath.h"
#include "path/BoatPath.h"
#include "path/TrainPath.h"
#include "path/SurfacePath.h"
#include <vector>
#include <iostream>
#include <string>

// Include files of your path classes will need to be added here

Point read_coordinates(int argc, char *argv[], int i_option) {
    Point p;

    if (argc > i_option+1) { p.x = std::atoi(argv[i_option]); p.y = std::atoi(argv[i_option + 1]); }
    else throw std::runtime_error("Coordinates incorrectly specified!");

    return p;
}

int main() {

    // Load the terrain map
    TerrainMap m(256, 256,"terrain.dat");

    // Load the coordinates of the start and end points

    Point start = Point(198, 205);
    Point finish = Point(78, 17);

    std::vector<Path*> paths = { //new YourPath(m,"MyPathName",start,finish), ...
        // Here add the list of dynamically created classes with path finding algorithms
        new CarPath(m, "car", start, finish),
        new BoatPath(m, "boat", start, finish),
        new TrainPath(m, "train", start, finish),
        new SurfacePath(m, "all-terrain", start, finish)
    };

    for (auto& p : paths) {
        std::cout << "Path search: " << p->getName() << std::endl;
        std::cout << "=============" << std::endl;
        p->find();
        p->printStats();
        std::cout << "=============" << std::endl;
        p->saveToFile();
        delete p;
    }

    return 0;
}
