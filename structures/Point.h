//
// Created by petrs on 05.12.2023.
//

#ifndef PIA_TERRAIN_POINT_H
#define PIA_TERRAIN_POINT_H


#include <cmath>

class Point {

public:
    int x;
    int y;
    int xParent, yParent;
    double hCost{}, gCost{}, fCost{};
    /*
     * G - vzdálenost od startu
     * H = vzdálenost od konce
     * F = součet obou
     */
    constexpr static int nx_max = 10000;

    // Constructor
    Point() {};

    Point(int i, int j);

    // Methods
    double length() const;

    void computeCosts(Point start, Point finish);

    static double calculateAtoB(Point from, Point to);

    // Overloaded operators
    Point& operator= (double a) { x = a; y = a; return *this; };

    bool operator!= (Point const& v) const { return !(operator== (v)); };

    bool operator== (Point const& v) const { return x == v.x && y == v.y; };

    Point operator+ (Point const& v) const { return Point(x+v.x,y+v.y); };

    Point operator- (Point const& v) const { return Point(x-v.x,y-v.y); };

    bool operator<  (Point const& v) const { return (x < v.x) || ((x == v.x) && (y < v.y)); }; // This is to provide a simple ordering, the operator doesn't have a geometrical meaning
    void toString() const;
};


#endif //PIA_TERRAIN_POINT_H
