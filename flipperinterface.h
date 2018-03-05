#ifndef FLIPPERINTERFACE_H
#define FLIPPERINTERFACE_H

#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QObject>
#include <QTimer>
#include <QHash>
#include <QVariant>
#include "globalconf.h"

class FlipperInterface: public QObject
{
    Q_OBJECT

public:
    FlipperInterface(const QString &tcpAddr, const int &port, const int &flipperAddr, QObject * parent = 0);
    ~FlipperInterface();
    void setFlipperTcpSettings(const QString &tcpAddr, const int &port, const int &flipperAddr);

    void setDecimalValue(const quint16 &channel, const quint16 &value);
    void setEnableChannels(const quint8 &value);
    void setCollectDataInterval(const int &interval);



public slots:
    void emitRequests();
    void emitRequestsHandler();
    void FlipperRespondHandler();
    void onStateChanged(int state);
    void start();
    void stop();


    void in(QHash<int,QVariant> const &data); //Handle request from other modules

private slots:
    void ModbusDeviceErrorHandler(QModbusDevice::Error error);
    void FlipperTcpSettingsChangedHandler();

signals:

    void out(QHash<int,QVariant>);
    void FlipperTcpSettingChanged();
private:

    static constexpr const quint32 m_CH1MeasureReleativeAddress = 0x0064;
    static constexpr const quint32 m_CH2MeasureReleativeAddress = 0x0065;
    static constexpr const quint32 m_CH3MeasureReleativeAddress = 0x0066;
    static constexpr const quint32 m_CH4MeasureReleativeAddress = 0x0068;
    static constexpr const quint32 m_CH5MeasureReleativeAddress = 0x0069;
    static constexpr const quint32 m_CH6MeasureReleativeAddress = 0x006A;
    static constexpr const quint32 m_ReadOutWordNumberMeasureCommand = 0x0001;
    static constexpr const quint8 m_ReadOutHoldingRegisterCode = 0x03;
    static constexpr const quint8 m_ReadOutInputRegisterCode = 0x04;
    static constexpr const quint8 m_WriteInHoldingRegisterCode = 0x10;
    static constexpr const int m_ConnectToDevice_Attempts_Max = 30;
    static constexpr const int m_Update_Interval_ms = 60000;
    static const QHash<quint32,ChannelEnableEnum> relativeCHaddressToChannelEnum;
    bool connectToFlipper();
    void initCollectDataTimer(const int &interval);

    QString m_TCPaddress;
    int m_TCPport;
    int m_FlipperAddress;
    int m_CollectDataInterVal;
    bool m_isRunning;
    QModbusTcpClient *modbusDevice;
    QTimer *collectDataTimer;
    QList<QModbusDataUnit> m_requestList;
    QHash<int, int> m_channelsDecimalPointsHash;
    quint8 m_ChannelEnable;
};

#endif // FLIPPERINTERFACE_H
