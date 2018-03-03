
#include "radialbar.h"
#include <QThread>
#include <QtWidgets/QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include "flippersettingmodel.h"
#include "flippersettings.h"
#include "globalconf.h"
#include "flipperdatabase.h"
#include "flipperinterface.h"
#include "guiinterface.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);


    qmlRegisterType<RadialBar>("CustomControls", 1, 0, "RadialBar");
    QQmlApplicationEngine engine;
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif

    // setup Application Setting
    qDebug() << QCoreApplication::applicationDirPath()+"/flipperMonitoring.ini";
    qDebug() << QCoreApplication::applicationDirPath()+"/flipperDatabase.db";

    // Initiailizing all modules
    FlipperSetting aFlipperSetting(QCoreApplication::applicationDirPath()+"/flipperMonitoring.ini");

    FlipperInterface aFlipperInterface(aFlipperSetting.getFlipperIp(), aFlipperSetting.getFlipperPort(), aFlipperSetting.getSVAddress());
    aFlipperInterface.setEnableChannels(aFlipperSetting.getChannelEnable());
    aFlipperInterface.setCollectDataInterval(60000);


    FlipperDatabase myDatabase((QCoreApplication::applicationDirPath()+"/flipperDatabase.db"));



    GuiInterface aGuiInterface;

    // create permanent thread
    QThread backEndThread;

    // Connect everything
    QObject::connect(&backEndThread,SIGNAL(started()),&myDatabase, SLOT(openDatabase()));
    //QObject::connect(&theFlipperInterface,SIGNAL(out(QHash<int,QVariant>)),&myDatabase,SLOT(in(QHash<int,QVariant>)));


    QQmlContext *thisContext = engine.rootContext();
    // expost FlipperSettings to QML
    thisContext->setContextProperty("theGuiInterface", &aGuiInterface);
    thisContext->setContextProperty("flipperSetting", &aFlipperSetting);



    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
