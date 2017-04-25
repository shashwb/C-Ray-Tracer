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


void pngViewer(JSONParser parser, QString outputName) {

    vector<Pixels *> pixels = parser.pixelsVector;

    //image init
    int width = parser.camera->size.size_one;
    int height = parser.camera->size.size_two;

    QImage pngImage(width, height, QImage::Format_RGB32);

    //go through pixels list
    for (int i = 0; i < pixels.size(); i++) {
        QRgb rgb_value;
        rgb_value = qRgb(pixels[i]->color.r, pixels[i]->color.g, pixels[i]->color.b);
        pngImage.setPixel(pixels[i]->coordinate.x, pixels[i]->coordinate.y, rgb_value);

    }
    pngImage.save("save.png");
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    JSONParser parser;

    if (argc < 3) {
        return EXIT_FAILURE;
    }
    else if (argc == 3) {
        QFile inputFile(argv[1]);
        QTextStream streamParse(&inputFile);
        if (!inputFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            return EXIT_FAILURE;
        }
        if (parser.Parse(streamParse, 1)) {
            return EXIT_FAILURE;
        }
        else {
            pngViewer(parser, QString::fromStdString(argv[2]));
        }
        return EXIT_SUCCESS;
    }
    else if (argc == 5) {

        QFile inputFile(argv[3]);
        QTextStream streamParse(&inputFile);
        int threads;

//        else if (string(argv[2]) == "-t") {
//            threads = stoii(argv[1]);
//        }

    }

    return a.exec();
}
