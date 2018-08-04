//#include "qtquickcontrolsapplication.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include<QDebug>
#include <QQmlContext>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QNetworkInterface>
//#include <QQuickItem>
#include <QPropertyAnimation>
#include <iostream>
#include <QtQuick>
#include <thread>
#include "NetworkModule/Outbox.h"
#include "NetworkModule/NetworkManager.h"
#include "NetworkModule/Inbox.h"
#include <string>

int main(int argc, char *argv[])
{

    
    QGuiApplication app(argc, argv);
    Outbox myOutbox;
    Inbox myInbox;
    NetworkManager myNetworkManager(&myOutbox,&myInbox);
    std::thread t1(&NetworkManager::RpiCommunicationTask,&myNetworkManager);
    t1.detach();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myInbox", &myInbox);
    engine.rootContext()->setContextProperty("myOutbox", &myOutbox);
    
     engine.load(QUrl(QStringLiteral("qrc:/GUIModule/main.qml")));
     if (engine.rootObjects().isEmpty())
          return -1;
      return app.exec();

}
