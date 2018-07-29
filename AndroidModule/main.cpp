//#include "qtquickcontrolsapplication.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include<QDebug>
#include <QQmlContext>
#include <QtPositioning/QGeoPositionInfoSource>
//#include <QQuickItem>
#include <QPropertyAnimation>
#include <iostream>
#include <QtQuick>
#include <thread>
#include "NetworkModule/OutMessage.h"
#include "NetworkModule/NetworkManager.h"
#include "NetworkModule/InMessage.h"
#include <string>

int main(int argc, char *argv[])
{

    
    QGuiApplication app(argc, argv);
    OutMessage myOutMessage;
    InMessage myInMessage;
    int IP1;
    NetworkManager myNetworkManager(&myOutMessage,&myInMessage);
    std::thread t1(&NetworkManager::networkLoop,&myNetworkManager);
    t1.detach();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myInMessage", &myInMessage);
    engine.rootContext()->setContextProperty("myOutMessage", &myOutMessage);
//    engine.rootContext()->setContextProperty("IP1", &IP1);
    
     engine.load(QUrl(QStringLiteral("qrc:/GUIModule/main.qml")));
     if (engine.rootObjects().isEmpty())
          return -1;
      return app.exec();

}
