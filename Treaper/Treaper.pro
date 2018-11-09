#-------------------------------------------------
#
# Project created by QtCreator 2018-10-17T10:50:27
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Treaper
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Assets/DataStructures/MQueues/otherfuncs.cpp \
    adddatastructure.cpp \
    myqdatastructure.cpp \
    addunit.cpp \
    splitqueues.cpp \
    mergedialog.cpp \
    thunderstruckabout.cpp \
    aboutdatastructure.cpp

HEADERS += \
    mainwindow.h \
    Assets/DataStructures/MQueues/implicit_treap_node.h \
    Assets/DataStructures/MQueues/mergequeue.h \
    Assets/DataStructures/MQueues/otherfuncs.h \
    adddatastructure.h \
    myqdatastructure.h \
    addunit.h \
    splitqueues.h \
    mergedialog.h \
    thunderstruckabout.h \
    aboutdatastructure.h

FORMS += \
        mainwindow.ui \
    adddatastructure.ui \
    addunit.ui \
    splitqueues.ui \
    mergedialog.ui \
    thunderstruckabout.ui \
    aboutdatastructure.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    interfaceicons.qrc
