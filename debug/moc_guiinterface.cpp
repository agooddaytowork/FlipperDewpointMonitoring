/****************************************************************************
** Meta object code from reading C++ file 'guiinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../guiinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guiinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GuiInterface_t {
    QByteArrayData data[15];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiInterface_t qt_meta_stringdata_GuiInterface = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GuiInterface"
QT_MOC_LITERAL(1, 13, 10), // "toDatabase"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 19), // "QHash<int,QVariant>"
QT_MOC_LITERAL(4, 45, 7), // "package"
QT_MOC_LITERAL(5, 53, 18), // "toFlipperInterface"
QT_MOC_LITERAL(6, 72, 2), // "in"
QT_MOC_LITERAL(7, 75, 4), // "data"
QT_MOC_LITERAL(8, 80, 18), // "requestUpdateGauge"
QT_MOC_LITERAL(9, 99, 2), // "CH"
QT_MOC_LITERAL(10, 102, 18), // "requestUpdateChart"
QT_MOC_LITERAL(11, 121, 12), // "SampleNumber"
QT_MOC_LITERAL(12, 134, 14), // "startRecording"
QT_MOC_LITERAL(13, 149, 13), // "stopRecording"
QT_MOC_LITERAL(14, 163, 17) // "getlastgaugeValue"

    },
    "GuiInterface\0toDatabase\0\0QHash<int,QVariant>\0"
    "package\0toFlipperInterface\0in\0data\0"
    "requestUpdateGauge\0CH\0requestUpdateChart\0"
    "SampleNumber\0startRecording\0stopRecording\0"
    "getlastgaugeValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   60,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    1,   63,    2, 0x02 /* Public */,
      10,    2,   66,    2, 0x02 /* Public */,
      12,    0,   71,    2, 0x02 /* Public */,
      13,    0,   72,    2, 0x02 /* Public */,
      14,    1,   73,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    7,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Double, QMetaType::Int,    9,

       0        // eod
};

void GuiInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GuiInterface *_t = static_cast<GuiInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toDatabase((*reinterpret_cast< const QHash<int,QVariant>(*)>(_a[1]))); break;
        case 1: _t->toFlipperInterface((*reinterpret_cast< const QHash<int,QVariant>(*)>(_a[1]))); break;
        case 2: _t->in((*reinterpret_cast< const QHash<int,QVariant>(*)>(_a[1]))); break;
        case 3: _t->requestUpdateGauge((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->requestUpdateChart((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 5: _t->startRecording(); break;
        case 6: _t->stopRecording(); break;
        case 7: { double _r = _t->getlastgaugeValue((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GuiInterface::*_t)(const QHash<int,QVariant> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GuiInterface::toDatabase)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GuiInterface::*_t)(const QHash<int,QVariant> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GuiInterface::toFlipperInterface)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GuiInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GuiInterface.data,
      qt_meta_data_GuiInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GuiInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GuiInterface.stringdata0))
        return static_cast<void*>(const_cast< GuiInterface*>(this));
    return QObject::qt_metacast(_clname);
}

int GuiInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GuiInterface::toDatabase(const QHash<int,QVariant> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GuiInterface::toFlipperInterface(const QHash<int,QVariant> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
