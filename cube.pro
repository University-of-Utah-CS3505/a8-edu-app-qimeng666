HEADERS += \
    cube.h

SOURCES += \
    cube.cpp \
    main.cpp

QT   += core gui opengl

greaterThan(QT_MAJOR_VERSION,4):QT +=widgets

LIBS += -lGLU

CONFIG += c++11

RESOURCES += \
    res.qrc
