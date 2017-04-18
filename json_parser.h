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



struct DeskWallpaper {
      int width;
      int height;
      QString url;

      int previewWidth;
      int previewHeight;
      QString previewUrl;

      int thumbWidth;
      int thumbHeight;
      QString thumbUrl;

      void printAll() {
          qDebug() << "Image width: " << this->width;
          qDebug() << "Image height: " << height;
          qDebug() << "Image url: " << url;

          qDebug() << "Preview width: " << previewWidth;
          qDebug() << "Preview height: " << previewHeight;
          qDebug() << "Preview url: " << previewUrl;

          qDebug() << "Thumb width: " << thumbWidth;
          qDebug() << "Thumb height: " << thumbHeight;
          qDebug() << "Thumb url: " << thumbUrl;
      }
  };



class JSONParser
{
public:

    //PARSER WILL STORE MEMBER VARIABLES OF SPHERE AND PLANE ETC

    DeskWallpaper wallpaper;

    JSONParser();

    bool Parse();

private:

    //store all the variables here

};

#endif // JSON_PARSER_H
