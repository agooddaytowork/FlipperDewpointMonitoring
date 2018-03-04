#include "flipperdatabase.h"
#include <QDateTime>

#define FlipperDatabaseDebug (1)

FlipperDatabase::~FlipperDatabase()
{

}

FlipperDatabase::FlipperDatabase(const QString &databasePath, QObject *parent): m_databasePath(databasePath), QObject(parent)
{

#ifdef FlipperDatabaseDebug
    qDebug() << "Flipper Database: FlipperDatabase()";
#endif


}

void FlipperDatabase::openDatabase()
{
#ifdef FlipperDatabaseDebug
    qDebug() << "Flipper Database: openDatabase()";
#endif
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(m_databasePath);

    if(!m_database.open())
    {
#ifdef FlipperDatabaseDebug
        qDebug() << "Error, connection with database failed! ";
#endif
    }
    else
    {
#ifdef FlipperDatabaseDebug
        qDebug() << "Database Connection OK! ";
#endif
        createTablesIfNotExists();
        doWork();
    }
}


void FlipperDatabase::createTablesIfNotExists()
{
#ifdef FlipperDatabaseDebug
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
#ifdef FlipperDatabaseDebug
    qDebug() << "Flipper Database: in()";
#endif
    if(!isFirstBufferBusy)
    {
#ifdef FlipperDatabaseDebug
        qDebug() << "Flipper Database: first buffer";
#endif
        m_RequestsBuffer_1.append(input);
         doWork();
    }
    else
    {
#ifdef FlipperDatabaseDebug
        qDebug() << "Flipper Database: second buffer";
#endif
        m_RequestsBuffer_2.append(input);
    }
}

void FlipperDatabase::doWork()
{
#ifdef FlipperDatabaseDebug
    qDebug() << "Flipper Database: doWork()";
#endif
    isFirstBufferBusy = true;
    while(!m_RequestsBuffer_1.isEmpty())
    {

#ifdef FlipperDatabaseDebug
        qDebug() << "Flipper Database: first buffer";
#endif
        processPackage(m_RequestsBuffer_1.first());
        m_RequestsBuffer_1.removeFirst();

    }
    isFirstBufferBusy = false;

    while(!m_RequestsBuffer_2.isEmpty())
    {
#ifdef FlipperDatabaseDebug
        qDebug() << "Flipper Database: second buffer";
#endif
        processPackage(m_RequestsBuffer_2.first());
        m_RequestsBuffer_2.removeFirst();
    }

}

void FlipperDatabase::processPackage(const QHash<int, QVariant> &data)
{
#ifdef FlipperDatabaseDebug
    qDebug() << "Flipper Database: processPackage()";
    qDebug() << "Key Value: " + QString::number(data.value(FlipperKeywords::PackageKey).toInt());
#endif
    switch (data.value(FlipperKeywords::PackageKey).toInt()) {
    case FlipperKeywords::ModbusInterface:

#ifdef FlipperDatabaseDebug
    qDebug() << "Flipper Database: Channel: " + QString::number(data.value(FlipperKeywords::FlipperChannel).toInt()) ;
#endif
        insertDewPointToDatabase(data.value(FlipperKeywords::FlipperChannel).toInt(), data.value(FlipperKeywords::Dewpoint).toDouble());
        break;

    case FlipperKeywords::GUI:
        if(data.value(FlipperKeywords::Request).toInt() == FlipperKeywords::updateGauge)
        {
            //get Last Dew Point of CH
        }
        else if (data.value(FlipperKeywords::Request).toInt() == FlipperKeywords::updateChart) {
            // get multiple Dew Point of CHs
        }
        break;

    case FlipperKeywords::Notification:
        break;

    default:
        break;
    }
}

void FlipperDatabase::insertDewPointToDatabase(const int &CH, const double &value)
{
#ifdef FlipperDatabaseDebug
    qDebug() << "Flipper Database: insertDewPointToDatabase()";
    qDebug() << "Channel: " + QString::number(CH) +" " + FlipperChannelToString.value(CH);
#endif
    QSqlQuery aQuery;

    int currentTime = QDateTime::currentMSecsSinceEpoch();
    aQuery.prepare("INSERT INTO " + FlipperChannelToString.value(CH) + " (timeStamp, data) VALUES (:time, :data) ");
    aQuery.bindValue(":time",currentTime );
    aQuery.bindValue(":data", value);

    if(aQuery.exec())
    {
#ifdef FlipperDatabaseDebug
        qDebug() << "Flipper Database: insert succeed";
        qDebug() << "Flipper Database: Emitting out package";
#endif

        QHash<int, QVariant> package;

        package.insert(PackageKey, updateGauge);
        package.insert(FlipperChannel, CH);
        package.insert(updateGauge, value);

        out(package);

        package.clear();
        package.insert(PackageKey, updateChart);
        package.insert(FlipperChannel, CH);
        package.insert(updateChart, QPointF(currentTime, value));

        out(package);
    }
    else
    {
#ifdef FlipperDatabaseDebug
        qDebug() << "Flipper Database: insert failed";
#endif
    }

}
