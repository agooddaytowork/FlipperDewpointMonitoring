#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include "globalconf.h"
#include "QtCharts/QAbstractSeries"
#include "QtCharts/QLineSeries"
#include <QtCharts/QDateTimeAxis>
#include <QDateTime>
#include <QMap>

QT_CHARTS_USE_NAMESPACE

class GuiInterface: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isRecording READ isRecording WRITE setIsRecording NOTIFY isRecordingChanged)
    QHash<int, double> gaugeValueHash;
    QHash<int, QList<QPointF>> chartDataHash;
    bool m_isRecording;
public:
    explicit GuiInterface( QObject * parent = nullptr);

    /*** TO DATABASE FUNCTION ****/
    Q_INVOKABLE void requestUpdateGauge( int const &CH);
    Q_INVOKABLE void requestUpdateChart( int  const&CH, const int &SampleNumber);


    /*** TO FLIPPER INTERFACE FUNCTION ****/
    Q_INVOKABLE void startRecording();
    Q_INVOKABLE void stopRecording();
    Q_INVOKABLE void setFlipperEnableChannel(int const &channels);
    Q_INVOKABLE void setFLipperTCPAddress(const QString &tcpAddr, const int &port, const int &flipperAddr);


    /**** INTERNAL FUNCTIONS *****/
    Q_INVOKABLE double getlastgaugeValue( int const &CH) const;
    Q_INVOKABLE void updateChartData(int const &CH, QAbstractSeries *serie, QAbstractAxis *axis);
    Q_INVOKABLE void resetChartDataHashPerCH(int const &CH);
    Q_INVOKABLE void resetChartDataHash();

    bool isRecording() const;
    void setIsRecording(bool data);

public slots:

    /*** PUBLIC SLOT THAT HANDLES DATA FROM OTHER MODULES ****/
    void in(const QHash<int,QVariant> &data);


signals:
    void toDatabase(const QHash<int,QVariant> &package);
    void toFlipperInterface(const QHash<int,QVariant> &package);
    void isRecordingChanged(bool);
};

#endif // GUIINTERFACE_H
