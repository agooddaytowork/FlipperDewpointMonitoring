#ifndef FLIPPERNOTIFICATION_H
#define FLIPPERNOTIFICATION_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkReply>
#include <QVariant>
#include <QTimer>
#include "globalconf.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "QSettings"
class FlipperNotification: public QObject
{

    Q_OBJECT

    QString m_serverPath;
    bool m_isServerOnline;
    bool m_isLeftOverDataAvailable;
    int m_ChannelNotSynced;
    quint64 m_lastTimePointToSyncWithServer;
    QString m_flipperSettingPath;
    int m_SVWatchDOGTimerInterval;

    QTimer *svWatchDogTimer;
    QNetworkAccessManager *aNetworkManager;

public:

    explicit FlipperNotification(QString const &svPath, const QString &settingPath, QObject *parent = nullptr);


    void notifyServerNewDewPointAvailable(const int &CH, const double &dewPoint, const quint64 &timePoint);
    void syncData(QJsonObject data);
    void setSVWatchDogTimerInterVal(int interval);
public slots:
    void startServerWatchDog();
    void checkServerOnline();
    void serverReplyHandler(QNetworkReply* reply);
    void in(const QHash<int,QVariant> &data);



signals:
    void serverIsOnline();
    void toDatabase(QHash<int,QVariant>);
    void toGuiInterface(QHash<int,QVariant>);

};

#endif // FLIPPERNOTIFICATION_H
