QT += quick
QT += network
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    NetworkModule/TCPServer.cpp \
    NetworkModule/NetworkManager.cpp \
    main.cpp \

HEADERS += \
#    qtquickcontrolsapplication.h \
    NetworkModule/TCPServer.h \
    NetworkModule/NetworkManager.h \
    NetworkModule/OutMessage.h \
    NetworkModule/InMessage.h \
#    car.h \ 
#    qtquickcontrolsapplication.h

RESOURCES += resources/qml.qrc resources/imageresources.qrc

DESTDIR = debug
OBJECTS_DIR = debug/.obj
MOC_DIR = debug/.moc
RCC_DIR = debug/.rccc
UI_DIR = debug/.ui


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GUIModule/functions.js \
    GUIModule/functions.jsc \
    GUIModule/AutopilotTab.qmlc \
    GUIModule/main.qmlc \
    GUIModule/MyCustomSlider.qmlc \
    GUIModule/WaypointTab.qmlc \
    GUIModule/HeadingAutopilot.qml \
    GUIModule/main.qml \
    GUIModule/MyCustomSlider.qml \
    GUIModule/WaypointTab.qml

