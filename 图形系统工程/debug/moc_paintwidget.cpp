/****************************************************************************
** Meta object code from reading C++ file 'paintwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../paintwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PaintWidget_t {
    QByteArrayData data[15];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintWidget_t qt_meta_stringdata_PaintWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PaintWidget"
QT_MOC_LITERAL(1, 12, 15), // "setCurrentShape"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "Shape::shapeChoice"
QT_MOC_LITERAL(4, 48, 1), // "s"
QT_MOC_LITERAL(5, 50, 15), // "setCurrentColor"
QT_MOC_LITERAL(6, 66, 18), // "Shape::colorChoice"
QT_MOC_LITERAL(7, 85, 11), // "colorchoice"
QT_MOC_LITERAL(8, 97, 21), // "setCurrentSelectState"
QT_MOC_LITERAL(9, 119, 6), // "Select"
QT_MOC_LITERAL(10, 126, 19), // "setCurrentConvState"
QT_MOC_LITERAL(11, 146, 4), // "Conv"
QT_MOC_LITERAL(12, 151, 1), // "c"
QT_MOC_LITERAL(13, 153, 5), // "clear"
QT_MOC_LITERAL(14, 159, 4) // "save"

    },
    "PaintWidget\0setCurrentShape\0\0"
    "Shape::shapeChoice\0s\0setCurrentColor\0"
    "Shape::colorChoice\0colorchoice\0"
    "setCurrentSelectState\0Select\0"
    "setCurrentConvState\0Conv\0c\0clear\0save"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintWidget[] = {

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
       1,    1,   44,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       8,    1,   50,    2, 0x0a /* Public */,
      10,    1,   53,    2, 0x0a /* Public */,
      13,    0,   56,    2, 0x0a /* Public */,
      14,    0,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,    4,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PaintWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PaintWidget *_t = static_cast<PaintWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCurrentShape((*reinterpret_cast< Shape::shapeChoice(*)>(_a[1]))); break;
        case 1: _t->setCurrentColor((*reinterpret_cast< Shape::colorChoice(*)>(_a[1]))); break;
        case 2: _t->setCurrentSelectState((*reinterpret_cast< Select(*)>(_a[1]))); break;
        case 3: _t->setCurrentConvState((*reinterpret_cast< Conv(*)>(_a[1]))); break;
        case 4: _t->clear(); break;
        case 5: _t->save(); break;
        default: ;
        }
    }
}

const QMetaObject PaintWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_PaintWidget.data,
      qt_meta_data_PaintWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PaintWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PaintWidget.stringdata0))
        return static_cast<void*>(const_cast< PaintWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int PaintWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
