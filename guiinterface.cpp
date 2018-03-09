#include "guiinterface.h"

#define GuiInterfaceDebug (0)
/**** INTERNAL FUNCTIONS *****/
GuiInterface::GuiInterface(QObject *parent): QObject(parent),m_isRecording(false),m_isServerOnline(false),m_isFlipperOnline(false)
{

#if GuiInterfaceDebug
    qDebug() << "GuiInterface -> GuiInterface()";
#endif
    for(int i = 0; i < 6; i++)
    {
        gaugeValueHash.insert(i,0.0);
    }
}

bool GuiInterface::isRecording() const
{
#if GuiInterfaceDebug
    qDebug() << "GuiInterface -> isRecording()";
#endif
    return m_isRecording;
}

void GuiInterface::setIsRecording(bool data)
{
#if GuiInterfaceDebug
    qDebug() << "GuiInterface -> setIsRecording()";
#endif
    m_isRecording = data;
    emit isRecordingChanged(data);

}


void GuiInterface::in(const QHash<int, QVariant> &data)
{
#if GuiInterfaceDebug
    qDebug() << "GuiInterface -> in()";
#endif


    switch (data.value(FlipperKeywords::PackageKey).toInt()) {

    case FlipperKeywords::updateGauge:

        gaugeValueHash.insert(data.value(FlipperKeywords::FlipperChannel).toInt(), data.value(FlipperKeywords::updateGauge).toDouble());

        break;

    case FlipperKeywords::ModbusInterface:

        if(data.value(FlipperKeywords::ModbusInterface).toInt() == FlipperKeywords::flipperIsOffline)
        {
            setIsFlipperOnline(false);
        }
        else if (data.value(FlipperKeywords::ModbusInterface).toInt() == FlipperKeywords::flipperIsOnline)
        {
            setIsFlipperOnline(true);
        }
        break;

    case FlipperKeywords::Notification:

        if(data.value(FlipperKeywords::Notification).toInt() == FlipperKeywords::serverIsOffline)
        {
            setIsServerOnline(false);
        }
        else if(data.value(FlipperKeywords::Notification).toInt() == FlipperKeywords::serverIsOnline)
        {
            setIsServerOnline(true);
        }
        break;


    case FlipperKeywords::updateChart:
#if GuiInterfaceDebug
        qDebug() << "GUi Interface: update Chart data request - CH: " + QString::number(data.value(FlipperKeywords::FlipperChannel).toInt());
#endif

        QList<QPointF> tmpList = chartDataHash.value(data.value(FlipperKeywords::FlipperChannel).toInt());

        if(tmpList.count() == 3000)
        {
            tmpList.removeFirst();
        }
        tmpList.append(data.value(updateChart).toPointF());
#if GuiInterfaceDebug
        qDebug() <<  data.value(FlipperKeywords::FlipperChannel).toInt();
#endif
        chartDataHash.insert(data.value(FlipperKeywords::FlipperChannel).toInt(), tmpList);

        break;


    }
}

double GuiInterface::getlastgaugeValue(const int &CH) const
{
#if GuiInterfaceDebug
    qDebug() <<  "GuiInterface::getlastgaugeValue()";
#endif
    return gaugeValueHash.value(CH);
}

void GuiInterface::updateChartData(const int &CH, QAbstractSeries *serie, QAbstractAxis *axis)
{
#if GuiInterfaceDebug
    qDebug() <<  "GuiInterface::updateChartData()";
#endif
    if(serie)
    {
        QList<QPointF> aList = chartDataHash.value(CH);
        QLineSeries *aSeries = static_cast<QLineSeries*>(serie);
        aSeries->clear();
        aSeries->append(aList);

        if(axis)
        {
#if GuiInterfaceDebug
            qDebug() << QString::number((qint64) aList.at(0).x());
#endif
            if(aSeries->count()>2)
            {

                QDateTimeAxis *xAxis = static_cast<QDateTimeAxis *>(axis);

                xAxis->setMin(QDateTime::fromMSecsSinceEpoch((quint64) aSeries->at(0).x()));
                xAxis->setMax(QDateTime::fromMSecsSinceEpoch((quint64) aSeries->at(aSeries->count()-1).x()));
            }



        }

    }
}

void GuiInterface::resetChartDataHashPerCH(const int &CH)
{

#if GuiInterfaceDebug
    qDebug() <<  "GuiInterface::resetChartDataHashPerCH()";
#endif
    chartDataHash.remove(CH);
    QList<QPointF> test;
    test.append(QPointF(0.0,0.0));
    chartDataHash.insert(CH, test);
}

void GuiInterface::resetChartDataHash()
{
    for( int i =0; i < 6; i++)
    {
        resetChartDataHashPerCH(i);
    }
}
/***** TO DATABASE FUNCTION *****/

void GuiInterface::requestUpdateChart(const int &CH, const int &SampleNumber)
{
#if GuiInterfaceDebug
    qDebug()<< "GuiInterface:: requestUpdateChart() - CH = " + QString::number(CH);
#endif

    QHash<int,QVariant> data;
    data.insert(FlipperKeywords::PackageKey, FlipperKeywords::GUI);
    data.insert(FlipperKeywords::GUI, FlipperKeywords::updateChart);
    data.insert(FlipperKeywords::FlipperChannel, CH);
    data.insert(FlipperKeywords::NumberOfSample, SampleNumber);
    emit toDatabase(data);
}

void GuiInterface::requestUpdateGauge(const int &CH)
{

#if GuiInterfaceDebug
    qDebug()<< "GuiInterface:: requestUpdateGauge()";
#endif
    QHash<int,QVariant> data;
    data.insert(FlipperKeywords::PackageKey, FlipperKeywords::GUI);
    data.insert(FlipperKeywords::GUI, FlipperKeywords::updateGauge);
    data.insert(FlipperKeywords::FlipperChannel, CH);
    emit toDatabase(data);
}

/***** TO FLIPPER INTERFACE FUNCTION *****/


void GuiInterface::setFlipperEnableChannel(const int &channels)
{

#if GuiInterfaceDebug
    qDebug()<< "GuiInterface:: setFlipperEnableChannel()";
#endif
    QHash<int, QVariant> package;


    package.insert(PackageKey, FlipperEnableChannelsChanged);
    package.insert(FlipperEnableChannelsChanged, channels);

    emit toFlipperInterface(package);
}

void GuiInterface::setFLipperTCPAddress(const QString &tcpAddr, const int &port, const int &flipperAddr)
{


#if GuiInterfaceDebug
    qDebug()<< "GuiInterface:: setFLipperTCPAddress()";
#endif
    QHash<int, QVariant> package;


    package.insert(PackageKey, FlipperTCPAddressChanged);
    package.insert(FlipperTCPAddressChanged, 1);
    package.insert(FlipperTcpAddress, tcpAddr);
    package.insert(FlipperTcpPort, port);
    package.insert(FlipperSVAddress, flipperAddr);

    emit toFlipperInterface(package);
}

void GuiInterface::startRecording()
{


#if GuiInterfaceDebug
    qDebug()<< "GuiInterface:: startRecording()";
#endif
    QHash<int,QVariant> data;
    data.insert(PackageKey, FlipperKeywords::startRecording);
    emit toFlipperInterface(data);
}

void GuiInterface::stopRecording()
{

#if GuiInterfaceDebug
    qDebug()<< "GuiInterface:: stopRecording()";
#endif
    QHash<int,QVariant> data;
    data.insert(PackageKey, FlipperKeywords::stopRecording);
    emit toFlipperInterface(data);
}

bool GuiInterface::isServerOnline() const
{
    return m_isServerOnline;
}

void GuiInterface::setIsServerOnline(bool data)
{
    m_isServerOnline = data;
    emit isServerOnlineChanged(data);
}

void GuiInterface::setIsFlipperOnline(bool data)
{
    m_isFlipperOnline = data;
    emit isFlipperOnlineChanged(data);
}

bool GuiInterface::isFlipperOnline() const
{
    return m_isFlipperOnline;
}
