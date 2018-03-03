//#ifndef FLIPPERSETTINGMODEL_H
//#define FLIPPERSETTINGMODEL_H

//#include <QAbstractListModel>
//#include <QObject>
//#include "flippersettings.h"

//class flipperSettingModel : public QAbstractListModel
//{

//    Q_OBJECT

//public:

//    enum flipperSettingObjectRoles
//    {
//        flipperId = Qt::UserRole + 1,
//        depotName,
//        flipperIp,
//        flipperPort,
//        decimalPointCH1,
//        decimalPointCH2,
//        decimalPointCH3,
//        decimalPointCH4,
//        decimalPointCH5,
//        decimalPointCH6,
//        notificationMailAddress,
//        notificaiionPassword,
//        standAloneMode,
//        sendAlertNotification,
//        sendDailyNotification,
//        channelEnable,
//        serverMode,
//        OOSpecCH1,
//        OOSpecCH2,
//        OOSpecCH3,
//        OOSpecCH4,
//        OOSpecCh5,
//        OOSpecCH6
//    };

//    flipperSettingModel(QObject * parent = 0);

//    void addFlipperSetting(const flipperSettings &setting);
//    int rowCount(const QModelIndex & parent = QModelIndex()) const;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) ;

//protected:
//    QHash<int, QByteArray> roleNames() const;
//private:
//    QHash<int, flipperSettings> m_flipperSettingHash;
//    QHash<int, QModelIndex> m_flipperSettingIndexHash;


//};

//#endif // FLIPPERSETTINGMODEL_H
