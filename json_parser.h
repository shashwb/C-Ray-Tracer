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
#include <string>
#include <QString>

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

    Camera camera;

    vector<MotherOfObjects*> vecObjects;  //vector of objects!!
    vector<Lights*> vecLights;
    vector<Pixels*> pixelsVector;

    JSONParser();
    bool Parse(QTextStream &stream, int num);
    void createPrimaryRay();
    void shadowRayTracer(Coordinate poi, MotherOfObjects* object, int i, int j);
    Ray calculatePrimaryRay(int i, int j);

};

#endif // JSON_PARSER_H
