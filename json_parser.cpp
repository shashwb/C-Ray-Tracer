#include "json_parser.h"
#include <iostream>

using namespace std;

JSONParser::JSONParser()
{
}

/*
 * This needs to take in a file to parse
 */
bool JSONParser::Parse() {

    qDebug() << "in the parse() function" << endl;


    QFile jsonFile("/Users/sethbalodi/CODE/proj3_temp/main.json");

    qDebug() << jsonFile.fileName();

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

        QJsonObject jObject = doc.object();

        QVariantMap mainMap = jObject.toVariantMap();

        //get response variant map
        QVariantMap responseMap = mainMap["response"].toMap();

        //get the width and height of image
//        wallpaper.width = responseMap["width"].toInt();
        wallpaper.width = responseMap["width"].toInt();
        wallpaper.height = responseMap["height"].toInt();

        //get the image url
        QVariantMap imageMap = responseMap["image"].toMap();
        wallpaper.url = imageMap["url"].toString();

        //get the preview image details
        QVariantMap previewMap = imageMap["preview"].toMap();
        wallpaper.previewWidth = previewMap["width"].toInt();
        wallpaper.previewHeight = previewMap["height"].toInt();
        wallpaper.previewUrl = previewMap["url"].toString();

         //get the thumbnail details
        QVariantMap thumbMap = imageMap["thumb"].toMap();
        wallpaper.thumbWidth = thumbMap["width"].toInt();
        wallpaper.thumbHeight = thumbMap["height"].toInt();
        wallpaper.thumbUrl = thumbMap["url"].toString();

        wallpaper.printAll();

        return true;
    }

    return false;
}
