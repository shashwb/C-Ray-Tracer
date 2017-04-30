#include "plane.h"
#include <math.h>

Plane::Plane() : MotherOfObjects()
{

}

Plane::Plane(Coordinate center_val, Coordinate normal_val, Coordinate color_val, double lam_val) : MotherOfObjects() {

    this->center = center_val;
    this->normal = normal_val;
    this->color = color_val;
    this->lambert = lam_val;

}

Coordinate Plane::getCenter() {
  return center;
}

void Plane::print() {
    qDebug() << "created a Plane object";
}

bool Plane::intersect(Ray ray, double &out) {

    double denomintor = normal.dotProduct(ray.direction);
    if (denomintor > 1e-6) {

        Coordinate p0 = normal - ray.origin;
//        out = dotProduct(p0, normal) / denomintor;
        out = p0.dotProduct(normal) / denomintor;
        if (out >= 0) {
            return true;
        }
    }
    return false;
}
