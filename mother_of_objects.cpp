#include "mother_of_objects.h"

MotherOfObjects::MotherOfObjects()
{
}

void MotherOfObjects::print() {
    //can't really happen
    qDebug() << "MotherOfAllObjects created";
}

Coordinate MotherOfObjects::getColor() {
    return this->color;
}

void MotherOfObjects::setColor(Color color) {
    this->color.x = color.r;
    this->color.y = color.g;
    this->color.z = color.b;
}

void MotherOfObjects::setCenter(Coordinate center_value) {
    this->center.x = center_value.x;
    this->center.y = center_value.y;
    this->center.z = center_value.z;
}

Coordinate MotherOfObjects::getCenter() {
    return this->center;
}

double MotherOfObjects::getRadius() {
    return this->radius;
}

void MotherOfObjects::setRadius(double radius_value) {
    this->radius = radius_value;
}



