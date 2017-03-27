#-------------------------------------------------
#
# Project created by QtCreator 2017-03-13T15:25:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CrimeFamily
TEMPLATE = app

#------------------ Include + Libs ----------------
include(src/DatabaseModule/DatabaseModule.pri)
include(src/CrimeTreeModule/CrimeTreeModule.pri)

INCLUDEPATH += \
                common \
                common/UserControl \
                src/DatabaseModule/include \
                src/CrimeTreeModule/include \
                $$PROTOBUF_PATH/include \
                $$PROTOBUF_PATH/model
#win32
#{
#    CONFIG(debug, debug|release)
#    {
#        LIBS += \
#            -L$$PROTOBUF_PATH/lib -llibprotobufd \
#            -L$$PROTOBUF_PATH/lib -llibprotobuf-lited \
#            -L$$PROTOBUF_PATH/lib -llibprotocd

#        QMAKE_RPATHDIR += $$PROTOBUF_PATH/lib -llibprotobufd \
#                                $$PROTOBUF_PATH/lib -llibprotobuf-lited \
#                                $$PROTOBUF_PATH/lib -llibprotocd
#    }
#    CONFIG(release, debug|release)
#    {
#        LIBS += \
#            -L$$PROTOBUF_PATH/lib -llibprotobuf \
#            -L$$PROTOBUF_PATH/lib -llibprotobuf-lite \
#            -L$$PROTOBUF_PATH/lib -llibprotoc

#        QMAKE_RPATHDIR += $$PROTOBUF_PATH/lib -llibprotobuf \
#                                $$PROTOBUF_PATH/lib -llibprotobuf-lite \
#                                $$PROTOBUF_PATH/lib -llibprotoc
#    }

#}
SOURCES += main.cpp\
        crimetreewindow.cpp \
    common/settings.cpp \
    common/datacommon.cpp \
    common/UserControl/slidingstackedwidget.cpp \
    common/UserControl/waitingspinnerwidget.cpp \
    common/UserControl/flowlayout.cpp

HEADERS  += crimetreewindow.h \
    common/global.h \
    common/log.h \
    common/settings.h \
    common/datacommon.h \
    common/UserControl/slidingstackedwidget.h \
    common/UserControl/waitingspinnerwidget.h \
    common/UserControl/flowlayout.h

RESOURCES += \
    resources/resources.qrc
