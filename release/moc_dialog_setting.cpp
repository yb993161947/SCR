/****************************************************************************
** Meta object code from reading C++ file 'dialog_setting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialog_setting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_setting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Dialog_Setting_t {
    QByteArrayData data[21];
    char stringdata0[421];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_Setting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_Setting_t qt_meta_stringdata_Dialog_Setting = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Dialog_Setting"
QT_MOC_LITERAL(1, 15, 7), // "setPort"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "loadData_Femur_AP"
QT_MOC_LITERAL(4, 42, 18), // "loadData_Femur_Lat"
QT_MOC_LITERAL(5, 61, 17), // "loadData_Tibia_AP"
QT_MOC_LITERAL(6, 79, 18), // "loadData_Tibia_Lat"
QT_MOC_LITERAL(7, 98, 14), // "InitMarkerName"
QT_MOC_LITERAL(8, 113, 14), // "QList<QString>"
QT_MOC_LITERAL(9, 128, 4), // "Name"
QT_MOC_LITERAL(10, 133, 15), // "setTypeofDevice"
QT_MOC_LITERAL(11, 149, 12), // "TypeofDevice"
QT_MOC_LITERAL(12, 162, 4), // "type"
QT_MOC_LITERAL(13, 167, 24), // "on_pushButtonUDP_clicked"
QT_MOC_LITERAL(14, 192, 30), // "on_pushButton_Femur_AP_clicked"
QT_MOC_LITERAL(15, 223, 31), // "on_pushButton_Femur_Lat_clicked"
QT_MOC_LITERAL(16, 255, 30), // "on_pushButton_Tibia_AP_clicked"
QT_MOC_LITERAL(17, 286, 31), // "on_pushButton_Tibia_Lat_clicked"
QT_MOC_LITERAL(18, 318, 32), // "on_pushButton_InitMarker_clicked"
QT_MOC_LITERAL(19, 351, 32), // "on_radioButton_TypeofNDI_clicked"
QT_MOC_LITERAL(20, 384, 36) // "on_radioButton_TypeofTracker_..."

    },
    "Dialog_Setting\0setPort\0\0loadData_Femur_AP\0"
    "loadData_Femur_Lat\0loadData_Tibia_AP\0"
    "loadData_Tibia_Lat\0InitMarkerName\0"
    "QList<QString>\0Name\0setTypeofDevice\0"
    "TypeofDevice\0type\0on_pushButtonUDP_clicked\0"
    "on_pushButton_Femur_AP_clicked\0"
    "on_pushButton_Femur_Lat_clicked\0"
    "on_pushButton_Tibia_AP_clicked\0"
    "on_pushButton_Tibia_Lat_clicked\0"
    "on_pushButton_InitMarker_clicked\0"
    "on_radioButton_TypeofNDI_clicked\0"
    "on_radioButton_TypeofTracker_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_Setting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    0,   92,    2, 0x06 /* Public */,
       4,    0,   93,    2, 0x06 /* Public */,
       5,    0,   94,    2, 0x06 /* Public */,
       6,    0,   95,    2, 0x06 /* Public */,
       7,    1,   96,    2, 0x06 /* Public */,
      10,    1,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  102,    2, 0x08 /* Private */,
      14,    0,  103,    2, 0x08 /* Private */,
      15,    0,  104,    2, 0x08 /* Private */,
      16,    0,  105,    2, 0x08 /* Private */,
      17,    0,  106,    2, 0x08 /* Private */,
      18,    0,  107,    2, 0x08 /* Private */,
      19,    0,  108,    2, 0x08 /* Private */,
      20,    0,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialog_Setting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_Setting *_t = static_cast<Dialog_Setting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setPort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->loadData_Femur_AP(); break;
        case 2: _t->loadData_Femur_Lat(); break;
        case 3: _t->loadData_Tibia_AP(); break;
        case 4: _t->loadData_Tibia_Lat(); break;
        case 5: _t->InitMarkerName((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 6: _t->setTypeofDevice((*reinterpret_cast< TypeofDevice(*)>(_a[1]))); break;
        case 7: _t->on_pushButtonUDP_clicked(); break;
        case 8: _t->on_pushButton_Femur_AP_clicked(); break;
        case 9: _t->on_pushButton_Femur_Lat_clicked(); break;
        case 10: _t->on_pushButton_Tibia_AP_clicked(); break;
        case 11: _t->on_pushButton_Tibia_Lat_clicked(); break;
        case 12: _t->on_pushButton_InitMarker_clicked(); break;
        case 13: _t->on_radioButton_TypeofNDI_clicked(); break;
        case 14: _t->on_radioButton_TypeofTracker_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Dialog_Setting::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog_Setting::setPort)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Dialog_Setting::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog_Setting::loadData_Femur_AP)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Dialog_Setting::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog_Setting::loadData_Femur_Lat)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Dialog_Setting::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog_Setting::loadData_Tibia_AP)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Dialog_Setting::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog_Setting::loadData_Tibia_Lat)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Dialog_Setting::*_t)(QList<QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog_Setting::InitMarkerName)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Dialog_Setting::*_t)(TypeofDevice );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog_Setting::setTypeofDevice)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject Dialog_Setting::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_Setting.data,
      qt_meta_data_Dialog_Setting,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dialog_Setting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_Setting::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_Setting.stringdata0))
        return static_cast<void*>(const_cast< Dialog_Setting*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog_Setting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Dialog_Setting::setPort(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dialog_Setting::loadData_Femur_AP()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Dialog_Setting::loadData_Femur_Lat()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Dialog_Setting::loadData_Tibia_AP()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Dialog_Setting::loadData_Tibia_Lat()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Dialog_Setting::InitMarkerName(QList<QString> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Dialog_Setting::setTypeofDevice(TypeofDevice _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
