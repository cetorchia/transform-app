TEMPLATE = app

QT += qml quick widgets sql

SOURCES += main.cpp \
    myobject.cpp \
    feed.cpp \
    record.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    myobject.h \
    feed.h \
    record.h

