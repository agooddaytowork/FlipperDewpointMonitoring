#ifndef GLOBALCONF_H
#define GLOBALCONF_H

#include <QDebug>

enum FlipperKeywords{
    PackageKey,
    ModbusInterface,
    Database,
    GUI,
    Notification,

    // For Flipper Interface
    FlipperChannel,
    Dewpoint,

    // For Gui
    Request,
    updateGauge,
    updateChart,
    startRecording,
    stopRecording,
    //////////////////////
    NumberOfSample
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

const QHash<int,int> FlipperChannelToInt{
    {Channel1, 0},
    {Channel2, 1},
    {Channel3, 2},
    {Channel5, 3},
    {Channel5, 4},
    {Channel6, 5}
};

#endif // GLOBALCONF_H
