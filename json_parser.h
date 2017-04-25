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
#include <QImage>

#include <vector>

#include "lights.h"
#include "sphere.h"
#include "camera.h"
#include "plane.h"
#include "mother_of_objects.h"


using namespace std;

struct Pixels {
    Coordinate coordinate;
    Color color;
};



class JSONParser
{
public:

    Sphere *sphere;  // we don't need a premade one
    Lights *light;   //we don't need a premade one, made once we read in the json
    Plane *plane;
    Camera *camera;


    vector<MotherOfObjects*> vecObjects;
    Ray primaryRay;

    vector<Sphere> *vecSphere;
    vector<Plane> *vecPlane;
    vector<Lights> vecLights;

    vector<Pixels *> pixelsVector;

    JSONParser();

//    bool Parse();
    bool Parse(QTextStream &stream, int num);
    Ray createPrimaryRay();

    Ray shadowRayTracer(Coordinate poi, MotherOfObjects* object);
    Ray calculatePrimaryRay(int i, int j);

private:



};

#endif // JSON_PARSER_H
