#include "json_parser.h"
#include "lights.h"
#include "camera.h"

#include <iostream>

using namespace std;

JSONParser::JSONParser()
{

}



bool JSONParser::Parse(QTextStream &stream, int num) {

    QFile jsonFile("/Users/sethbalodi/CODE/proj3_temp/scene0.json");

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file, exiting....";
        return false;
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonParseError *err = new QJsonParseError();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, err);

    if (err->error != 0) {
        qDebug() << err->errorString();
    }

    if (doc.isNull()) {
        qDebug() << "Invalid json document, exiting...";
        return false;
    }

    else if (doc.isObject()) {

//        Sphere *newSphere;
//        newSphere->center.x = 80;
//        newSphere->center.y = 40;
//        newSphere->center.z = 10;

//        Plane *newPlane;
//        newPlane->center.x = 600;
//        newPlane->center.y = 300;
//        newPlane->center.z = 200;


//        vecObjects.push_back(newSphere);
//        vecObjects.push_back(newPlane);

//        cout << "SIZE OF VECOBJECTS: " << vecObjects.size() << endl;

//        for (int i = 0; i < vecObjects.size(); i++) {
//            cout << endl;
//            cout << "values inside" << vecObjects.at(i) << endl;
//            cout << endl;
//        }


        QJsonObject jObject = doc.object();
        QVariantMap mainMap = jObject.toVariantMap();

        //ALL CAMERA PARSING
        QVariantMap cameraMap = mainMap["camera"].toMap();

            //camera center
        QVariantMap camera_centerMap = cameraMap["center"].toMap();
        camera->center.x = camera_centerMap["x"].toDouble();
        camera->center.y = camera_centerMap["y"].toDouble();
        camera->center.z = camera_centerMap["z"].toDouble();

            //camera focus
        camera->focus = cameraMap["focus"].toInt();

            //camera normal
        QVariantMap normalMap = cameraMap["normal"].toMap();
        camera->normal.x = normalMap["x"].toDouble();
        camera->normal.y = normalMap["y"].toDouble();
        camera->normal.z = normalMap["z"].toDouble();


        QVariantList resolutionList = cameraMap["resolution"].toList();
        cout << "resolutionList size: " << resolutionList.size() << endl;
        camera->resolution.resolution_one = resolutionList.first().toDouble();
        camera->resolution.resolution_two = resolutionList.at(1).toDouble();

        QVariantList sizeList = cameraMap["size"].toList();
        camera->size.size_one = resolutionList.first().toDouble();
        camera->size.size_two = resolutionList.at(1).toDouble();
        //FINISH CAMERA PARSING


        //LIGHT PARSING
        QVariantMap lightMap = mainMap["lights"].toMap();
        light->intensity = lightMap["intensity"].toDouble();

        QVariantMap lightMap_location = lightMap["location"].toMap();
        light->loc.x = lightMap_location["x"].toDouble();
        light->loc.y = lightMap_location["y"].toDouble();
        light->loc.z = lightMap_location["z"].toDouble();
        //FINISH LIGHT PARSING

        QVariantList objectsList = mainMap["objects"].toList();
        cout << "objectList size: " << objectsList.size() << endl;

        QJsonValue objects = jObject.value("objects");
        QJsonArray objectsArray = objects.toArray();
        foreach (const QJsonValue & v, objectsArray) {
            qDebug() << "objects lambert value: " << v.toObject().value("lambert").toDouble();
//            qDebug() << "objects radius value: " << v.toObject();
        }

        qDebug() << "CAMERA->Center: x equals " << camera->center.x;
        qDebug() << "CAMERA->Center: y equals " << camera->center.y;
        qDebug() << "CAMERA->Center: z equals " << camera->center.z;
        qDebug() << "CAMERA->focus " << camera->focus;

        qDebug() << "CAMERA->normal.x : " << camera->normal.x;
        qDebug() << "CAMERA->normal.y : " << camera->normal.y;
        qDebug() << "CAMERA->normal.z : " << camera->normal.z;

        qDebug() << "CAMERA->resolution[1]: " << resolutionList.first().toDouble();
        qDebug() << "CAMERA->resolution[2]: " << resolutionList.at(1).toDouble();

        qDebug() << "CAMERA->size[1]: " << sizeList.first().toDouble();
        qDebug() << "CAMERA->size[2]: " << sizeList.at(1).toDouble();

        //lights
        qDebug() << "Lights.intensity : " << light->intensity;
        qDebug() << "Lights.loc.x : " << light->loc.x;
        qDebug() << "Lights.loc.y : " << light->loc.y;
        qDebug() << "Lights.loc.z : " << light->loc.z;

        qDebug() << "DEBUG OBJECT CENTER X" << sphere->center.x;
        qDebug() << "DEBUG OBJECT CENTER Y" << sphere->center.y;
        qDebug() << "DEBUG OBJECT CENTER Z" << sphere->center.z;

        qDebug() << "DEBUG OBJECT COLOR R" << sphere->center.x;
        qDebug() << "DEBUG OBJECT COLOR G" << sphere->center.y;
        qDebug() << "DEBUG OBJECT COLOR B" << sphere->center.z;

        qDebug() << "DEBUG OBJECT LAMBERT" << sphere->lambert;
        qDebug() << "DEBUG OBJECT RADIUS" << sphere->radius;

        return true;
    }

    return false;
}




Ray JSONParser::createPrimaryRay() {
    int height = camera->size.size_one;
    int width = camera->size.size_two;

    cout << "the height: " << height << endl;
    cout << "the width: " << width << endl;

    Sphere *tempSphere;  //this will store the object that is intersected
    Pixels pixel;

    //iterate through all pixels
    for (int i = 0; i < height; i++) {
        for (int j = 0; i < width; j++) {

            //calculate primary ray
            //JUST DO THIS ENTIRE FUNCTION ALL IN HERE!
            Ray primaryRay = calculatePrimaryRay(i, j); //NEED TO CALCULATE THIS <- call primary ray function

            double nearest_t = INFINITY;
            bool intersect =  false;

            for (int object_iterator = 0; object_iterator < vecSphere->size(); object_iterator++) {
                tempSphere = &vecSphere->at(object_iterator);
                intersect = tempSphere->intersect(primaryRay, nearest_t);
                if (intersect) {
                    //if it intersects, then mark the place
                    tempSphere = &vecSphere->at(object_iterator);
                }
            }
            //if it doesn't hit an object
//            if (tempSphere == nullptr) {
            if (true) {
                pixel.coordinate.x = i;
                pixel.coordinate.y = j;
                pixel.coordinate.z = 0;
                pixel.color.r = 0;
                pixel.color.g = 0;
                pixel.color.b = 0;
            }
            else {
                //callShadowRay function()

                //get the point of intersection to pass into the callshadow ray function!
            }

        }
    }
}

Ray JSONParser::calculatePrimaryRay(int i, int j) {
    Coordinate first_point = camera->center - camera->normal * camera->focus;
    Coordinate second_point(i, j, 0);

    Coordinate temporary = second_point - first_point;
    Coordinate direction = temporary; // need to normalize this shit

    Ray finalRay;
    finalRay.origin = first_point;
    finalRay.direction = direction;

    primaryRay.origin = first_point;
    primaryRay.direction = direction;

    return finalRay;
}


//pass in the point of intersection
Ray JSONParser::shadowRayTracer(Coordinate poi, MotherOfObjects* object) {

    //this is where we check the lights
    double nearest_t;

    for (int i = 0; i < vecLights.size(); i++) {
        Coordinate p2 = vecLights.at(i).loc - poi;
        //create shadow ray
        Ray shadowRay(poi, p2);

        for (int j = 0; j < vecObjects.size(); j++) {
            if (object != vecObjects.at(j)) {

                //if it doesn't intersect the same object
                //if intersects another object, then color black
                if (vecObjects[j]->intersect(shadowRay, nearest_t)) {
                    break;
                }
                else {
//                    double scale = vecObjects.at(j)->normal.dotProduct(shadowRay) * vecObjects.at(j)->lambert;
//                    Coordinate pixel_color = scale * vecLights.at(i).intensity * vecObjects.at(i)->color;

                }

            }

        }

    }


}
