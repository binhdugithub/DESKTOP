/****************************************************************************
** Meta object code from reading C++ file 'crimetreeform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/CrimeTreeModule/form/crimetreeform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'crimetreeform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CrimeTreeForm_t {
    QByteArrayData data[8];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CrimeTreeForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CrimeTreeForm_t qt_meta_stringdata_CrimeTreeForm = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CrimeTreeForm"
QT_MOC_LITERAL(1, 14, 28), // "handle_btnAddNewCase_clicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 26), // "handle_btnEditCase_clicked"
QT_MOC_LITERAL(4, 71, 25), // "handle_btnDelCase_clicked"
QT_MOC_LITERAL(5, 97, 28), // "handle_btnAcceptCase_clicked"
QT_MOC_LITERAL(6, 126, 28), // "handle_btnCancelCase_clicked"
QT_MOC_LITERAL(7, 155, 37) // "handle_tableCase_itemSelectio..."

    },
    "CrimeTreeForm\0handle_btnAddNewCase_clicked\0"
    "\0handle_btnEditCase_clicked\0"
    "handle_btnDelCase_clicked\0"
    "handle_btnAcceptCase_clicked\0"
    "handle_btnCancelCase_clicked\0"
    "handle_tableCase_itemSelectionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CrimeTreeForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       3,    1,   47,    2, 0x08 /* Private */,
       4,    1,   50,    2, 0x08 /* Private */,
       5,    1,   53,    2, 0x08 /* Private */,
       6,    1,   56,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void CrimeTreeForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CrimeTreeForm *_t = static_cast<CrimeTreeForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handle_btnAddNewCase_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->handle_btnEditCase_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->handle_btnDelCase_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->handle_btnAcceptCase_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->handle_btnCancelCase_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->handle_tableCase_itemSelectionChanged(); break;
        default: ;
        }
    }
}

const QMetaObject CrimeTreeForm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CrimeTreeForm.data,
      qt_meta_data_CrimeTreeForm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CrimeTreeForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CrimeTreeForm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CrimeTreeForm.stringdata0))
        return static_cast<void*>(const_cast< CrimeTreeForm*>(this));
    return QObject::qt_metacast(_clname);
}

int CrimeTreeForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
