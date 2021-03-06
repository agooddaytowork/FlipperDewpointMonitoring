
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
#include "flippernotification.h"
#include "guiinterface.h"
#include "mouseeventspy.h"


QString getEth0MACAddressFromSystem(QString const &scriptPath)
{
    QProcess exec;

    QStringList argo,list;

    argo <<scriptPath;

    list <<"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:";

    exec.setEnvironment(list);
    exec.setProcessChannelMode(QProcess::MergedChannels );
    exec.start("/bin/sh", argo);
    exec.waitForFinished();
    QString output = exec.readLine();
    output = output.simplified();
    qDebug() << output;
    return output;
}


int main(int argc, char *argv[])
{

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    qRegisterMetaType<QHash<int,QVariant>>("GlobalPackage");
    qmlRegisterType<RadialBar>("CustomControls", 1, 0, "RadialBar");
    qmlRegisterSingletonType<MouseEventSpy>("MouseEventSpy", 1, 0, "MouseEventSpy", MouseEventSpy::singletonProvider);
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

#if (defined (LINUX) || defined (__linux__))
    qDebug() << "LINUX STUFFFF";
    aFlipperSetting.setEth0MacAddress(getEth0MACAddressFromSystem("/home/pi/InitScripts/getEth0MacAddress.sh"));
#endif

    FlipperInterface aFlipperInterface(aFlipperSetting.getFlipperIp(), aFlipperSetting.getFlipperPort(), aFlipperSetting.getSVAddress());
    aFlipperInterface.setEnableChannels(aFlipperSetting.getChannelEnable());
    aFlipperInterface.setCollectDataInterval(aFlipperSetting.getFlipperInterfaceCollectDataInterval());
    aFlipperInterface.setDecimalValue(Channel1, aFlipperSetting.getCH1DecimalPoint());
    aFlipperInterface.setDecimalValue(Channel2, aFlipperSetting.getCH1DecimalPoint());
    aFlipperInterface.setDecimalValue(Channel3, aFlipperSetting.getCH1DecimalPoint());



    FlipperDatabase myDatabase((QCoreApplication::applicationDirPath()+"/flipperDatabase.db"));
    FlipperNotification aNotification("https://aws.essdepots.com",QCoreApplication::applicationDirPath()+"/flipperMonitoring.ini");
    aNotification.setSVWatchDogTimerInterVal(aFlipperSetting.getSVWatchDogTimerInterval());
    GuiInterface aGuiInterface;

    // create permanent thread
    QThread *backEndThread = new QThread();
    QThread *NotificatioNThread = new QThread();
    myDatabase.moveToThread(backEndThread);
    aFlipperInterface.moveToThread(backEndThread);
    aNotification.moveToThread(backEndThread);

    // Connect everything
    QObject::connect(backEndThread,SIGNAL(started()),&myDatabase, SLOT(openDatabase()));
    QObject::connect(backEndThread,SIGNAL(started()),NotificatioNThread,SLOT(start()));
 //   QObject::connect(NotificatioNThread,SIGNAL(started()),&aNotification,SLOT(startServerWatchDog()));
   QObject::connect(backEndThread,SIGNAL(started()),&aNotification,SLOT(startServerWatchDog()));

    QObject::connect(&myDatabase,SIGNAL(toGuiInterface(QHash<int,QVariant>)),&aGuiInterface,SLOT(in(QHash<int,QVariant>)));
    QObject::connect(&myDatabase,SIGNAL(toFlipperNotificatoin(QHash<int,QVariant>)),&aNotification,SLOT(in(QHash<int,QVariant>)));

    QObject::connect(&aGuiInterface,SIGNAL(toDatabase(QHash<int,QVariant>)),&myDatabase,SLOT(in(QHash<int,QVariant>)));
    QObject::connect(&aGuiInterface,SIGNAL(toFlipperInterface(QHash<int,QVariant>)),&aFlipperInterface,SLOT(in(QHash<int,QVariant>)));

    QObject::connect(&aFlipperInterface, SIGNAL(out(QHash<int,QVariant>)), &myDatabase, SLOT(in(QHash<int,QVariant>)));
    QObject::connect(&aFlipperInterface,SIGNAL(out(QHash<int,QVariant>)),&aNotification,SLOT(in(QHash<int,QVariant>)));
    QObject::connect(&aFlipperInterface,SIGNAL(toGuiInterface(QHash<int,QVariant>)),&aGuiInterface,SLOT(in(QHash<int,QVariant>)));

    QObject::connect(&aNotification, SIGNAL(toDatabase(QHash<int,QVariant>)),&myDatabase,SLOT(in(QHash<int,QVariant>)));
    QObject::connect(&aNotification,SIGNAL(toGuiInterface(QHash<int,QVariant>)),&aGuiInterface,SLOT(in(QHash<int,QVariant>)));



    backEndThread->start();
    QQmlContext *thisContext = engine.rootContext();
    // expose FlipperSettings to QML
    thisContext->setContextProperty("theGuiInterface", &aGuiInterface);
    thisContext->setContextProperty("flipperSetting", &aFlipperSetting);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
