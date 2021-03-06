#include "flipperinterface.h"
#include <QDebug>



FlipperInterface::~FlipperInterface()
{
    stop();
    modbusDevice->disconnectDevice();
}

FlipperInterface::FlipperInterface(const QString &tcpAddr, const int &port, const int &flipperAddr, QObject *parent): QObject(parent), m_TCPaddress(tcpAddr), m_TCPport(port), m_FlipperAddress(flipperAddr),m_isRunning(false), m_ChannelEnable(0x00)
{

#if FlipperInterfaceDebug
    qDebug() << "Initialize Flipper interface";
#endif
    // set default update data interval

    m_CollectDataInterVal = m_Update_Interval_ms;
    // set default decimal value to all channels

    setDecimalValue(Channel1, 10);
    setDecimalValue(Channel2, 10);
    setDecimalValue(Channel3, 10);
    setDecimalValue(Channel4, 10);
    setDecimalValue(Channel5, 10);
    setDecimalValue(Channel6, 10);

    QObject::connect(this,SIGNAL(FlipperTcpSettingChanged()),this,SLOT(FlipperTcpSettingsChangedHandler()));
}

void FlipperInterface::start()
{

#if FlipperInterfaceDebug
    qDebug() << "Flipper interface started";
#endif
    if(connectToFlipper()){
        m_isRunning = true;
        initCollectDataTimer(m_CollectDataInterVal);
    }

}

void FlipperInterface::stop()
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface stopped";
#endif
    collectDataTimer->stop();
    m_isRunning = false;
}

void FlipperInterface::setDecimalValue(const quint16 &channel, const quint16 &value)
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: setDecimal value of channel" + QString::number(channel) + " to : " + QString::number(value);
#endif
    m_channelsDecimalPointsHash.insert(channel, value);
}

void FlipperInterface::setEnableChannels(const quint8 &value)
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: setEnable channe"  + value;
#endif
    m_ChannelEnable = value;
}

void FlipperInterface::FlipperRespondHandler()
{

#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter Flipper Respond Handler";
#endif
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        double value =0;
        if(unit.valueCount() != 0)
        {
            value = ((double)((qint16)unit.value(0)) / (double) m_channelsDecimalPointsHash.value(relativeCHaddressToChannelEnum.value(unit.startAddress())));
        }
#if FlipperInterfaceDebug
        qDebug() << "start address: " + QString::number(unit.startAddress());
        qDebug() << "value at 0: " + QString::number((qint16) unit.value(0));
        qDebug() << "value to Double: " + QString::number(value);
#endif

        // create package to emit OUT
        QHash<int, QVariant> package;
        package.insert(FlipperKeywords::PackageKey, FlipperKeywords::ModbusInterface);
        package.insert(FlipperKeywords::FlipperChannel, relativeCHaddressToChannelEnum.value(unit.startAddress()));
        package.insert(FlipperKeywords::Dewpoint, value);
        package.insert(FlipperKeywords::SampleTimePoint, (quint64) QDateTime::currentMSecsSinceEpoch());

        emit out(package);

    } else if (reply->error() == QModbusDevice::ProtocolError) {
        qDebug() << reply->errorString();
    } else {
        qDebug() <<reply->errorString();
    }

    reply->deleteLater();
}

void FlipperInterface::emitRequests()
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter emitRequests";
#endif
    if(m_ChannelEnable & Channel1) m_requestList.append(QModbusDataUnit(QModbusDataUnit::InputRegisters,m_CH1MeasureReleativeAddress,m_ReadOutWordNumberMeasureCommand));
    if(m_ChannelEnable & Channel2) m_requestList.append(QModbusDataUnit(QModbusDataUnit::InputRegisters,m_CH2MeasureReleativeAddress,m_ReadOutWordNumberMeasureCommand));
    if(m_ChannelEnable & Channel3) m_requestList.append(QModbusDataUnit(QModbusDataUnit::InputRegisters,m_CH3MeasureReleativeAddress,m_ReadOutWordNumberMeasureCommand));
    if(m_ChannelEnable & Channel4) m_requestList.append(QModbusDataUnit(QModbusDataUnit::InputRegisters,m_CH4MeasureReleativeAddress,m_ReadOutWordNumberMeasureCommand));
    if(m_ChannelEnable & Channel5) m_requestList.append(QModbusDataUnit(QModbusDataUnit::InputRegisters,m_CH5MeasureReleativeAddress,m_ReadOutWordNumberMeasureCommand));
    if(m_ChannelEnable & Channel6) m_requestList.append(QModbusDataUnit(QModbusDataUnit::InputRegisters,m_CH6MeasureReleativeAddress,m_ReadOutWordNumberMeasureCommand));

    emitRequestsHandler();
}

void FlipperInterface::emitRequestsHandler()
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter emitRequestHandler";
    qDebug() << "number of requests : " + m_requestList.count();
#endif
    for (int i = 0; i < m_requestList.count(); i++)
    {
        if(auto *reply = modbusDevice->sendReadRequest(m_requestList.at(i),m_FlipperAddress))
        {
            if (!reply->isFinished())
                QObject::connect(reply, &QModbusReply::finished, this, &FlipperInterface::FlipperRespondHandler);
            else
                delete reply; // broadcast replies return immediately
        }
        else
        {

        }
    }
    m_requestList.clear();
}

bool FlipperInterface::connectToFlipper()
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter connectToFlipper()";
#endif
    modbusDevice = new QModbusTcpClient(this);
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, m_TCPaddress);
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, m_TCPport);
    modbusDevice->setTimeout(1000);
    modbusDevice->setNumberOfRetries(3);
    QObject::connect(modbusDevice, SIGNAL(errorOccurred(QModbusDevice::Error)),this, SLOT(ModbusDeviceErrorHandler(QModbusDevice::Error)));

    if(modbusDevice->connectDevice())
    {
#if FlipperInterfaceDebug
        qDebug() << modbusDevice->state();
#endif
        QObject::connect(modbusDevice, &QModbusTcpClient::stateChanged, this, &FlipperInterface::onStateChanged);
        return true;
    }
    return false;
}


void FlipperInterface::initCollectDataTimer(const int &interval)
{

#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter initCollectDataTimer()";
#endif
    collectDataTimer = new QTimer(this);
    collectDataTimer->setInterval(interval);
    QObject::connect(collectDataTimer, SIGNAL(timeout()), this,SLOT(emitRequests()));

}

void FlipperInterface::setCollectDataInterval(const int &interval)
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter setCollectDataTimer()";
#endif
    m_CollectDataInterVal = interval;
}

void FlipperInterface::ModbusDeviceErrorHandler(QModbusDevice::Error error)
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter ModbusDeviceErrorHandler()";
#endif
    switch (error) {
    case QModbusDevice::ConnectionError:
    case QModbusDevice::TimeoutError:

        if(m_isRunning)
        {
            // reconnect
#if FlipperInterfaceDebug
            qDebug() << "Connection error, reconnect until STOP signal triggered";
#endif
            this->stop();
            this->start();
            break;
        }


    default:

#if FlipperInterfaceDebug
        qDebug() << "QModbus device errors ! skip; only handle Qmodbus:Connection error and Timeout error";
#endif
        modbusDevice->disconnectDevice();

        QHash<int,QVariant> package;

        package.insert(FlipperKeywords::PackageKey, FlipperKeywords::ModbusInterface);
        package.insert(FlipperKeywords::ModbusInterface, FlipperKeywords::flipperIsOffline);

        emit toGuiInterface(package);
        break;
    }

}

void FlipperInterface::onStateChanged(int state)
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter onStateChanged()";
    qDebug() << modbusDevice->state();
#endif

    static int attemptCounter = 0;
    if(state  == QModbusDevice::ConnectedState)
    {
        collectDataTimer->start();
        emitRequests();

        QHash<int,QVariant> package;

        package.insert(FlipperKeywords::PackageKey, FlipperKeywords::ModbusInterface);
        package.insert(FlipperKeywords::ModbusInterface, FlipperKeywords::flipperIsOnline);

        emit toGuiInterface(package);
    }
    else if(state == QModbusDevice::UnconnectedState)
    {

        modbusDevice->connectDevice();
        attemptCounter++;

        if(attemptCounter == m_ConnectToDevice_Attempts_Max)
        {
            attemptCounter = 0;
            // emit FATAL ERROR HERE  and STOP THE WHOLE PROGRAM
        }


    }

}

void FlipperInterface::setFlipperTcpSettings(const QString &tcpAddr, const int &port, const int &flipperAddr)
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter setFlipperTcpSettings()";
#endif


    m_TCPaddress = tcpAddr;
    m_TCPport = port;
    m_FlipperAddress = flipperAddr;
    emit FlipperTcpSettingChanged();
}


void FlipperInterface::FlipperTcpSettingsChangedHandler()
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter FlipperTcpSettingsChangedHandler()";
#endif
    //    if(collectDataTimer->isActive())
    //    {
    //        collectDataTimer->stop();
    //        if(connectToFlipper()) collectDataTimer->start();
    //    }
    //    else
    //    {
    //        connectToFlipper();
    //    }
}

const QHash<quint32,ChannelEnableEnum> FlipperInterface::relativeCHaddressToChannelEnum=QHash<quint32,ChannelEnableEnum>
({
     {m_CH1MeasureReleativeAddress, Channel1},
     {m_CH2MeasureReleativeAddress, Channel2},
     {m_CH3MeasureReleativeAddress, Channel3},
     {m_CH4MeasureReleativeAddress, Channel4},
     {m_CH5MeasureReleativeAddress, Channel5},
     {m_CH6MeasureReleativeAddress, Channel6}
 });

void FlipperInterface::in(const QHash<int, QVariant> &data)
{
#if FlipperInterfaceDebug
    qDebug() << "Flipper interface: enter in()";
#endif

    switch (data.value(PackageKey).toInt()) {
    case FlipperKeywords::startRecording:
#if FlipperInterfaceDebug
        qDebug() << "Start Recording";
#endif
        this->start();
        break;

    case FlipperKeywords::stopRecording:
#if FlipperInterfaceDebug
        qDebug() << "Stop Recording";
#endif
        this->stop();
        break;

    case FlipperEnableChannelsChanged:
#if FlipperInterfaceDebug
        qDebug() << "FlipperEnableChannelsChanged";
#endif
        this->setEnableChannels(data.value(FlipperEnableChannelsChanged).toInt());
        break;

    case FlipperTCPAddressChanged:
#if FlipperInterfaceDebug
        qDebug() << "FlipperTCPAddressChanged";
#endif
        this->setFlipperTcpSettings(data.value(FlipperTcpAddress).toString(), data.value(FlipperTcpPort).toInt(), data.value(FlipperSVAddress).toInt());
        break;

    default:
        break;
    }

}
