#include "json_parser.h"
#include "lights.h"
#include "camera.h"

#include <iostream>

using namespace std;

JSONParser::JSONParser()
{
  cout << "PARSER CREATED" << endl;
}



bool JSONParser::Parse(QTextStream &stream, int num) {

    QFile jsonFile("/Users/sethbalodi/CODE/proj3_temp/scene0.json");
    // /Users/sethbalodi/CODE/proj3_temp/scene0.json

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file, exiting....";
        return false;
    }

    QByteArray jsonData = jsonFile.readAll();
    cout << "JSON Data:" << endl;
    cout << jsonData.toStdString() << endl;

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

        QJsonObject jObject = doc.object();
        QVariantMap mainMap = jObject.toVariantMap();

        //ALL CAMERA PARSING
        QVariantMap cameraMap = mainMap["camera"].toMap();

            //camera center
        QVariantMap camera_centerMap = cameraMap["center"].toMap();

        camera.center.x = camera_centerMap["x"].toDouble();
        camera.center.y = camera_centerMap["y"].toDouble();
        camera.center.z = camera_centerMap["z"].toDouble();

            //camera focus
        camera.focus = cameraMap["focus"].toInt();

            //camera normal
        QVariantMap normalMap = cameraMap["normal"].toMap();
        camera.normal.x = normalMap["x"].toDouble();
        camera.normal.y = normalMap["y"].toDouble();
        camera.normal.z = normalMap["z"].toDouble();


        QVariantList resolutionList = cameraMap["resolution"].toList();
        camera.resolution.resolution_one = resolutionList.first().toDouble();
        camera.resolution.resolution_two = resolutionList.at(1).toDouble();

        QVariantList sizeList = cameraMap["size"].toList();
        camera.size.size_one = sizeList.first().toDouble();
        camera.size.size_two = sizeList.at(1).toDouble();

        QJsonArray jsonLights = jObject["lights"].toArray();

        //size of this array?
        cout << "*******size of Light list? : " << jsonLights.size() << endl;

        QVariantMap lightsMap = mainMap["lights"].toMap();

        for (QJsonValue lightsValue : jsonLights) {
		        QJsonObject lightObj = lightsValue.toObject();
            light.intensity = lightObj["intensity"].toDouble();

            QVariantMap lightVariant = lightObj.toVariantMap();
            QVariantMap lightLocationMap = lightVariant["location"].toMap();
            light.loc.x = lightLocationMap["x"].toDouble();
            light.loc.y = lightLocationMap["y"].toDouble();
            light.loc.z = lightLocationMap["z"].toDouble();
	      }


        QJsonArray jsonObjects = jObject["objects"].toArray();
        QVariantMap objectsMap = mainMap["objects"].toMap();

        cout << endl;
        cout << "////// OBJECTS" << endl;

        for (QJsonValue objectsValue : jsonObjects) {
          QJsonObject objectObj = objectsValue.toObject();
          if (objectObj["type"].toString() == "sphere") {
            cout << endl;
            cout << "THIS FUCKING OBJECT IS A SPHERE" << endl;

            //create a new sphere
            Sphere newSphere;

            QVariantMap objectVariant = objectObj.toVariantMap();
            QVariantMap objectCenter = objectVariant["center"].toMap();
            QVariantMap objectColor = objectVariant["color"].toMap();
            newSphere.center.x = objectCenter["x"].toDouble();
            newSphere.center.y = objectCenter["y"].toDouble();
            newSphere.center.z = objectCenter["z"].toDouble();
            cout << "newphere->center.x: " << newSphere.center.x << endl;
            cout << "newSphere->center.y: " << newSphere.center.y << endl;
            cout << "newSphere->center.z: " << newSphere.center.z << endl;

            sphere.color.x = objectColor["r"].toInt();
            sphere.color.y = objectColor["g"].toInt();
            sphere.color.z = objectColor["b"].toInt();
            cout << "Sphere->color.x: " << sphere.color.x << endl;
            cout << "Sphere->color.y: " << sphere.color.y << endl;
            cout << "Sphere->color.z: " << sphere.color.z << endl;

            sphere.lambert = objectObj["lambert"].toDouble();
            sphere.radius = objectObj["radius"].toDouble();

            cout << "Sphere->lambert: " << sphere.lambert << endl;
            cout << "Sphere->radius: " << sphere.radius << endl;

            vecObjects.push_back(&newSphere);

          }

          else if (objectObj["type"].toString() == "plane") {
            cout << endl;
            cout << "THIS FUCKING OBJECT IS A PLANE" << endl;
            QVariantMap objectVariant = objectObj.toVariantMap();
            QVariantMap objectCenter = objectVariant["center"].toMap();
            QVariantMap objectColor = objectVariant["color"].toMap();
            QVariantMap objectNormal = objectVariant["normal"].toMap();

            Plane newPlane;

            newPlane.center.x = objectCenter["x"].toDouble();
            newPlane.center.y = objectCenter["y"].toDouble();
            newPlane.center.z = objectCenter["z"].toDouble();
            cout << "newPlane->center.x: " << newPlane.center.x << endl;
            cout << "newPlane->center.y: " << newPlane.center.y << endl;
            cout << "newPlane->center.z: " << newPlane.center.z << endl;

            plane.color.x = objectColor["r"].toInt();
            plane.color.y = objectColor["g"].toInt();
            plane.color.z = objectColor["b"].toInt();
            cout << "Plane->color.x: " << plane.color.x << endl;
            cout << "Plane->color.y: " << plane.color.y << endl;
            cout << "Plane->color.z: " << plane.color.z << endl;

            plane.lambert = objectObj["lambert"].toDouble();
            cout << "Plane->lambert: " << plane.lambert << endl;

            plane.normal.x = objectNormal["x"].toDouble();
            plane.normal.y = objectNormal["y"].toDouble();
            plane.normal.z = objectNormal["z"].toDouble();
            cout << "Plane->normal.x: " << plane.normal.x << endl;
            cout << "Plane->normal.y: " << plane.normal.y << endl;
            cout << "Plane->normal.z: " << plane.normal.z << endl;

            vecObjects.push_back(&newPlane);

          }
          else {
            cout << "NOT A VALID TYPE OF OBJECT FROM JSON, EXITING" << endl;
            return false;

          }
        }

        cout << endl;
        cout << "SIZE OF THE OBJECT VECTOR: " << vecObjects.size() << endl;

      cout << endl;
      cout << "////// CAMERA" << endl;
      cout << "Camera->center.x: " << camera.center.x << endl;
      cout << "Camera->center.y: " << camera.center.y << endl;
      cout << "Camera->center.z: " << camera.center.z << endl;
      cout << "Camera->focus: " << camera.focus << endl;
      cout << "Camera->normal.x: " << camera.normal.x << endl;
      cout << "Camera->normal.y: " << camera.normal.y << endl;
      cout << "Camera->normal.z: " << camera.normal.z << endl;
      cout << "Camera->size: " << camera.size.size_one << " " << camera.size.size_two << endl;
      cout << "Camera->resolution: " << camera.resolution.resolution_one << " " << camera.resolution.resolution_two << endl;

      cout << endl;
      cout << "////// LIGHTS" << endl;
      cout << "Light->intensity: " << light.intensity << endl;
      cout << "LIGHT INTENSITY -> " << light.intensity << endl;
      cout << "LIGHT LOCATION x -> " << light.loc.x << endl;
      cout << "LIGHT LOCATION y -> " << light.loc.y << endl;
      cout << "LIGHT LOCATION z -> " << light.loc.z << endl;

        return true;
    }

    return false;
}




Ray JSONParser::createPrimaryRay() {
    int height = camera.size.size_one;
    int width = camera.size.size_two;

    cout << "the height: " << height << endl;
    cout << "the width: " << width << endl;

    Ray exampleRay;

    Sphere *tempSphere;  //this will store the object that is intersected
    MotherOfObjects *tempObject;
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
    } //end of forloop i
    return exampleRay;
}

Ray JSONParser::calculatePrimaryRay(int i, int j) {
    Coordinate first_point = camera.center - camera.normal * camera.focus;
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
