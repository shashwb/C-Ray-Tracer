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
#include <QImage>

#include "mother_of_objects.h"
#include "json_parser.h"
#include "sphere.h"
#include "plane.h"

using namespace std;


void pngViewer(JSONParser parser) {

     vector<Pixels *> pixels = parser.pixelsVector;

     //image init
     int width = parser.camera.size.size_one;
     int height = parser.camera.size.size_two;

     QImage pngImage(width, height, QImage::Format_RGB32);

     //go through pixels list
     for (int i = 0; i < pixels.size(); i++) {
         QRgb rgb_value;
         //these need to be changed to an actual "color" struct!!!!
         rgb_value = qRgb(pixels[i]->color.x, pixels[i]->color.y, pixels[i]->color.z);
         pngImage.setPixel(pixels[i]->coordinate.x, pixels[i]->coordinate.y, rgb_value);
     }
     pngImage.save("save.png");
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "MAIN FUNCTION" << endl;

    JSONParser parser;

//    if (argc < 3) {
//        cout << "Too little arguments!" << endl;
//        return EXIT_FAILURE;
//    }
//    else if (argc == 4) {

        cout << "proper number of arguments!" << endl;

        QFile inputFile(argv[2]);

        cout << "input file: " << argv[2] << endl;

        QTextStream streamParse(&inputFile);

//        if (!inputFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
//          cout << "cannot open device" << endl;
//            return EXIT_FAILURE;
//        }
//        if (!parser.Parse(streamParse, 1)) {
//          cout << "why does this fail?" << endl;
//            return EXIT_FAILURE;
//        }
//        else {
          cout << "everything else looks good! Procced!" << endl;
          parser.Parse(streamParse, 1); //default number of threads

          // Ray primaryRay = parser.createPrimaryRay();
          parser.createPrimaryRay();

          pngViewer(parser);

            // pngViewer(parser, QString::fromStdString(argv[2]));
//        }
        return EXIT_SUCCESS;
//    }
//    else if (argc >= 5) {
//      cout << "way too many arguments, calm down there buddy!" << endl;
//        return EXIT_FAILURE;
//
//    }

    return a.exec();
}
