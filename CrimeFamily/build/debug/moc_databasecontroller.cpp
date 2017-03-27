/****************************************************************************
** Meta object code from reading C++ file 'databasecontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/DatabaseModule/controller/databasecontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'databasecontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DatabaseController_t {
    QByteArrayData data[17];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DatabaseController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DatabaseController_t qt_meta_stringdata_DatabaseController = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DatabaseController"
QT_MOC_LITERAL(1, 19, 13), // "getDataFinish"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "value"
QT_MOC_LITERAL(4, 40, 15), // "update_caseInfo"
QT_MOC_LITERAL(5, 56, 2), // "id"
QT_MOC_LITERAL(6, 59, 4), // "mode"
QT_MOC_LITERAL(7, 64, 15), // "remove_caseInfo"
QT_MOC_LITERAL(8, 80, 16), // "update_crimeInfo"
QT_MOC_LITERAL(9, 97, 16), // "remove_crimeInfo"
QT_MOC_LITERAL(10, 114, 23), // "update_relationshipInfo"
QT_MOC_LITERAL(11, 138, 23), // "remove_relationshipInfo"
QT_MOC_LITERAL(12, 162, 16), // "display_waitting"
QT_MOC_LITERAL(13, 179, 15), // "display_message"
QT_MOC_LITERAL(14, 195, 7), // "message"
QT_MOC_LITERAL(15, 203, 13), // "display_error"
QT_MOC_LITERAL(16, 217, 20) // "handle_message_error"

    },
    "DatabaseController\0getDataFinish\0\0"
    "value\0update_caseInfo\0id\0mode\0"
    "remove_caseInfo\0update_crimeInfo\0"
    "remove_crimeInfo\0update_relationshipInfo\0"
    "remove_relationshipInfo\0display_waitting\0"
    "display_message\0message\0display_error\0"
    "handle_message_error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatabaseController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    2,   72,    2, 0x06 /* Public */,
       7,    1,   77,    2, 0x06 /* Public */,
       8,    2,   80,    2, 0x06 /* Public */,
       9,    1,   85,    2, 0x06 /* Public */,
      10,    2,   88,    2, 0x06 /* Public */,
      11,    1,   93,    2, 0x06 /* Public */,
      12,    1,   96,    2, 0x06 /* Public */,
      13,    1,   99,    2, 0x06 /* Public */,
      15,    1,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Long, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Long,    5,
    QMetaType::Void, QMetaType::Long, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Long,    5,
    QMetaType::Void, QMetaType::Long, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Long,    5,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   14,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   14,

       0        // eod
};

void DatabaseController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DatabaseController *_t = static_cast<DatabaseController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getDataFinish((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->update_caseInfo((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->remove_caseInfo((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 3: _t->update_crimeInfo((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->remove_crimeInfo((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 5: _t->update_relationshipInfo((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->remove_relationshipInfo((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 7: _t->display_waitting((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->display_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->display_error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->handle_message_error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DatabaseController::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::getDataFinish)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(long , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::update_caseInfo)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::remove_caseInfo)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(long , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::update_crimeInfo)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::remove_crimeInfo)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(long , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::update_relationshipInfo)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::remove_relationshipInfo)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::display_waitting)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::display_message)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (DatabaseController::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DatabaseController::display_error)) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject DatabaseController::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DatabaseController.data,
      qt_meta_data_DatabaseController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DatabaseController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DatabaseController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DatabaseController.stringdata0))
        return static_cast<void*>(const_cast< DatabaseController*>(this));
    return QThread::qt_metacast(_clname);
}

int DatabaseController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DatabaseController::getDataFinish(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DatabaseController::update_caseInfo(long _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DatabaseController::remove_caseInfo(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DatabaseController::update_crimeInfo(long _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DatabaseController::remove_crimeInfo(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DatabaseController::update_relationshipInfo(long _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DatabaseController::remove_relationshipInfo(long _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DatabaseController::display_waitting(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DatabaseController::display_message(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DatabaseController::display_error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
