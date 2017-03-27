QT += sql

INCLUDEPATH += \
                $$PWD/common \
                $$PWD/controller \
                $$PWD/include \
                $$PWD/model

HEADERS += \
    $$PWD/controller/databasecontroller.h \
    $$PWD/model/dataaccess.h \
    $$PWD/include/DatabaseModule

SOURCES += \
    $$PWD/controller/databasecontroller.cpp \
    $$PWD/model/dataaccess.cpp
