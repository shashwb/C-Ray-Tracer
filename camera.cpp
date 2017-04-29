#include "camera.h"

Camera::Camera()
{
  cout << endl;
  cout << "CREATED CAMERA OBJECT" << endl;
  cout << endl;
}


Camera::Camera(Coordinate center_value, int focus_value,
       Coordinate normal_value, Resolution res_value, Size size_value) {

    center = center_value;
    focus = focus_value;
    normal = normal_value;
    resolution = res_value;

}

void Camera::print() {
    qDebug() << "created a Camera object";
    // cout << endl;
    // cout << "created a new Camera object" << endl;
    // cout << endl;
}
