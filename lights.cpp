#include "lights.h"

Lights::Lights()
{

}

Lights::Lights(Coordinate location_value, double intensity_value) {

    this->loc = location_value;
    this->intensity = intensity_value;

}

void Lights::print() {
    qDebug() << "created Light object from inheritance";
}
