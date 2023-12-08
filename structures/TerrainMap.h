#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include <cmath>
#include <vector>
#include <string>
#include "Point.h"

// Simple class for a 2D (x,y) coordinate vector with integer values



// Data container for matrix representation

template<typename T>
class Matrix {
public:
    Matrix(int n, int m) : nx(n), ny(m), data(n*m) {};
    void zero() { for (T& i : data) i = 0; };
    T operator() (int i, int j) const { return data[i+nx*j]; };
    T& operator() (int i, int j) { return data[i+nx*j]; };
    T operator() (Point const& ij) const { return data[ij.x+nx*ij.y]; };
    T& operator() (Point const& ij) { return data[ij.x+nx*ij.y]; };
    T flattened(int i) const { return data[i]; };
    T& flattened(int i) { return data[i]; };
private:
    int nx; int ny;
    std::vector<T> data;
};

// This class stores the terrain map as a matrix of altitude values

class TerrainMap {

public:
    // Attributes
    const int nx; const int ny;

    // Constructor
    TerrainMap(int n, int m);                       // Creates a zero altitude matrix with dimensions n x m

    TerrainMap(int n, int m, const std::string& filename); // Creates a matrix with dimensions n x m and loads altitude data from file (by rows)

    // Methods
    int alt(int x, int y);                          // Return altitude data for specific coordinates

    int alt(Point const& v);

    double slope(const Point &from, const Point &to); // Return slope between two points (used for neighbours)

    void outputStats();                             // Report access statistics to std. output

    bool validCoords(Point p) const;                // Verify that the given coordinates are within bounds
private:
    Matrix<int> altitude;
    Matrix<int> access_count;
};

#endif
