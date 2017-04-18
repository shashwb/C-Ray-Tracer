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

#include "json_parser.h"

using namespace std;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    JSONParser parser;
    parser.Parse();

    return a.exec();
}
