#ifndef MOTHER_OF_OBJECTS_H
#define MOTHER_OF_OBJECTS_H

// #include "json_parser.h"

#include <string>
#include <iostream>
#include <QDebug>
#include <math.h>

using namespace std;


 struct Color {
     int r, g, b;
 };

struct Coordinate {
    double x, y, z;
    Coordinate() {}
    Coordinate(double x, double y, double z) : x(x), y(y), z(z) {}
    Coordinate operator + (const Coordinate &v) const {
        return Coordinate(x+v.x, y+v.y, z+v.z);
    }
    Coordinate operator - (const Coordinate &v) const {
        return Coordinate(x-v.x, y-v.y, z-v.z);
    }
    Coordinate operator * (double d) const {
        return Coordinate(x*d, y*d, z*d);
    }
    Coordinate operator / (double d) const {
        return Coordinate(x/d, y/d, z/d);
    }
    Coordinate normalize() const {
        double mg = sqrt(x*x + y*y + z*z);
        return Coordinate(x/mg,y/mg,z/mg);
    }
    double dotProduct(const Coordinate &coordinate_two) {
        return (this->x*coordinate_two.x + this->y*coordinate_two.y + this->z*coordinate_two.z);
    }

};

struct Ray {
    Coordinate origin, direction;
    Ray() {}
    Ray(const Coordinate &origin, Coordinate &direction) : origin(origin), direction(direction) {}
};


class MotherOfObjects
{

public:
  double lambert;
  Coordinate center;
  Coordinate color;
  string type;
  Coordinate normal;
  double radius;

//  Ray ray;
//  Coordinate coordinate;

    MotherOfObjects();
    virtual void print() = 0;
    virtual bool intersect(Ray ray, double &out) = 0;
    virtual Coordinate getCenter() = 0;

};

#endif // MOTHER_OF_OBJECTS_H
