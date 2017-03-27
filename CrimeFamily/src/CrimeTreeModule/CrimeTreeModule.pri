INCLUDEPATH += \
                $$PWD/common \
                $$PWD/common/UserControl \
                $$PWD/controller \
                $$PWD/include \
                $$PWD/form \
                $$PWD/model \
                $$PWD/views

HEADERS += \
    $$PWD/controller/crimetreecontroller.h \
    $$PWD/include/CrimeTreeModule \
    $$PWD/form/crimetreeform.h \
    $$PWD/views/casemanagementview.h \
    $$PWD/views/crimetreeview.h \
    $$PWD/common/UserControl/treegraphicsview.h \
    $$PWD/views/crimedetailview.h \
    $$PWD/common/UserControl/crimegraphicsitem.h \
    $$PWD/common/UserControl/relationshipgraphicsitem.h \
    $$PWD/views/relationshipdetailview.h

SOURCES += \
    $$PWD/controller/crimetreecontroller.cpp \
    $$PWD/form/crimetreeform.cpp \
    $$PWD/views/casemanagementview.cpp \
    $$PWD/views/crimetreeview.cpp \
    $$PWD/common/UserControl/treegraphicsview.cpp \
    $$PWD/views/crimedetailview.cpp \
    $$PWD/common/UserControl/crimegraphicsitem.cpp \
    $$PWD/common/UserControl/relationshipgraphicsitem.cpp \
    $$PWD/views/relationshipdetailview.cpp
