#include "guiinterface.h"


/**** INTERNAL FUNCTIONS *****/
GuiInterface::GuiInterface(QObject *parent): m_isRecording(false),QObject(parent)
{
    QList<QPointF> test;

    test.append(QPointF(0.0,0.0));
    for(int i = 0; i < 6; i++)
    {
        gaugeValueHash.insert(i,0.0);
        chartDataHash.insert(i, test);
    }
}

bool GuiInterface::isRecording() const
{
    return m_isRecording;
}

void GuiInterface::setIsRecording(bool data)
{

        m_isRecording = data;
        emit isRecordingChanged(data);

}


void GuiInterface::in(const QHash<int, QVariant> &data)
{

    switch (data.value(PackageKey).toInt()) {
    case updateGauge:

        gaugeValueHash.insert(FlipperChannelToInt.value(data.value(FlipperChannel).toInt()), data.value(updateGauge).toDouble());

        break;
    case updateChart:
        QList<QPointF> tmpList = chartDataHash.value(FlipperChannelToInt.value(data.value(FlipperChannel).toInt()));

        if(tmpList.count() == 3000)
        {
            tmpList.removeFirst();
        }
        tmpList.append(data.value(updateChart).toPointF());
        chartDataHash.insert(FlipperChannelToInt.value(data.value(FlipperChannel).toInt()), tmpList);

        break;

    }
}

double GuiInterface::getlastgaugeValue(const int &CH) const
{
    return gaugeValueHash.value(CH);
}

void GuiInterface::updateChartData(const int &CH, QAbstractSeries *serie)
{

    if(serie)
    {
        QLineSeries *aSeries = static_cast<QLineSeries*>(serie);
        aSeries->append(chartDataHash.value(CH));

    }
}

void GuiInterface::resetChartDataHashPerCH(const int &CH)
{
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
    QHash<int,QVariant> data;
    data.insert(FlipperKeywords::GUI, FlipperKeywords::updateChart);
    data.insert(FlipperKeywords::FlipperChannel, CH);
    data.insert(FlipperKeywords::NumberOfSample, SampleNumber);
    emit toDatabase(data);
}

void GuiInterface::requestUpdateGauge(const int &CH)
{
    QHash<int,QVariant> data;
    data.insert(FlipperKeywords::GUI, FlipperKeywords::updateGauge);
    data.insert(FlipperKeywords::FlipperChannel, CH);
    emit toDatabase(data);
}

/***** TO FLIPPER INTERFACE FUNCTION *****/


void GuiInterface::setFlipperEnableChannel(const int &channels)
{
    QHash<int, QVariant> package;


    package.insert(PackageKey, GUI);
    package.insert(FlipperEnableChannelsChanged, channels);

    emit toFlipperInterface(package);
}

void GuiInterface::setFLipperTCPAddress(const QString &tcpAddr, const int &port, const int &flipperAddr)
{
    QHash<int, QVariant> package;


    package.insert(PackageKey, GUI);
    package.insert(FlipperTCPAddressChanged, 1);
    package.insert(FlipperTcpAddress, tcpAddr);
    package.insert(FlipperTcpPort, port);
    package.insert(FlipperSVAddress, flipperAddr);

    emit toFlipperInterface(package);
}

void GuiInterface::startRecording()
{
    QHash<int,QVariant> data;
    data.insert(PackageKey, GUI);
    data.insert(FlipperKeywords::startRecording, 1);
    emit toFlipperInterface(data);
}

void GuiInterface::stopRecording()
{
    QHash<int,QVariant> data;
    data.insert(PackageKey, GUI);
    data.insert(FlipperKeywords::stopRecording, 1);
    emit toFlipperInterface(data);
}
