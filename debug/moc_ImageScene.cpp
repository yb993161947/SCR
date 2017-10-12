/****************************************************************************
** Meta object code from reading C++ file 'ImageScene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ImageScene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ImageScene_t {
    QByteArrayData data[26];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageScene_t qt_meta_stringdata_ImageScene = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ImageScene"
QT_MOC_LITERAL(1, 11, 12), // "pointChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "index"
QT_MOC_LITERAL(4, 31, 14), // "doubleclicked1"
QT_MOC_LITERAL(5, 46, 15), // "QGraphicsScene*"
QT_MOC_LITERAL(6, 62, 5), // "scene"
QT_MOC_LITERAL(7, 68, 6), // "zoomIn"
QT_MOC_LITERAL(8, 75, 5), // "ratio"
QT_MOC_LITERAL(9, 81, 7), // "zoomOut"
QT_MOC_LITERAL(10, 89, 14), // "zoomInMatching"
QT_MOC_LITERAL(11, 104, 15), // "zoomOutMatching"
QT_MOC_LITERAL(12, 120, 11), // "setPixImage"
QT_MOC_LITERAL(13, 132, 7), // "Pix_Scr"
QT_MOC_LITERAL(14, 140, 12), // "loadDCMImage"
QT_MOC_LITERAL(15, 153, 8), // "FilePath"
QT_MOC_LITERAL(16, 162, 12), // "loadBMPImage"
QT_MOC_LITERAL(17, 175, 9), // "loadImage"
QT_MOC_LITERAL(18, 185, 7), // "cv::Mat"
QT_MOC_LITERAL(19, 193, 5), // "Image"
QT_MOC_LITERAL(20, 199, 17), // "loadMatchingImage"
QT_MOC_LITERAL(21, 217, 6), // "Pixmap"
QT_MOC_LITERAL(22, 224, 9), // "saveImage"
QT_MOC_LITERAL(23, 234, 15), // "setmouseConnect"
QT_MOC_LITERAL(24, 250, 1), // "a"
QT_MOC_LITERAL(25, 252, 14) // "ismouseConnect"

    },
    "ImageScene\0pointChanged\0\0index\0"
    "doubleclicked1\0QGraphicsScene*\0scene\0"
    "zoomIn\0ratio\0zoomOut\0zoomInMatching\0"
    "zoomOutMatching\0setPixImage\0Pix_Scr\0"
    "loadDCMImage\0FilePath\0loadBMPImage\0"
    "loadImage\0cv::Mat\0Image\0loadMatchingImage\0"
    "Pixmap\0saveImage\0setmouseConnect\0a\0"
    "ismouseConnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   95,    2, 0x0a /* Public */,
       9,    1,   98,    2, 0x0a /* Public */,
      10,    1,  101,    2, 0x0a /* Public */,
      11,    1,  104,    2, 0x0a /* Public */,
      12,    1,  107,    2, 0x0a /* Public */,
      14,    1,  110,    2, 0x0a /* Public */,
      16,    1,  113,    2, 0x0a /* Public */,
      17,    1,  116,    2, 0x0a /* Public */,
      20,    1,  119,    2, 0x0a /* Public */,
      20,    1,  122,    2, 0x0a /* Public */,
      22,    1,  125,    2, 0x0a /* Public */,
      23,    1,  128,    2, 0x0a /* Public */,
      25,    0,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::QPixmap,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::QPixmap,   21,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Bool,

       0        // eod
};

void ImageScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageScene *_t = static_cast<ImageScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pointChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->doubleclicked1((*reinterpret_cast< QGraphicsScene*(*)>(_a[1]))); break;
        case 2: _t->zoomIn((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->zoomOut((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->zoomInMatching((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->zoomOutMatching((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->setPixImage((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 7: _t->loadDCMImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->loadBMPImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->loadImage((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 10: _t->loadMatchingImage((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 11: _t->loadMatchingImage((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 12: _t->saveImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->setmouseConnect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: { bool _r = _t->ismouseConnect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsScene* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImageScene::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageScene::pointChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ImageScene::*_t)(QGraphicsScene * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageScene::doubleclicked1)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ImageScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_ImageScene.data,
      qt_meta_data_ImageScene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageScene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageScene.stringdata0))
        return static_cast<void*>(const_cast< ImageScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int ImageScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
void ImageScene::pointChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageScene::doubleclicked1(QGraphicsScene * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
