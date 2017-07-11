/****************************************************************************
** Meta object code from reading C++ file 'capturevideowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../captureVideo/capturevideowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'capturevideowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CaptureVideoWidget_t {
    QByteArrayData data[16];
    char stringdata0[346];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CaptureVideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CaptureVideoWidget_t qt_meta_stringdata_CaptureVideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CaptureVideoWidget"
QT_MOC_LITERAL(1, 19, 15), // "processFinished"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "issuccessfully"
QT_MOC_LITERAL(4, 51, 9), // "timerSlot"
QT_MOC_LITERAL(5, 61, 12), // "lassoHandler"
QT_MOC_LITERAL(6, 74, 15), // "displaySrcImage"
QT_MOC_LITERAL(7, 90, 27), // "on_pushButton_Exit_released"
QT_MOC_LITERAL(8, 118, 32), // "on_pushButton_OpenVideo_released"
QT_MOC_LITERAL(9, 151, 30), // "on_pushButton_Capture_released"
QT_MOC_LITERAL(10, 182, 31), // "on_pushButton_OpenImage_clicked"
QT_MOC_LITERAL(11, 214, 29), // "on_pushButton_Process_clicked"
QT_MOC_LITERAL(12, 244, 32), // "on_checkBox_removeCircle_toggled"
QT_MOC_LITERAL(13, 277, 7), // "checked"
QT_MOC_LITERAL(14, 285, 29), // "on_radioButton_source_toggled"
QT_MOC_LITERAL(15, 315, 30) // "on_radioButton_refined_toggled"

    },
    "CaptureVideoWidget\0processFinished\0\0"
    "issuccessfully\0timerSlot\0lassoHandler\0"
    "displaySrcImage\0on_pushButton_Exit_released\0"
    "on_pushButton_OpenVideo_released\0"
    "on_pushButton_Capture_released\0"
    "on_pushButton_OpenImage_clicked\0"
    "on_pushButton_Process_clicked\0"
    "on_checkBox_removeCircle_toggled\0"
    "checked\0on_radioButton_source_toggled\0"
    "on_radioButton_refined_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CaptureVideoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   77,    2, 0x08 /* Private */,
       5,    0,   78,    2, 0x08 /* Private */,
       6,    0,   79,    2, 0x08 /* Private */,
       7,    0,   80,    2, 0x08 /* Private */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    1,   85,    2, 0x08 /* Private */,
      14,    1,   88,    2, 0x08 /* Private */,
      15,    1,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void CaptureVideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CaptureVideoWidget *_t = static_cast<CaptureVideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->timerSlot(); break;
        case 2: _t->lassoHandler(); break;
        case 3: _t->displaySrcImage(); break;
        case 4: _t->on_pushButton_Exit_released(); break;
        case 5: _t->on_pushButton_OpenVideo_released(); break;
        case 6: _t->on_pushButton_Capture_released(); break;
        case 7: _t->on_pushButton_OpenImage_clicked(); break;
        case 8: _t->on_pushButton_Process_clicked(); break;
        case 9: _t->on_checkBox_removeCircle_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_radioButton_source_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_radioButton_refined_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CaptureVideoWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CaptureVideoWidget::processFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CaptureVideoWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CaptureVideoWidget.data,
      qt_meta_data_CaptureVideoWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CaptureVideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CaptureVideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CaptureVideoWidget.stringdata0))
        return static_cast<void*>(const_cast< CaptureVideoWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CaptureVideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CaptureVideoWidget::processFinished(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
