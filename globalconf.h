#ifndef GLOBALCONF_H
#define GLOBALCONF_H

#include <QDebug>
#define FlipperDatabaseDebug (1)
#define FlipperInterfaceDebug (0)
#define GuiInterfaceDebug (0)
#define FlipperNotificationDebug (1)

#define UPDATE_DATA_SV_PATH "/KTproj/flipperdataupdatev2.php"
//#define SVWATCHDOGTIMER_INTERVAL 200000
//#define FLIPPERINTERFACECOLLECTDATA_INTERVAL 60000
#include <QProcess>



enum FlipperKeywords{
    PackageKey,
    ModbusInterface,
    Database,
    GUI,
    Notification,

    // For Flipper Interface
    FlipperChannel,
    Dewpoint,
    SampleTimePoint,
    // For Gui
    Request,
    updateGauge,
    updateChart,
    startRecording,
    stopRecording,
    FlipperEnableChannelsChanged,
    FlipperTCPAddressChanged,
    FlipperTcpAddress,
    FlipperTcpPort,
    FlipperSVAddress,
    //////////////////////
    NumberOfSample,

    // NotificationModule
    LastSampleTimePoint,
    getNotSyncedData,


    // statusFlag

    serverIsOffline,
    serverIsOnline,

    flipperIsOffline,
    flipperIsOnline

};

enum ChannelEnableEnum{
    Channel1 = 0x01,
    Channel2 = 0x02,
    Channel3 = 0x04,
    Channel4 = 0x08,
    Channel5 = 0x10,
    Channel6 = 0x20
};

const QHash<int,QString> FlipperChannelToString{
    {Channel1, "CH1"},
    {Channel2, "CH2"},
    {Channel3, "CH3"},
    {Channel5, "CH4"},
    {Channel5, "CH5"},
    {Channel6, "CH6"}
};

const QHash<int,QString> FlipperChannelIntToString{
    {0, "CH1"},
    {1, "CH2"},
    {2, "CH3"},
    {3, "CH4"},
    {4, "CH5"},
    {5, "CH6"}
};

const QHash<int,int> FlipperChannelToInt{
    {Channel1, 0},
    {Channel2, 1},
    {Channel3, 2},
    {Channel5, 3},
    {Channel5, 4},
    {Channel6, 5}
};


#endif // GLOBALCONF_H
