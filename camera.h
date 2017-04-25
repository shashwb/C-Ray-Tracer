#ifndef CAMERA_H
#define CAMERA_H

#include <QDebug>

#include "mother_of_objects.h"


class Camera
{

    struct Size {
        int size_one;
        int size_two;
    };

    struct Resolution {
        double resolution_one;
        double resolution_two;
    };


public:

    Camera();

    Camera(Coordinate center_value, int focus_value, Coordinate normal_value, Resolution res_value, Size size_value);

    void print();

    Coordinate center;
    Coordinate normal;
    int focus;
    Size size;
    Resolution resolution;
    string type;

private:



};

#endif // CAMERA_H
