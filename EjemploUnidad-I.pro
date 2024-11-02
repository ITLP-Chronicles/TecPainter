QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bezier.cpp \
    linea.cpp \
    main.cpp \
    mainwindow.cpp \
    matriz.cpp \
    matriz2d.cpp \
    objeto2d.cpp \
    punto.cpp \
    punto3d.cpp \
    utils.cpp

HEADERS += \
    bezier.h \
    linea.h \
    mainwindow.h \
    matriz.h \
    matriz2d.h \
    objeto2d.h \
    punto.h \
    punto3d.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
