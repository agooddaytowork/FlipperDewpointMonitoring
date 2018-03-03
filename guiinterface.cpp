#include "guiinterface.h"

GuiInterface::GuiInterface(QObject *parent): QObject(parent)
{

    gaugeValueHash.insert(0, 0.0);
    gaugeValueHash.insert(1, 0.0);
    gaugeValueHash.insert(2, 0.0);
    gaugeValueHash.insert(3, 0.0);
    gaugeValueHash.insert(4, 0.0);
    gaugeValueHash.insert(5, 0.0);

}

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

void GuiInterface::startRecording()
{
    QHash<int,QVariant> data;
    data.insert(FlipperKeywords::GUI, FlipperKeywords::startRecording);
    emit toDatabase(data);
}

void GuiInterface::stopRecording()
{
    QHash<int,QVariant> data;
    data.insert(FlipperKeywords::GUI, FlipperKeywords::stopRecording);
    emit toDatabase(data);
}

void GuiInterface::in(const QHash<int, QVariant> &data)
{

}

double GuiInterface::getlastgaugeValue(const int &CH) const
{
    return gaugeValueHash.value(CH);
}

