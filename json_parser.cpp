#include "json_parser.h"
#include "lights.h"
#include "camera.h"
#include <typeinfo>
#include <iostream>
#include "mother_of_objects.h"

using namespace std;

JSONParser::JSONParser()
{
  cout << "PARSER CREATED" << endl;
}



bool JSONParser::Parse(QTextStream &stream, int num) {

    QFile jsonFile("/Users/sethbalodi/CODE/project3-shashwb/tests/scene0.json");
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

        QVariantMap cameraMap = mainMap["camera"].toMap();
        QVariantMap camera_centerMap = cameraMap["center"].toMap();

        //DEBUGGING CODE
//        double double_val = 0;
//        string double_type = typeid(double_val).name();
//        cout << "****TYPE OF DOUBLE VAL : " << double_type << endl;
//        int int_val = 20;
//        string int_type = typeid(int_val).name();
//        cout << "****TYPE OF INT VAL : " << int_type << endl;
//        string camera_type_x = typeid(camera.center.x).name();
//        cout << "******TYPE OF CAMERA CENTER X -> " << camera_type_x << endl;
//        string camera_type_y = typeid(camera_centerMap["y"].toDouble()).name();
//        string camera_type_z = typeid(camera_centerMap["z"].toDouble()).name();
//        if (camera_type_x != double_type || camera_type_y != double_type || camera_type_z != double_type) {
//          cout << "ERROR: did not parse a valid double value into camera center" << endl;
//          return false;
//        }
        //DEBUGGING CODE

        cout << "SUCCESS: parsed a valid double value" << endl;

        camera.center.x = camera_centerMap["x"].toDouble();
        camera.center.y = camera_centerMap["y"].toDouble();
        camera.center.z = camera_centerMap["z"].toDouble();
        camera.focus = cameraMap["focus"].toInt();
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
        QVariantMap lightsMap = mainMap["lights"].toMap();

        vecLights.clear();


        for (QJsonValue lightsValue : jsonLights) {
            QJsonObject lightObj = lightsValue.toObject();
            QVariantMap lightVariant = lightObj.toVariantMap();
            QVariantMap lightLocationMap = lightVariant["location"].toMap();
            double intensity_value = lightObj["intensity"].toDouble();
            Coordinate location_value(lightLocationMap["x"].toDouble(), lightLocationMap["y"].toDouble(), lightLocationMap["y"].toDouble());
            Lights *newLight = new Lights(location_value, intensity_value);
            vecLights.push_back(newLight);
            cout << "PUSH BACK A LIGHT, current size of vector: " << vecLights.size() << endl;
            cout << endl;
	      }


        QJsonArray jsonObjects = jObject["objects"].toArray();
        QVariantMap objectsMap = mainMap["objects"].toMap();


        for (QJsonValue objectsValue : jsonObjects) {
          QJsonObject objectObj = objectsValue.toObject();
          if (objectObj["type"].toString() == "sphere") {

            QVariantMap objectVariant = objectObj.toVariantMap();
            QVariantMap objectCenter = objectVariant["center"].toMap();
            QVariantMap objectColor = objectVariant["color"].toMap();
              
            Coordinate center_value(objectCenter["x"].toDouble(), objectCenter["y"].toDouble(), objectCenter["z"].toDouble());
            Color color_value(objectColor["r"].toInt(), objectColor["g"].toInt(), objectColor["b"].toInt());
            double lambert_value = objectObj["lambert"].toDouble();
            double radius_value = objectObj["lambert"].toDouble();
            QString type = objectObj["type"].toString();
            string type_value = type.toStdString();
              
            Sphere *newSphere = new Sphere(center_value, color_value, lambert_value, radius_value, type_value);
            newSphere->setColor(color_value);
            newSphere->setCenter(center_value);
            newSphere->setRadius(radius_value);

            vecObjects.push_back(newSphere);
            cout << "PUSHED BACK A SPHERE, current size of vector: " << vecObjects.size() << endl;

          }
          else if (objectObj["type"].toString() == "plane") {
            QVariantMap objectVariant = objectObj.toVariantMap();
            QVariantMap objectCenter = objectVariant["center"].toMap();
            QVariantMap objectColor = objectVariant["color"].toMap();
            QVariantMap objectNormal = objectVariant["normal"].toMap();
              
            Coordinate center_value(objectCenter["x"].toDouble(), objectCenter["y"].toDouble(), objectCenter["z"].toDouble());
            Coordinate color_value(objectColor["r"].toInt(), objectColor["g"].toInt(), objectColor["b"].toInt());
            Coordinate normal_value(objectNormal["x"].toInt(), objectNormal["y"].toInt(), objectNormal["z"].toInt());
            double lambert_value = objectObj["lambert"].toDouble();
              
            Plane *newPlane = new Plane(center_value, normal_value, color_value, lambert_value);
//              newPlane->setColor(color_value);
              newPlane->type = "plane";
            vecObjects.push_back(newPlane);
            cout << "PUSHED BACK A PLANE, current size of vector: " << vecObjects.size() << endl;
          }
          else {
            cout << "NOT A VALID TYPE OF OBJECT FROM JSON, EXITING" << endl;
            return false;
          }
        }
        return true;
    }
    return false;
}














void JSONParser::createPrimaryRay() {

    int height = camera.size.size_one;
    int width = camera.size.size_two;
    MotherOfObjects *tempObject;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {

        Ray primaryRay = calculatePrimaryRay(i, j);
        double nearest_t = 0;

        for (int k = 0; k < vecObjects.size(); k++) {

          tempObject = vecObjects[k];

            if (vecObjects[k]->intersect(primaryRay, nearest_t)) {
                
                if (i == 62 && j == 118) {
                    cout << endl;
                    cout << "::::::::::::::::::::::::::::::::::::::::::::" << endl;
                    cout << "::::::::::::::::::::::::::::::::::::::::::::" << endl;
                    cout << "::::::::::::::::::::::::::::::::::::::::::::" << endl;
                    cout << "::::::::::::::::::::::::::::::::::::::::::::WE DID IT!!!!" << endl;
                    cout << "::::::::::::::::::::::::::::::::::::::::::::" << endl;
                    cout << "::::::::::::::::::::::::::::::::::::::::::::" << endl;
                    cout << "::::::::::::::::::::::::::::::::::::::::::::" << endl;
                    cout << endl;
                }
                    cout << "___________________________________________" << endl;
                
                
                cout << endl;
                cout << "*********intersecting at: (" << i << "," << j <<  ")" << endl;
                Coordinate poi = primaryRay.origin + primaryRay.direction * nearest_t;
                shadowRayTracer(poi, tempObject, i, j);

            } else {
                cout << "pixel value: (" << i << "," << j << ") did not intersect" << endl;
            }
        }
      }
    }
}











Ray JSONParser::calculatePrimaryRay(int i, int j) {

    Coordinate first_point = camera.center - camera.normal * camera.focus;
    Coordinate second_point;
    second_point.x = camera.resolution.resolution_two*(i - (camera.size.size_two / 2));
    second_point.y = camera.resolution.resolution_one*(j - (camera.size.size_one / 2));
    second_point.z = 10;

    Coordinate temporary = second_point - first_point;
    Coordinate direction = temporary.normalize();

    Ray finalRay;
    finalRay.origin = first_point;
    finalRay.direction = direction;

//    primaryRay.origin = first_point;
//    primaryRay.direction = direction;

    return finalRay;
}













void JSONParser::shadowRayTracer(Coordinate pointOfIntersection, MotherOfObjects* object, int i, int j) {
    
    double max_intensity = 0;
    double scale = 0;
    
    for (int vecIndex = 0; vecIndex < vecLights.size(); vecIndex++) {
        
        Coordinate p2 = vecLights[vecIndex]->loc - pointOfIntersection;
        Coordinate p2_normal = p2.normalize();
        
        Ray shadowRay(pointOfIntersection, p2_normal);
        double nearest_t;
        
        for (int vecObj = 0; vecObj < vecObjects.size(); vecObj++) {
            
            if (object != vecObjects.at(vecObj)) {
                
                cout << "////////////////////////////////////////" << endl;
                cout << "shadow ray intersects" << endl;
                cout << "////////////////////////////////////////" << endl;
                cout << endl;

                if (vecObjects[vecObj]->intersect(shadowRay, nearest_t)) {
                  Pixels *newPixel = new Pixels;
                  //CHANGE THIS TO RGB
                  newPixel->coordinate.x = i;
                  newPixel->coordinate.y = j;
                  newPixel->coordinate.z = 0;
                  newPixel->color.r = 0;
                  newPixel->color.g = 0;
                  newPixel->color.b = 0;
                  pixelsVector.push_back(newPixel);

                  cout << "pushed pixel at coordinates (" << newPixel->coordinate.x << "," << newPixel->coordinate.y << ")" << endl;
                }
            }
        }
        
        if (object->type.compare("sphere")) {
            cout << "INSIDE SPHERE COMPARE" << endl;
            Coordinate sphereNormal = pointOfIntersection - object->center;
            double lam_value = vecObjects[vecIndex]->lambert;
            double scale_addition = sphereNormal.dotProduct(shadowRay.direction) * lam_value;
            scale = scale + scale_addition;
        }
        
        // iterating through the entire vector, set the maximum light intensity of all of the lights
        if (vecLights[vecIndex]->intensity > max_intensity) {
            max_intensity = vecLights[vecIndex]->intensity;
            cout << "MAX INTENSITY SET: " << max_intensity << endl;
        }
        
        if (scale > 0) {
            cout << "THE SCALE IS ->" << scale << endl;
            Coordinate object_color = object->getColor();
            Coordinate pixel_color = object_color * scale * max_intensity;
            Pixels *newPixel = new Pixels;
            newPixel->coordinate.x = i;
            newPixel->coordinate.y = j;
            newPixel->coordinate.z = 0;
            newPixel->color.r = pixel_color.x;
            newPixel->color.g = pixel_color.y;
            newPixel->color.b = pixel_color.z;
            pixelsVector.push_back(newPixel);
            
            cout << "pushed pixel at coordinates (" << newPixel->coordinate.x << "," << newPixel->coordinate.y << ")" << endl;
            cout << "Size of Pixels Array: " << pixelsVector.size() << endl;
            cout << endl;
            cout << endl;
        }
        

    }
}
