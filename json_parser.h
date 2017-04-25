#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QJsonParseError>
#include <QVariant>
#include <QDebug>
#include <QIODevice>
#include <QByteArray>
#include <QVariantMap>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <vector>

#include "lights.h"
#include "sphere.h"
#include "camera.h"
#include "plane.h"
#include "mother_of_objects.h"


using namespace std;

struct Pixel {
    Coordinate coordinate;
    Color color;
};

//double dotProduct(const Coordinate &coordinate_one, const Coordinate &coordinate_two) {
//    return (coordinate_one.x*coordinate_two.x + coordinate_one.y*coordinate_two.y + coordinate_one.z*coordinate_two.z);
//}


class JSONParser
{
public:

    //PARSER WILL STORE MEMBER VARIABLES OF SPHERE AND PLANE ETC

    Sphere sphere;  // we don't need a premade one
    Lights light;   //we don't need a premade one, made once we read in the json
    Plane plane;
    Camera camera;


    vector<MotherOfObjects*> vecObjects;

    vector<Sphere> *vecSphere;
    vector<Plane> *vecPlane;
    vector<Lights> vecLights;
    vector<Coordinate> *vecPixels;
    JSONParser();

    bool Parse();
    Ray createPrimaryRay();

    Ray shadowRayTracer(Coordinate poi, MotherOfObjects* object);

private:



};

#endif // JSON_PARSER_H
