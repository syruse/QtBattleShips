#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "objectlistwrapper.h"
#include "marker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<Marker>("marker", 1, 0, "Marker", "Can not instantiate State from QML");

    ObjectListWrapper wrapper;

    if(!wrapper.initialize())
        return -1;

    return app.exec();
}
