/****************************************************************************
** Meta object code from reading C++ file 'flipperinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "flipperinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flipperinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlipperInterface_t {
    QByteArrayData data[32];
    char stringdata0[438];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlipperInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlipperInterface_t qt_meta_stringdata_FlipperInterface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FlipperInterface"
QT_MOC_LITERAL(1, 17, 23), // "RecordDewPointToLocalDB"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 7), // "channel"
QT_MOC_LITERAL(4, 50, 5), // "value"
QT_MOC_LITERAL(5, 56, 24), // "FlipperTcpSettingChanged"
QT_MOC_LITERAL(6, 81, 12), // "emitRequests"
QT_MOC_LITERAL(7, 94, 19), // "emitRequestsHandler"
QT_MOC_LITERAL(8, 114, 21), // "FlipperRespondHandler"
QT_MOC_LITERAL(9, 136, 14), // "onStateChanged"
QT_MOC_LITERAL(10, 151, 5), // "state"
QT_MOC_LITERAL(11, 157, 5), // "start"
QT_MOC_LITERAL(12, 163, 21), // "setFlipperTcpSettings"
QT_MOC_LITERAL(13, 185, 7), // "tcpAddr"
QT_MOC_LITERAL(14, 193, 4), // "port"
QT_MOC_LITERAL(15, 198, 11), // "flipperAddr"
QT_MOC_LITERAL(16, 210, 4), // "stop"
QT_MOC_LITERAL(17, 215, 15), // "setDecimalValue"
QT_MOC_LITERAL(18, 231, 17), // "setEnableChannels"
QT_MOC_LITERAL(19, 249, 22), // "setCollectDataInterval"
QT_MOC_LITERAL(20, 272, 8), // "interval"
QT_MOC_LITERAL(21, 281, 24), // "ModbusDeviceErrorHandler"
QT_MOC_LITERAL(22, 306, 20), // "QModbusDevice::Error"
QT_MOC_LITERAL(23, 327, 5), // "error"
QT_MOC_LITERAL(24, 333, 32), // "FlipperTcpSettingsChangedHandler"
QT_MOC_LITERAL(25, 366, 17), // "ChannelEnableEnum"
QT_MOC_LITERAL(26, 384, 8), // "Channel1"
QT_MOC_LITERAL(27, 393, 8), // "Channel2"
QT_MOC_LITERAL(28, 402, 8), // "Channel3"
QT_MOC_LITERAL(29, 411, 8), // "Channel4"
QT_MOC_LITERAL(30, 420, 8), // "Channel5"
QT_MOC_LITERAL(31, 429, 8) // "Channel6"

    },
    "FlipperInterface\0RecordDewPointToLocalDB\0"
    "\0channel\0value\0FlipperTcpSettingChanged\0"
    "emitRequests\0emitRequestsHandler\0"
    "FlipperRespondHandler\0onStateChanged\0"
    "state\0start\0setFlipperTcpSettings\0"
    "tcpAddr\0port\0flipperAddr\0stop\0"
    "setDecimalValue\0setEnableChannels\0"
    "setCollectDataInterval\0interval\0"
    "ModbusDeviceErrorHandler\0QModbusDevice::Error\0"
    "error\0FlipperTcpSettingsChangedHandler\0"
    "ChannelEnableEnum\0Channel1\0Channel2\0"
    "Channel3\0Channel4\0Channel5\0Channel6"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlipperInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       1,  120, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,
       5,    0,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   90,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    1,   93,    2, 0x0a /* Public */,
      11,    0,   96,    2, 0x0a /* Public */,
      12,    3,   97,    2, 0x0a /* Public */,
      16,    0,  104,    2, 0x0a /* Public */,
      17,    2,  105,    2, 0x0a /* Public */,
      18,    1,  110,    2, 0x0a /* Public */,
      19,    1,  113,    2, 0x0a /* Public */,
      21,    1,  116,    2, 0x08 /* Private */,
      24,    0,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Double,    3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort,    3,    4,
    QMetaType::Void, QMetaType::UChar,    4,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,

 // enums: name, flags, count, data
      25, 0x0,    6,  124,

 // enum data: key, value
      26, uint(FlipperInterface::Channel1),
      27, uint(FlipperInterface::Channel2),
      28, uint(FlipperInterface::Channel3),
      29, uint(FlipperInterface::Channel4),
      30, uint(FlipperInterface::Channel5),
      31, uint(FlipperInterface::Channel6),

       0        // eod
};

void FlipperInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlipperInterface *_t = static_cast<FlipperInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->RecordDewPointToLocalDB((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const double(*)>(_a[2]))); break;
        case 1: _t->FlipperTcpSettingChanged(); break;
        case 2: _t->emitRequests(); break;
        case 3: _t->emitRequestsHandler(); break;
        case 4: _t->FlipperRespondHandler(); break;
        case 5: _t->onStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->start(); break;
        case 7: _t->setFlipperTcpSettings((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 8: _t->stop(); break;
        case 9: _t->setDecimalValue((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< const quint16(*)>(_a[2]))); break;
        case 10: _t->setEnableChannels((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 11: _t->setCollectDataInterval((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 12: _t->ModbusDeviceErrorHandler((*reinterpret_cast< QModbusDevice::Error(*)>(_a[1]))); break;
        case 13: _t->FlipperTcpSettingsChangedHandler(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FlipperInterface::*_t)(const int & , const double & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlipperInterface::RecordDewPointToLocalDB)) {
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
      qt_meta_data_FlipperInterface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FlipperInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlipperInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void FlipperInterface::RecordDewPointToLocalDB(const int & _t1, const double & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlipperInterface::FlipperTcpSettingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
