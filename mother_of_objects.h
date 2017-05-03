#ifndef MOTHER_OF_OBJECTS_H
#define MOTHER_OF_OBJECTS_H

// #include "json_parser.h"

#include <string>
#include <iostream>
#include <QDebug>
#include <math.h>

using namespace std;




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
    Ray(const Coordinate &o, Coordinate &d) {
        origin = o;
        direction = d;
    }
};

struct Color {
    int r, g, b;
    
    Color() {}
    Color(int r, int g, int b) : r(r), g(g), b(b) {}
    
    Color operator * (double value) {
        int red = static_cast<int>(r * value);
        int green = static_cast<int>(g * value);
        int blue = static_cast<int>(b * value);
        return Color(red, green, blue);
    }
    
    Color operator * (Coordinate &v) {
        return Color(r * v.x, g * v.y, b * v.z);
    }
    
};


class MotherOfObjects
{

public:
 //
    double lambert = 1;
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
    Coordinate getColor();
    void setColor(Color color);
    Coordinate getCenter();
    void setCenter(Coordinate center_value);
    void setRadius(double radius_value);
    double getRadius();
};

#endif // MOTHER_OF_OBJECTS_H
