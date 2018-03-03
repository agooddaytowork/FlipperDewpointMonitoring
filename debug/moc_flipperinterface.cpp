/****************************************************************************
** Meta object code from reading C++ file 'flipperinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../flipperinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flipperinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlipperInterface_t {
    QByteArrayData data[16];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlipperInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlipperInterface_t qt_meta_stringdata_FlipperInterface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FlipperInterface"
QT_MOC_LITERAL(1, 17, 3), // "out"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 19), // "QHash<int,QVariant>"
QT_MOC_LITERAL(4, 42, 24), // "FlipperTcpSettingChanged"
QT_MOC_LITERAL(5, 67, 12), // "emitRequests"
QT_MOC_LITERAL(6, 80, 19), // "emitRequestsHandler"
QT_MOC_LITERAL(7, 100, 21), // "FlipperRespondHandler"
QT_MOC_LITERAL(8, 122, 14), // "onStateChanged"
QT_MOC_LITERAL(9, 137, 5), // "state"
QT_MOC_LITERAL(10, 143, 5), // "start"
QT_MOC_LITERAL(11, 149, 2), // "in"
QT_MOC_LITERAL(12, 152, 24), // "ModbusDeviceErrorHandler"
QT_MOC_LITERAL(13, 177, 20), // "QModbusDevice::Error"
QT_MOC_LITERAL(14, 198, 5), // "error"
QT_MOC_LITERAL(15, 204, 32) // "FlipperTcpSettingsChangedHandler"

    },
    "FlipperInterface\0out\0\0QHash<int,QVariant>\0"
    "FlipperTcpSettingChanged\0emitRequests\0"
    "emitRequestsHandler\0FlipperRespondHandler\0"
    "onStateChanged\0state\0start\0in\0"
    "ModbusDeviceErrorHandler\0QModbusDevice::Error\0"
    "error\0FlipperTcpSettingsChangedHandler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlipperInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   68,    2, 0x0a /* Public */,
       6,    0,   69,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    1,   71,    2, 0x0a /* Public */,
      10,    0,   74,    2, 0x0a /* Public */,
      11,    1,   75,    2, 0x0a /* Public */,
      12,    1,   78,    2, 0x08 /* Private */,
      15,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void FlipperInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlipperInterface *_t = static_cast<FlipperInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->out((*reinterpret_cast< QHash<int,QVariant>(*)>(_a[1]))); break;
        case 1: _t->FlipperTcpSettingChanged(); break;
        case 2: _t->emitRequests(); break;
        case 3: _t->emitRequestsHandler(); break;
        case 4: _t->FlipperRespondHandler(); break;
        case 5: _t->onStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->start(); break;
        case 7: _t->in((*reinterpret_cast< QHash<int,QVariant>(*)>(_a[1]))); break;
        case 8: _t->ModbusDeviceErrorHandler((*reinterpret_cast< QModbusDevice::Error(*)>(_a[1]))); break;
        case 9: _t->FlipperTcpSettingsChangedHandler(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FlipperInterface::*_t)(QHash<int,QVariant> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlipperInterface::out)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FlipperInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlipperInterface::FlipperTcpSettingChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject FlipperInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FlipperInterface.data,
      qt_meta_data_FlipperInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlipperInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlipperInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlipperInterface.stringdata0))
        return static_cast<void*>(const_cast< FlipperInterface*>(this));
    return QObject::qt_metacast(_clname);
}

int FlipperInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void FlipperInterface::out(QHash<int,QVariant> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlipperInterface::FlipperTcpSettingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
