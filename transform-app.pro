TEMPLATE = app

QT += qml quick widgets sql

SOURCES += main.cpp \
    database.cpp \
    datastore.cpp \
    feedstore.cpp \
    datatransformer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    database.h \
    datastore.h \
    feedstore.h \
    datatransformer.h

