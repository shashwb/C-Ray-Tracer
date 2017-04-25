#ifndef PLANE_H
#define PLANE_H

#include <QDebug>
#include "mother_of_objects.h"



class Plane : virtual public MotherOfObjects
{

public:

    Plane();

    Plane(Coordinate center_val, Coordinate normal_val, Coordinate color_val, double lam_val);

    void print();

    bool intersect(Ray ray, double &out);

    Coordinate center;
    Coordinate normal;
    Coordinate color;
    double lambert;
//    string type;

private:



};

#endif // PLANE_H
