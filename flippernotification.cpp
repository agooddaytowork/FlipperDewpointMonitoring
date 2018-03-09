#include "flippernotification.h"

#define UPDATE_DATA_SV_PATH "/KTproj/flipperdataupdatev2.php"

FlipperNotification::FlipperNotification(const QString &svPath, const QString &settingPath, QObject *parent):
    QObject(parent), m_serverPath(svPath), m_isServerOnline(false), m_flipperSettingPath(settingPath), m_isLeftOverDataAvailable(false), m_lastTimePointToSyncWithServer(0),m_ChannelNotSynced(0)
{

#if FlipperNotificationDebug
    qDebug() << "FlipperNotification::FlipperNotification()";
#endif

}


void FlipperNotification::startServerWatchDog()
{

#if FlipperNotificationDebug
    qDebug() << "FlipperNotification::startServerWatchDog()";
#endif
    checkServerOnline();
    QTimer *aTimer = new QTimer(this);

    QObject::connect(aTimer,SIGNAL(timeout()), this, SLOT(checkServerOnline()));
    aTimer->start(300000); // check every 5 minutes
}

void FlipperNotification::checkServerOnline()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(serverReplyHandler(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl(m_serverPath)));

}


void FlipperNotification::serverReplyHandler(QNetworkReply *reply)
{

#if FlipperNotificationDebug
    qDebug() << "FlipperNotification: serverReplyHandler() ";
#endif
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if(status_code.isValid())
    {
#if FlipperNotificationDebug
        qDebug() << "status code: " + status_code.toString();
        qDebug() << "reply: " + reply->readAll();
#endif
        switch (status_code.toInt()) {
        case 200:

#if FlipperNotificationDebug
            qDebug() << "status: 200 - OK ";
#endif
            m_isServerOnline = true;

            if(m_isLeftOverDataAvailable)
            {
                // emit request to database for leftOverData
                QHash<int,QVariant> package;
                package.insert(FlipperKeywords::PackageKey, FlipperKeywords::Notification);
                package.insert(FlipperKeywords::Notification, FlipperKeywords::getNotSyncedData);
                package.insert(FlipperKeywords::LastSampleTimePoint, m_lastTimePointToSyncWithServer);
                package.insert(FlipperKeywords::FlipperChannel, m_ChannelNotSynced);

                emit toDatabase(package);
            }

            emit serverIsOnline();
            break;

        case 500:
        case 501:
        case 502:
        case 503:
        case 504:
        case 505:
        case 506:
        case 507:
        case 508:
        case 509:
        case 510:
        case 511:
        case 598:
        case 599:
#if FlipperNotificationDebug
            qDebug() << "status: 500 -> 511, 598, 599 - Server error";
            qDebug() << "status code: " +status_code.toString();

#endif
            m_isServerOnline = false;
            break;

            break;
        default:
            m_isServerOnline = false;
            break;
        }
    }
    else
    {
#if FlipperNotificationDebug
        qDebug() << "FlipperNotification: SV path is not Valid, no returned valid HTTP status code ";
#endif
        m_isServerOnline = false;
    }
}


void FlipperNotification::in(const QHash<int, QVariant> &data)
{
#if FlipperNotificationDebug
    qDebug() << "FlipperNotification::in()";
#endif

    switch (data.value(FlipperKeywords::PackageKey).toInt()) {
    case FlipperKeywords::ModbusInterface:
#if FlipperDatabaseDebug
        qDebug() << "FlipperNotification: Channel: " + QString::number(data.value(FlipperKeywords::FlipperChannel).toInt()) ;
#endif

        notifyServerNewDewPointAvailable(data.value(FlipperKeywords::FlipperChannel).toInt(), data.value(FlipperKeywords::Dewpoint).toDouble(), data.value(FlipperKeywords::SampleTimePoint).toULongLong());
        break;

    case FlipperKeywords::Notification:
        if(data.value(FlipperKeywords::Notification).toInt() == FlipperKeywords::getNotSyncedData)
        {
            //  get a big QJsonObject here for conveninent :D
            syncData(data.value(FlipperKeywords::getNotSyncedData).toJsonObject());
        }
    default:
        break;
    }

}

void FlipperNotification::notifyServerNewDewPointAvailable(const int &CH, const double &dewPoint, const quint64 &timePoint)
{
#if FlipperNotificationDebug
    qDebug() << "FlipperNotification::notifyServerNewDewPointAvailable()";
#endif


    QSettings m_setting(m_flipperSettingPath, QSettings::IniFormat);
    QJsonObject SendData ;
    SendData.insert("MAC", m_setting.value("eth0MacAddress").toString().remove(QRegExp("[\\:]")));
    SendData.insert("Channel", CH);
    QJsonArray DewpointData;
    DewpointData << QJsonObject{{QString::number(timePoint), dewPoint}};
    SendData.insert("Data", DewpointData);


    QByteArray data = QJsonDocument(SendData).toJson();

    if(m_isServerOnline)
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(serverReplyHandler(QNetworkReply*)));
#if FlipperNotificationDebug
    qDebug() << "SV path: " + m_serverPath+UPDATE_DATA_SV_PATH;
#endif

        QUrl url(m_serverPath + UPDATE_DATA_SV_PATH);
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        manager->post(request, data);
    }
    else
    {
        if(!m_isLeftOverDataAvailable)
        {
            m_isLeftOverDataAvailable = true;
            m_lastTimePointToSyncWithServer = timePoint;
            m_ChannelNotSynced |= CH;
        }
    }

}


void FlipperNotification::syncData( QJsonObject SendData)
{
#if FlipperNotificationDebug
    qDebug() << "syncData::notifyServerNewDewPointAvailable()";
#endif

    if(m_isServerOnline)
    {

        QSettings m_setting(m_flipperSettingPath, QSettings::IniFormat);

       SendData.insert("MAC", m_setting.value("eth0MacAddress").toString().remove(QRegExp("[\\:]")));

         QByteArray data = QJsonDocument(SendData).toJson();

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(serverReplyHandler(QNetworkReply*)));

        QUrl url(m_serverPath + UPDATE_DATA_SV_PATH);
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        manager->post(request, data);

        // reset the flag

        m_ChannelNotSynced = 0;
        m_isLeftOverDataAvailable = false;
    }
}


