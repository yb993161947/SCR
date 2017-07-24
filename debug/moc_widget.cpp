/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CArmAngleCalCuLate/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CArmWidget_t {
    QByteArrayData data[9];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CArmWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CArmWidget_t qt_meta_stringdata_CArmWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CArmWidget"
QT_MOC_LITERAL(1, 11, 32), // "on_pushButtonOpenPicture_clicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 37), // "on_textEditReferenceValue_tex..."
QT_MOC_LITERAL(4, 83, 25), // "on_lineEdit_B_textChanged"
QT_MOC_LITERAL(5, 109, 4), // "arg1"
QT_MOC_LITERAL(6, 114, 29), // "on_lineEdit_ankle_textChanged"
QT_MOC_LITERAL(7, 144, 28), // "on_radioButton_femur_clicked"
QT_MOC_LITERAL(8, 173, 28) // "on_radioButton_tibia_clicked"

    },
    "CArmWidget\0on_pushButtonOpenPicture_clicked\0"
    "\0on_textEditReferenceValue_textChanged\0"
    "on_lineEdit_B_textChanged\0arg1\0"
    "on_lineEdit_ankle_textChanged\0"
    "on_radioButton_femur_clicked\0"
    "on_radioButton_tibia_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CArmWidget[] = {

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
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    1,   46,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,
       7,    0,   52,    2, 0x08 /* Private */,
       8,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CArmWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CArmWidget *_t = static_cast<CArmWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonOpenPicture_clicked(); break;
        case 1: _t->on_textEditReferenceValue_textChanged(); break;
        case 2: _t->on_lineEdit_B_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_lineEdit_ankle_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_radioButton_femur_clicked(); break;
        case 5: _t->on_radioButton_tibia_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject CArmWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CArmWidget.data,
      qt_meta_data_CArmWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CArmWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CArmWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CArmWidget.stringdata0))
        return static_cast<void*>(const_cast< CArmWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CArmWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
