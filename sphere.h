#ifndef SPHERE_H
#define SPHERE_H

#include <QDebug>

#include "mother_of_objects.h"



class Sphere : virtual public MotherOfObjects
{


public:

    double lambert;
    Coordinate center;
    double radius;
    Coordinate color;


    Sphere();

    Sphere(Coordinate center_value, Coordinate color_value, double lambert_value, double radius_value);

    void print();

    bool intersect(Ray ray, double &out);


private:




};

#endif // SPHERE_H
