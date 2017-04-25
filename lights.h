#ifndef LIGHTS_H
#define LIGHTS_H

#include <QDebug>

#include "mother_of_objects.h"



class Lights
{

public:

    Coordinate loc;
    double intensity;


    Lights();

    Lights(Coordinate location_value, double intensity_value);

    void print();



private:



};

#endif // LIGHTS_H
