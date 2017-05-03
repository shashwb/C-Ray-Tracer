#ifndef SPHERE_H
#define SPHERE_H

#include <QDebug>

#include "mother_of_objects.h"
#include <string>



class Sphere : public MotherOfObjects
{


public:

    // member variables
    double lambert_one;
    Coordinate center;
    double radius;
    Color color;
    string type;

    // member function
    Sphere();
    Sphere(Coordinate center_value, Color color_value, double lambert_value, double radius_value, string type);
    void print();
    bool intersect(Ray ray, double &out);
    Coordinate getCenter();


private:




};

#endif // SPHERE_H
