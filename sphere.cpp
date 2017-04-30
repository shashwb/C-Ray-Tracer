#include "sphere.h"


Sphere::Sphere() : MotherOfObjects()
{

}

Sphere::Sphere(Coordinate center_value, Coordinate color_value, double lambert_value, double radius_value) : MotherOfObjects() {

    this->center = center_value;
    this->color = color_value;
    this->lambert = lambert_value;
    this->radius = radius_value;

}

void Sphere::print() {
    qDebug() << "created a Sphere object";
}

Coordinate Sphere::getCenter() {
  return center;
}

bool Sphere::intersect(Ray ray, double &out) {

    double out1, out2;

    Coordinate length =  center - ray.origin;
    double tca = length.dotProduct(ray.direction);

    if (tca < 0) {
        return false;
    }
    double dot_solution = length.dotProduct(length) - (tca * tca);
    double radius_squared = radius * radius;

    if (dot_solution > radius_squared) {
        return false;
    }

    double thc = sqrt(radius_squared - dot_solution);

    out1 = tca - thc;
    out2 = tca + thc;

    if (out1 > out2) {
        std::swap(out1, out2);
    }
    if (out1 < 0) {
        out1 = out2;    //if out1 is negative use the other one (out2)
        if (out1 < 0) {
            return false;
        }
    }
    //the closest intersect magnitude
    out = out1;

    return true;

}
