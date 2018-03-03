#include "localdbinterface.h"

QT_CHARTS_USE_NAMESPACE

LocalDBInterface::LocalDBInterface(const QString &dbUsername, const QString &dbPassword, const QString &dbName, QObject *parent): QObject(parent), m_dbUsername(dbUsername), m_dbPassword(dbPassword), m_dbName(dbName)
{

}


void LocalDBInterface::start()
{
    localDb = QSqlDatabase::addDatabase("QMYSQL");
    localDb.setHostName("localhost");
    localDb.setPort(3306);
    localDb.setDatabaseName(m_dbName);
    localDb.setUserName(m_dbUsername);
    localDb.setPassword(m_dbPassword);
    if(localDb.open())
    {

    }
}

QHash<QString, QVariant>  LocalDBInterface::loadFlipperSettingsfromDB()
{
    QSqlQuery tmpQuery(localDb);
    QHash<QString, QVariant> tmpHash;

    if(tmpQuery.exec("SELECT * FROM flippersettings LIMIT BY 1"))
    {
        while(tmpQuery.next())
        {
            tmpHash.insert("id", tmpQuery.value("id").toInt());
            tmpHash.insert("depotName", tmpQuery.value("depotName").toString());
            tmpHash.insert("flipperIP", tmpQuery.value("flipperIP").toString());
            tmpHash.insert("flipperPort", tmpQuery.value("flipperPort").toInt());
            tmpHash.insert("decimalPointCH1", tmpQuery.value("decimalPointCH1").toInt());
            tmpHash.insert("decimalPointCH2", tmpQuery.value("decimalPointCH2").toInt());
            tmpHash.insert("decimalPointCH3", tmpQuery.value("decimalPointCH3").toInt());
            tmpHash.insert("decimalPointCH4", tmpQuery.value("decimalPointCH4").toInt());
            tmpHash.insert("decimalPointCH5", tmpQuery.value("decimalPointCH5").toInt());
            tmpHash.insert("decimalPointCH6", tmpQuery.value("decimalPointCH6").toInt());
            tmpHash.insert("notificationMailaddress", tmpQuery.value("notificationMailaddress").toString());
            tmpHash.insert("notificationPassword", tmpQuery.value("notificationPassword").toString());
            tmpHash.insert("standAloneMode", tmpQuery.value("standAloneMode").toBool());
            tmpHash.insert("sendAlertNotification", tmpQuery.value("sendAlertNotification").toBool());
            tmpHash.insert("sendDailyNotification", tmpQuery.value("sendDailyNotification").toBool());
            tmpHash.insert("channelEnable", tmpQuery.value("channelEnable").toInt());
            tmpHash.insert("serverMode", tmpQuery.value("serverMode").toBool());

        }
    }
    return tmpHash;
}

void LocalDBInterface::updateflipperSettingsToDB(const QHash<QString, QVariant> &tmpHash)
{
    QSqlQuery tmpQuery(localDb);

    tmpQuery.prepare("UPDATE flippersettings SET depotName = ?, flipperIP = ?, flipperPort = ?, decimalPointCH1 = ?,decimalPointCH2 = ?, decimalPointCH3 = ?, decimalPointCH4 =?, decimalPointCH5 = ?, decimalPointCH6 =?, notificationMailaddress = ?, notificationPassword =?,  standAloneMode =?, sendAlertNotification=?, sendDailyNotification = ?, channelEnable =?, serverMode = ? WHERE id = ? ");

    tmpQuery.addBindValue(tmpHash.value("depotName").toString());
    tmpQuery.addBindValue(tmpHash.value("flipperIP").toString());
    tmpQuery.addBindValue(tmpHash.value("flipperPort").toInt());
    tmpQuery.addBindValue(tmpHash.value("decimalPointCH1").toInt());
    tmpQuery.addBindValue(tmpHash.value("decimalPointCH2").toInt());
    tmpQuery.addBindValue(tmpHash.value("decimalPointCH3").toInt());
    tmpQuery.addBindValue(tmpHash.value("decimalPointCH4").toInt());
    tmpQuery.addBindValue(tmpHash.value("decimalPointCH4").toInt());
    tmpQuery.addBindValue(tmpHash.value("decimalPointCH5").toInt());
    tmpQuery.addBindValue(tmpHash.value("decimalPointCH6").toInt());
    tmpQuery.addBindValue(tmpHash.value("notificationMailaddress").toString());
    tmpQuery.addBindValue(tmpHash.value("notificationPassword").toString());
    tmpQuery.addBindValue(tmpHash.value("standAloneMode").toBool());
    tmpQuery.addBindValue(tmpHash.value("sendAlertNotification").toBool());
    tmpQuery.addBindValue(tmpHash.value("sendDailyNotification").toBool());
    tmpQuery.addBindValue(tmpHash.value("channelEnable").toBool());
    tmpQuery.addBindValue(tmpHash.value("serverMode").toBool());
    tmpQuery.addBindValue(tmpHash.value("id").toInt());

    tmpQuery.exec();

}
