#include "flipperdatabase.h"
#include <QDateTime>



FlipperDatabase::~FlipperDatabase()
{

}

FlipperDatabase::FlipperDatabase(const QString &databasePath, QObject *parent): QObject(parent), m_databasePath(databasePath)
{

#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: FlipperDatabase()";
#endif


}

void FlipperDatabase::openDatabase()
{
#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: openDatabase()";
#endif
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(m_databasePath);

    if(!m_database.open())
    {
#if FlipperDatabaseDebug
        qDebug() << "Error, connection with database failed! ";
#endif
    }
    else
    {
#if FlipperDatabaseDebug
        qDebug() << "Database Connection OK! ";
#endif
        createTablesIfNotExists();
        doWork();
    }
}


void FlipperDatabase::createTablesIfNotExists()
{
#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: createTablesIfNotExists()";
#endif
    QSqlQuery aQuery;

    aQuery.exec("CREATE TABLE IF NOT EXISTS CH1(timeStamp interger primary key, data) ");
    aQuery.exec("CREATE TABLE IF NOT EXISTS CH2(timeStamp interger primary key, data) ");
    aQuery.exec("CREATE TABLE IF NOT EXISTS CH3(timeStamp interger primary key, data) ");
    aQuery.exec("CREATE TABLE IF NOT EXISTS CH4(timeStamp interger primary key, data) ");
    aQuery.exec("CREATE TABLE IF NOT EXISTS CH5(timeStamp interger primary key, data) ");
    aQuery.exec("CREATE TABLE IF NOT EXISTS CH6(timeStamp interger primary key, data) ");
}

void FlipperDatabase::in(const QHash<int, QVariant> &input)
{
#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: in()";
#endif
    if(!isFirstBufferBusy)
    {
#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: first buffer";
#endif
        m_RequestsBuffer_1.append(input);
        doWork();
    }
    else
    {
#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: second buffer";
#endif
        m_RequestsBuffer_2.append(input);
    }
}

void FlipperDatabase::doWork()
{
#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: doWork()";
#endif
    isFirstBufferBusy = true;
    while(!m_RequestsBuffer_1.isEmpty())
    {

#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: first buffer";
#endif
        processPackage(m_RequestsBuffer_1.first());
        m_RequestsBuffer_1.removeFirst();

    }
    isFirstBufferBusy = false;

    while(!m_RequestsBuffer_2.isEmpty())
    {
#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: second buffer";
#endif
        processPackage(m_RequestsBuffer_2.first());
        m_RequestsBuffer_2.removeFirst();
    }

}

void FlipperDatabase::processPackage(const QHash<int, QVariant> &data)
{
#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: processPackage()";
    qDebug() << "Key Value: " + QString::number(data.value(FlipperKeywords::PackageKey).toInt());
#endif
    switch (data.value(FlipperKeywords::PackageKey).toInt()) {
    case FlipperKeywords::ModbusInterface:

#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: Channel: " + QString::number(data.value(FlipperKeywords::FlipperChannel).toInt()) ;
#endif
        insertDewPointToDatabase(data.value(FlipperKeywords::FlipperChannel).toInt(), data.value(FlipperKeywords::Dewpoint).toDouble(), data.value(FlipperKeywords::SampleTimePoint).toULongLong());
        break;

    case FlipperKeywords::GUI:
        if(data.value(FlipperKeywords::GUI).toInt() == FlipperKeywords::updateGauge)
        {

#if FlipperDatabaseDebug
            qDebug() << "Flipper Database: updateGAUGE()";
#endif
            //get Last Dew Point of CH

            getLastDewPointFromDatabase(data.value(FlipperKeywords::FlipperChannel).toInt());


        }
        else if (data.value(FlipperKeywords::GUI).toInt() == FlipperKeywords::updateChart) {
            // get multiple Dew Point of CHs
#if FlipperDatabaseDebug
            qDebug()<< "Flipper Database: requestUpdateChart() - CH = " + QString::number(data.value(FlipperKeywords::FlipperChannel).toInt());
#endif
            getDewpointFromDatabase(data.value(FlipperKeywords::FlipperChannel).toInt(), 3000);
        }
        break;

    case FlipperKeywords::Notification:
        if(data.value(FlipperKeywords::Notification).toInt()  == FlipperKeywords::getNotSyncedData)
        {
#if FlipperDatabaseDebug
            qDebug() << "Flipper Database: getNotSyncedDataFromDatabase()";
#endif
            getNotSyncedDataFromDatabase(data.value(FlipperKeywords::FlipperChannel).toInt(), data.value(FlipperKeywords::LastSampleTimePoint).toULongLong());

        }

        break;

    default:
        break;
    }
}

void FlipperDatabase::insertDewPointToDatabase(const int &CH, const double &value, const quint64 timePoint)
{
#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: insertDewPointToDatabase()";
    qDebug() << "Channel: " + QString::number(CH) +" " + FlipperChannelToString.value(CH);
#endif
    QSqlQuery aQuery;

    aQuery.prepare("INSERT INTO " + FlipperChannelToString.value(CH) + " (timeStamp, data) VALUES (:time, :data) ");
    aQuery.bindValue(":time",timePoint );
    aQuery.bindValue(":data", value);

    if(aQuery.exec())
    {
#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: insert succeed";
        qDebug() << "Flipper Database: Emitting out package";
#endif
        QHash<int, QVariant> package;

        package.insert(PackageKey, updateGauge);
        package.insert(FlipperChannel, CH);
        package.insert(updateGauge, value);

        emit toGuiInterface(package);

        package.clear();
        package.insert(PackageKey, updateChart);
        package.insert(FlipperChannel, CH);
        package.insert(updateChart, QPointF(timePoint, value));

        emit toGuiInterface(package);
    }
    else
    {
#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: insert failed";
#endif
    }

}


void FlipperDatabase::getLastDewPointFromDatabase(const int &CH)
{

#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: getLastDewPointFromDatabase()";
    qDebug() << "Channel: " + QString::number(CH);
#endif
    QSqlQuery aQuery;

    if( aQuery.exec("SELECT * FROM " + FlipperChannelIntToString.value(CH) + " ORDER BY timeStamp DESC LIMIT 1" ))
    {
#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: query succeed";
#endif
        while(aQuery.next())
        {
#if FlipperDatabaseDebug
            qDebug() << "Flipper Database: query data:" + aQuery.value("data").toString();
#endif
            QHash<int, QVariant> package;

            package.insert(PackageKey, updateGauge);
            package.insert(FlipperChannel, CH);
            package.insert(updateGauge, aQuery.value("data").toDouble());
            emit toGuiInterface(package);
        }
    }
    else
    {
#if FlipperDatabaseDebug
        qDebug() << "Flipper Database: query FAILED";
#endif
    }
}

void FlipperDatabase::getDewpointFromDatabase(const int &CH, const int &samples)
{
#if FlipperDatabaseDebug
    qDebug() << "Flipper Database: getDewpointFromDatabase()";
    qDebug() << "CH: " + QString::number(CH);
#endif
    QSqlQuery aQuery;

    if( aQuery.exec("SELECT * FROM " + FlipperChannelIntToString.value(CH) + " ORDER BY timeStamp ASC LIMIT " + QString::number(samples) ))
    {
        while(aQuery.next())
        {
            QHash<int, QVariant> package;
#if FlipperDatabaseDebug
            qDebug() << "timeStamp: " + QString::number(aQuery.value("timeStamp").toULongLong()) + " data: " + QString::number(aQuery.value("data").toDouble());

#endif
            package.insert(PackageKey, updateChart);
            package.insert(FlipperChannel, CH);
            package.insert(updateChart, QPointF((quint64) aQuery.value("timeStamp").toULongLong(),aQuery.value("data").toDouble()));
            emit toGuiInterface(package);
        }
    }
}

void FlipperDatabase::getNotSyncedDataFromDatabase(const int &channels, const quint64 &stoppedTimeStamp)
{
#if FlipperDatabaseDebug
    qDebug() << "FlipperDatabase::getNotSyncedDataFromDatabase()";
    qDebug() << "Channel: " + QString::number(channels) + " timeStamp: " + QString::number(stoppedTimeStamp);
#endif

    QList<QString> ChannelName;
    // will deal with all channels here; break package at 1000 data point
    if(channels & Channel1)
    {
#if FlipperDatabaseDebug
    qDebug() << "getNotSyncedData Channel 1";
#endif
        ChannelName.append(FlipperChannelToString.value(Channel1));
    }
    if(channels & Channel2)
    {
#if FlipperDatabaseDebug
    qDebug() << "getNotSyncedData Channel 2";
#endif
        ChannelName.append(FlipperChannelToString.value(Channel2));
    }
    if(channels & Channel3)
    {
#if FlipperDatabaseDebug
    qDebug() << "getNotSyncedData Channel 3";
#endif
        ChannelName.append(FlipperChannelToString.value(Channel3));
    }


    for(int i = 0; i < ChannelName.count(); i++)
    {

#if FlipperDatabaseDebug
    qDebug() << "Enter creating data loop";
#endif
        QSqlQuery aQuery;
        QJsonObject jSonpackage;

        jSonpackage.insert("Channel", FlipperChannelToString.key(ChannelName.at(i)));

        QJsonArray data;
        QString lastTimeStamp=QString::number(stoppedTimeStamp);
        bool dataAvailable=true;

        while(dataAvailable)
        {
#if FlipperDatabaseDebug

    qDebug() << "Query Statment: select * from " + ChannelName.at(i) + " where timeStamp > " + lastTimeStamp + " limit 1000";
#endif
            if(aQuery.exec("select * from " + ChannelName.at(i) + " where timeStamp > " + lastTimeStamp + " limit 1000"))
            {
#if FlipperDatabaseDebug
    qDebug() << " Checking Query size";
#endif
                if(aQuery.size() != 0 && aQuery.size() != -1 )
                {
#if FlipperDatabaseDebug
    qDebug() << " Checking Query size !=0 && != -1";
#endif
                    while(aQuery.next())
                    {
                        data << QJsonObject{{aQuery.value("timeStamp").toString(),aQuery.value("data").toDouble()}};
                        lastTimeStamp = aQuery.value("timeStamp").toString();
                    }

                    jSonpackage.insert("Data", data);

                    QHash<int,QVariant> package;
                    package.insert(FlipperKeywords::PackageKey, FlipperKeywords::Notification);
                    package.insert(FlipperKeywords::Notification, FlipperKeywords::getNotSyncedData);
                    package.insert(FlipperKeywords::getNotSyncedData, jSonpackage);
#if FlipperDatabaseDebug
    qDebug() << " Emitting syncing package to Notification Module";
#endif
                    emit toFlipperNotificatoin(package);
                }
                else
                {
#if FlipperDatabaseDebug
    qDebug() << " LoopsEnd , no new data available ";
#endif
                    dataAvailable = false;
                }
            }
            else
            {
#if FlipperDatabaseDebug
    qDebug() << " LoopsEnd , query failed ";
#endif
                dataAvailable = false;
            }
        }
    }
}
