#ifndef FLIPPERDATABASE_H
#define FLIPPERDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QHash>
#include <QList>
#include "globalconf.h"

class FlipperDatabase: public QObject
{
    Q_OBJECT
    QSqlDatabase m_database;
    QString m_databasePath;
    void createTablesIfNotExists();

    QList<QHash<int,QVariant>> m_RequestsBuffer_1;
    QList<QHash<int,QVariant>> m_RequestsBuffer_2;
    bool isFirstBufferBusy = false;
    void doWork();
    void processPackage(const QHash<int,QVariant> &data);

    // super small internal functions
    void insertDewPointToDatabase(const int &CH, const double &value);
public:
    FlipperDatabase(const QString &databasePath, QObject * parent = nullptr);
    ~FlipperDatabase();


public slots:
    void openDatabase();
    void in(const QHash<int,QVariant> &input);
signals:
    void out(const QHash<int,QVariant> &output);
};

#endif // FLIPPERDATABASE_H
