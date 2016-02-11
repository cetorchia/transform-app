TEMPLATE = app

QT += qml quick widgets sql network xml

SOURCES += main.cpp \
    database.cpp \
    datastore.cpp \
    feedstore.cpp \
    datatransformer.cpp \
    regextransformer.cpp \
    csvexporter.cpp \
    urlextractor.cpp \
    treemodel.cpp \
    pathextransformer.cpp \
    treeparser.cpp \
    queryelementlistmodel.cpp

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
    datatransformer.h \
    regextransformer.h \
    csvexporter.h \
    urlextractor.h \
    treemodel.h \
    pathextransformer.h \
    treeparser.h \
    queryelementlistmodel.h

CONFIG += c++11
