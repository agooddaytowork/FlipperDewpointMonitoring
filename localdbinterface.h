#ifndef LOCALDBINTERFACE_H
#define LOCALDBINTERFACE_H


#include <QtSql/QSqlDatabase>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QAbstractAxis>
#include <QtSql/QSqlQuery>

#include "flippersettings.h"
QT_CHARTS_USE_NAMESPACE

class LocalDBInterface : public QObject
{
    Q_OBJECT

public:
     LocalDBInterface(const QString &dbUsername, const QString &dbPassword, const QString &dbName, QObject *parent = 0);

     QHash<QString, QVariant> FlipperSetting;
public slots:
    void start();
    QHash<QString, QVariant> loadFlipperSettingsfromDB();
    void updateflipperSettingsToDB(const QHash<QString, QVariant> &tmpHash);
signals:
    void databaseReady();
private:
    QString m_dbUsername;
    QString m_dbPassword;
    QString m_dbName;
    QSqlDatabase localDb;
    //flipperSettings currentFlipperSettings;

};

#endif // LOCALDBINTERFACE_H
