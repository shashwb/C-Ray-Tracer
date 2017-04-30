#ifndef SPHERE_H
#define SPHERE_H

#include <QDebug>

#include "mother_of_objects.h"
#include <string>



class Sphere : public MotherOfObjects
{


public:

    // member variables
    double lambert;
    Coordinate center;
    double radius;
    Coordinate color;
    string type;

    // member function
    Sphere();
    Sphere(Coordinate center_value, Coordinate color_value, double lambert_value, double radius_value);
    void print();
    bool intersect(Ray ray, double &out);
    Coordinate getCenter();


private:




};

#endif // SPHERE_H
