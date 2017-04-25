#include "camera.h"

Camera::Camera()
{

}


Camera::Camera(Coordinate center_value, int focus_value,
       Coordinate normal_value, Resolution res_value, Size size_value) {

    this->center = center_value;
    this->focus = focus_value;
    this->normal = normal_value;
    this->resolution = res_value;

}

void Camera::print() {
    qDebug() << "created a Camera object";
}
