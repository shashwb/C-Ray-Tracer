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

    QFile jsonFile("/Users/sethbalodi/CODE/proj3_temp/scene0.json");
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file, exiting....";
        return false;
    }

    QByteArray jsonData = jsonFile.readAll();
//    cout << "JSON Data:" << endl;
//    cout << jsonData.toStdString() << endl;
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

        cout << endl;
        cout << "////// LIGHTS" << endl;
        cout << "size of the vecLights before everything: " << vecLights.size() << endl;
        vecLights.clear();
        cout << "clearing...." << endl;
        cout << "size of vecLights after clearing: " << vecLights.size() << endl;

        for (QJsonValue lightsValue : jsonLights) {
		        QJsonObject lightObj = lightsValue.toObject();

            Lights newLight;

            newLight.intensity = lightObj["intensity"].toDouble();
            cout << "newLight->intensity: " << newLight.intensity << endl;

            QVariantMap lightVariant = lightObj.toVariantMap();
            QVariantMap lightLocationMap = lightVariant["location"].toMap();
            newLight.loc.x = lightLocationMap["x"].toDouble();
            newLight.loc.y = lightLocationMap["y"].toDouble();
            newLight.loc.z = lightLocationMap["z"].toDouble();
            cout << "newLight LOCATION x -> " << newLight.loc.x << endl;
            cout << "newLight LOCATION y -> " << newLight.loc.y << endl;
            cout << "newLight LOCATION z -> " << newLight.loc.z << endl;

            vecLights.push_back(&newLight);

            cout << "PUSH BACK A LIGHT, current size of vector: " << vecLights.size() << endl;
            cout << endl;
	      }


        QJsonArray jsonObjects = jObject["objects"].toArray();
        QVariantMap objectsMap = mainMap["objects"].toMap();

        cout << endl;
        cout << "////// OBJECTS" << endl;
        cout << "size of vecObjects before everything: " << vecObjects.size() << endl;
        vecObjects.clear();
        cout << "clearing...." << endl;
        cout << "size of vecObjects after clearing: " << vecObjects.size() << endl;

        for (QJsonValue objectsValue : jsonObjects) {
          QJsonObject objectObj = objectsValue.toObject();
          if (objectObj["type"].toString() == "sphere") {
            cout << endl;
            cout << "THIS FUCKING OBJECT IS A SPHERE" << endl;

            //create a new sphere
            // MotherOfObjects newSphere = new Sphere;
//            MotherOfObjects *newSphere = new Sphere;

            // newSphere.type = objectObj["type"].toString();

            QVariantMap objectVariant = objectObj.toVariantMap();
            QVariantMap objectCenter = objectVariant["center"].toMap();
            QVariantMap objectColor = objectVariant["color"].toMap();
              
            Coordinate center_value(objectCenter["x"].toDouble(), objectCenter["y"].toDouble(), objectCenter["z"].toDouble());
            Coordinate color_value(objectColor["r"].toInt(), objectColor["g"].toInt(), objectColor["b"].toInt());
            double lambert_value = objectObj["lambert"].toDouble();
            double radius_value = objectObj["lambert"].toDouble();
              
            Sphere *newSphere = new Sphere(center_value, color_value, lambert_value, radius_value);
//              Sphere newSphere = new Sphere(center_value, color_value, lambert_value, radius);
              
//            newSphere->
//            newSphere->center.x = objectCenter["x"].toDouble();
//            newSphere->center.y = objectCenter["y"].toDouble();
//            newSphere->center.z = objectCenter["z"].toDouble();
//            cout << "newphere->center.x: " << newSphere->center.x << endl;
//            cout << "newSphere->center.y: " << newSphere->center.y << endl;
//            cout << "newSphere->center.z: " << newSphere->center.z << endl;
//
//            newSphere->color.x = objectColor["r"].toInt();
//            newSphere->color.y = objectColor["g"].toInt();
//            newSphere->color.z = objectColor["b"].toInt();
//            cout << "newSphere->color.x: " << newSphere->color.x << endl;
//            cout << "newSphere->color.y: " << newSphere->color.y << endl;
//            cout << "newSphere->color.z: " << newSphere->color.z << endl;

//            newSphere->lambert = objectObj["lambert"].toDouble();
//            newSphere->radius = objectObj["radius"].toDouble();

            cout << "newSphere->lambert: " << newSphere->lambert << endl;
            cout << "newSphere->radius: " << newSphere->radius << endl;

            vecObjects.push_back(newSphere);
            cout << "PUSHED BACK A SPHERE, current size of vector: " << vecObjects.size() << endl;

          }

          else if (objectObj["type"].toString() == "plane") {
            cout << endl;
            cout << "THIS FUCKING OBJECT IS A PLANE" << endl;

            QVariantMap objectVariant = objectObj.toVariantMap();
            QVariantMap objectCenter = objectVariant["center"].toMap();
            QVariantMap objectColor = objectVariant["color"].toMap();
            QVariantMap objectNormal = objectVariant["normal"].toMap();
              
//              Plane newPlane
              
              
              
              Coordinate center_value(objectCenter["x"].toDouble(), objectCenter["y"].toDouble(), objectCenter["z"].toDouble());
              Coordinate color_value(objectColor["r"].toInt(), objectColor["g"].toInt(), objectColor["b"].toInt());
              Coordinate normal_value(objectNormal["x"].toInt(), objectNormal["y"].toInt(), objectNormal["z"].toInt());
              double lambert_value = objectObj["lambert"].toDouble();
              
              
              Plane *newPlane = new Plane(center_value, normal_value, color_value, lambert_value);
              
//              double radius_value = objectObj["lambert"].toDouble();
              

//            MotherOfObjects *newPlane = new Plane;
//
//            newPlane->center.x = objectCenter["x"].toDouble();
//            newPlane->center.y = objectCenter["y"].toDouble();
//            newPlane->center.z = objectCenter["z"].toDouble();
//            cout << "newPlane->center.x: " << newPlane->center.x << endl;
//            cout << "newPlane->center.y: " << newPlane->center.y << endl;
//            cout << "newPlane->center.z: " << newPlane->center.z << endl;
//
//            newPlane->color.x = objectColor["r"].toInt();
//            newPlane->color.y = objectColor["g"].toInt();
//            newPlane->color.z = objectColor["b"].toInt();
//            cout << "newPlane->color.x: " << newPlane->color.x << endl;
//            cout << "newPlane->color.y: " << newPlane->color.y << endl;
//            cout << "newPlane->color.z: " << newPlane->color.z << endl;
//
//            newPlane->lambert = objectObj["lambert"].toDouble();
//            cout << "newPlane->lambert: " << newPlane->lambert << endl;
//
//            newPlane->normal.x = objectNormal["x"].toDouble();
//            newPlane->normal.y = objectNormal["y"].toDouble();
//            newPlane->normal.z = objectNormal["z"].toDouble();
//            cout << "newPlane->normal.x: " << newPlane->normal.x << endl;
//            cout << "newPlane->normal.y: " << newPlane->normal.y << endl;
//            cout << "newPlane->normal.z: " << newPlane->normal.z << endl;

            vecObjects.push_back(newPlane);
            cout << "PUSHED BACK A PLANE, current size of vector: " << vecObjects.size() << endl;
          }
          else {
            cout << "NOT A VALID TYPE OF OBJECT FROM JSON, EXITING" << endl;
            return false;
          }
        }
        cout << endl;
        cout << "FINAL SIZE OF THE OBJECT VECTOR: " << vecObjects.size() << endl;

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
        return true;
    }
    return false;
}


void JSONParser::createPrimaryRay() {

    cout << "IN THE PRIMARY RAY FUNCTION" << endl;

    int height = camera.size.size_one;
    int width = camera.size.size_two;

    cout << "the height (pixels): " << height << endl;
    cout << "the width (pixels): " << width << endl;

    Ray finalRay;

    cout << "____SIZE OF OBJECT VECTOR: " << vecObjects.size() << endl;
    cout << endl;
    cout << endl;

   MotherOfObjects *tempObject;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {

        // cout << "RAY is being send through pixel value: (" << i << "," << j << ")";
        Ray primaryRay = calculatePrimaryRay(i, j);
        double nearest_t;

           if (i == 62 && j == 118) {
               cout << "______BREAKPOINT" << endl;
           }

        for (int k = 0; k < vecObjects.size(); k++) {

//            cout << "iteration of k---> " << k << endl;

          tempObject = vecObjects[k];

            if (tempObject->intersect(primaryRay, nearest_t)) {
//                 cout << endl;
//                 cout << "nearest intersection" << nearest_t << endl;
//                 cout << "SUCCESS :: this intersects at point: (" << i << "," << j << ")" << endl;
//                 cout << endl;

                //because it intersected, we have to run the shadow ray
                //point of intersection
                
                
                if (i == 62 && j == 118) {
                    cout << endl;
                    cout << "::::::::::::::::::::::::::::::::::::::::::::WE DID IT!!!!" << endl;
                    cout << endl;
                }
                else {
                    cout << "___________________________________________THIS IS NOT THE PROPER INTERSECTION" << endl;
                }
                
                
                cout << endl;
                cout << "*********intersecting at: (" << i << "," << j <<  ")" << endl;
                Coordinate poi = primaryRay.origin + primaryRay.direction * nearest_t;
                shadowRayTracer(poi, tempObject, i, j);

          }
          else {
              // cout << " ::::: DOES NOT INTERSECT DOE" << endl;
              //return a black pixel, but we can just do this in the shadow function
            }
        }
      }
    }

    // return finalRay;
}


Ray JSONParser::calculatePrimaryRay(int i, int j) {

    Coordinate first_point = camera.center - camera.normal * camera.focus;
//    Coordinate second_point(i, j, 0);
    Coordinate second_point;
    second_point.x = camera.resolution.resolution_two*(i - (camera.size.size_two / 2));
    second_point.y = camera.resolution.resolution_one*(j - (camera.size.size_one / 2));
    second_point.z = 0;

    Coordinate temporary = second_point - first_point;
    Coordinate direction = temporary.normalize();

    Ray finalRay;
    finalRay.origin = first_point;
    finalRay.direction = direction;

    primaryRay.origin = first_point;
    primaryRay.direction = direction;

    return finalRay;
}


//pass in the point of intersection
void JSONParser::shadowRayTracer(Coordinate pointOfIntersection, MotherOfObjects* object, int i, int j) {

  cout << "IN THE SHADOW RAY FUNCTION" << endl;
    
    double max_intensity = 0;

    //this is where we check the lights

    for (int vecIndex = 0; vecIndex < vecLights.size(); vecIndex++) {
        cout << "FIRST VECLIGHTS LOOP" << endl;
        Coordinate p2 = vecLights.at(vecIndex)->loc - pointOfIntersection;
        cout << "FIRST VECLIGHT LOOP PAST COORDINATE" << endl;
        Coordinate p2_normal = p2.normalize();
        //create shadow ray
        Ray shadowRay(pointOfIntersection, p2_normal);
        cout << "Ray origin -> " << shadowRay.origin.x << " " << shadowRay.origin.y << " " << shadowRay.origin.z << endl;
        
        
        cout << "Ray direction -> " << shadowRay.direction.x << " " << shadowRay.direction.y << " " << shadowRay.direction.z << endl;
        double nearest_t;

         //MotherOfObjects *tempObjects;
        
        
        
        
        
            //get the light intensity, make sure it's MAX of all lights
            //compare to previous maximum, store this value
            //calculations can be outside
            //scale inside
            
            double scale = object->normal.dotProduct(shadowRay.direction) * object->lambert;
            
            if (vecLights[vecIndex]->intensity > max_intensity) {
                max_intensity = vecLights[vecIndex]->intensity;
            }
            
            if (scale > 0) {
                //overload multiplication
                Coordinate pixel_color = object->color * scale * max_intensity;
                Pixels *newPixel = new Pixels;
                //CHANGE THIS TO RGB
                newPixel->coordinate.x = i;
                newPixel->coordinate.y = j;
                newPixel->coordinate.z = 0;
                newPixel->color = pixel_color;
                pixelsVector.push_back(newPixel);
            }
        
        
        
        for (int vecObj = 0; vecObj < vecObjects.size(); vecObj++) {
            
            cout << "VECOBJECTS FOR LOOP" << endl;

            if (object != vecObjects.at(vecObj)) {
//            if (true) {
            
                //if the object is not in this
                cout << "INSIDE OF WHERE I SET THE PIXELS" << endl;

               // tempObjects = ;
                
                cout << "value of nearest_t: " << nearest_t << endl;

                if (vecObjects[vecObj]->intersect(shadowRay, nearest_t)) {
//                if (true) {
                    
                  Pixels *newPixel = new Pixels;
                  //CHANGE THIS TO RGB
                  newPixel->coordinate.x = i;
                  newPixel->coordinate.y = j;
                  newPixel->coordinate.z = 0;
                  newPixel->color.x = 0;
                  newPixel->color.y = 0;
                  newPixel->color.z = 0;
                  pixelsVector.push_back(newPixel);

                  cout << "pushed pixel at coordinates (" << newPixel->coordinate.x << "," << newPixel->coordinate.y << ")" << endl;

                  // break;
                }
            }
            else {
                cout << "NO INTERSETCT for shadowRay to light" << endl;
            }
        }

        cout << "Size of Pixels Array: " << pixelsVector.size() << endl;
        cout << endl;
        cout << endl;

    }
}
