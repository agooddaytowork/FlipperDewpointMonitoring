#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include "globalconf.h"

class GuiInterface: public QObject
{
    Q_OBJECT


    QHash<int, double> gaugeValueHash;

public:
    explicit GuiInterface( QObject * parent = nullptr);

    Q_INVOKABLE void requestUpdateGauge( int const &CH);
    Q_INVOKABLE void requestUpdateChart( int  const&CH, const int &SampleNumber);
    Q_INVOKABLE void startRecording();
    Q_INVOKABLE void stopRecording();
    Q_INVOKABLE double getlastgaugeValue( int const &CH) const;


public slots:
    void in(const QHash<int,QVariant> &data);
signals:
    void toDatabase(const QHash<int,QVariant> &package);
    void toFlipperInterface(const QHash<int,QVariant> &package);
};

#endif // GUIINTERFACE_H
