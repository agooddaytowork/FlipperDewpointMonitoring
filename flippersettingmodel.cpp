//#include "flippersettingmodel.h"


//flipperSettingModel::flipperSettingModel(QObject *parent): QAbstractListModel(parent)
//{

//}


//void flipperSettingModel::addFlipperSetting(const flipperSettings &setting)
//{
//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    m_flipperSettingHash.insert(setting.getid(), setting);
//    endInsertRows();
//}

//int flipperSettingModel::rowCount(const QModelIndex &parent) const
//{

//    Q_UNUSED(parent);

//    return m_flipperSettingHash.count();
//}

//QVariant flipperSettingModel::data(const QModelIndex &index, int role) const
//{

//    if(index.row() < 0 || index.row() >= m_flipperSettingHash.count())
//        return QVariant();

//    flipperSettings setting = m_flipperSettingHash.values()[index.row()];
//    if(role == flipperId) return setting.getid();
//    else if (role == depotName) return setting.getDepotName();
//    else if (role == flipperIp) return setting.getFlipperIp();
//    else if (role == flipperPort) return setting.getFlipperPort();
//    else if (role == decimalPointCH1) return setting.getCH1DecimalPoint();
//    else if (role == decimalPointCH2) return setting.getCH2DecimalPoint();
//    else if (role == decimalPointCH3) return setting.getCH3DecimalPoint();
//    else if (role == decimalPointCH4) return setting.getCH4DecimalPoint();
//    else if (role == decimalPointCH5) return setting.getCH5DecimalPoint();
//    else if (role == decimalPointCH6) return setting.getCH6DecimalPoint();
//    else if (role == notificationMailAddress) return setting.getNotificationMailAddress();
//    else if (role == notificaiionPassword) return setting.getNotificationMailPassword();
//    else if (role == standAloneMode) return setting.isStandAloneMode();
//    else if (role == sendAlertNotification) return setting.isSendingAlertNotification();
//    else if (role == sendDailyNotification) return setting.isSendingDailyNotification();
//    else if (role == channelEnable) return setting.getChannelEnable();
//    else if (role == serverMode) return setting.isServerMode();
//    else if (role == OOSpecCH1) return setting.getCh1OOSpec();
//    else if (role == OOSpecCH2) return setting.getCh2OOSpec();
//    else if (role == OOSpecCH3) return setting.getCh3OOSpec();
//    else if (role == OOSpecCH4) return setting.getCh4OOSpec();
//    else if (role == OOSpecCh5) return setting.getCh5OOSpec();
//    else if (role == OOSpecCH6) return setting.getCh6OOSpec();

//    return QVariant();
//}


//bool flipperSettingModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if(index.row() < 0 || index.row() >= m_flipperSettingHash.count())
//        return false;

//    flipperSettings setting = m_flipperSettingHash.values()[index.row()];
//    if(role == flipperId)  setting.updateFlipperSetting("flipperId", value.toString());
//    else if (role == depotName) setting.updateFlipperSetting("depotName", value.toString());
//    else if (role == flipperIp) setting.updateFlipperSetting("flipperIp", value.toString());
//    else if (role == flipperPort) setting.updateFlipperSetting("flipperPort", value.toInt());
//    else if (role == decimalPointCH1) setting.updateFlipperSetting("decimalPointCH1", value.toInt());
//    else if (role == decimalPointCH2) setting.updateFlipperSetting("decimalPointCH2", value.toInt());
//    else if (role == decimalPointCH3) setting.updateFlipperSetting("decimalPointCH3", value.toInt());
//    else if (role == decimalPointCH4) setting.updateFlipperSetting("decimalPointCH4", value.toInt());
//    else if (role == decimalPointCH5) setting.updateFlipperSetting("decimalPointCH5", value.toInt());
//    else if (role == decimalPointCH6) setting.updateFlipperSetting("decimalPointCH6", value.toInt());
//    else if (role == notificationMailAddress) setting.updateFlipperSetting("notificationMailAddress", value.toString());
//    else if (role == notificaiionPassword) setting.updateFlipperSetting("notificaiionPassword", value.toString());
//    else if (role == standAloneMode) setting.updateFlipperSetting("standAloneMode", value.toBool());
//    else if (role == sendAlertNotification) setting.updateFlipperSetting("sendAlertNotification", value.toBool());
//    else if (role == sendDailyNotification) setting.updateFlipperSetting("sendDailyNotification", value.toBool());
//    else if (role == channelEnable) setting.updateFlipperSetting("channelEnable", value.toInt());
//    else if (role == serverMode) setting.updateFlipperSetting("serverMode", value.toBool());

//    else if (role == OOSpecCH1) setting.updateFlipperSetting("OOSpecCH1", value.toDouble());
//    else if (role == OOSpecCH2) setting.updateFlipperSetting("OOSpecCH2", value.toDouble());
//    else if (role == OOSpecCH3) setting.updateFlipperSetting("OOSpecCH3", value.toDouble());
//    else if (role == OOSpecCH4) setting.updateFlipperSetting("OOSpecCH4", value.toDouble());
//    else if (role == OOSpecCh5) setting.updateFlipperSetting("OOSpecCH5", value.toDouble());
//    else if (role == OOSpecCH6) setting.updateFlipperSetting("OOSpecCH6", value.toDouble());
//    return true;
//}

//QHash<int, QByteArray> flipperSettingModel::roleNames() const
//{
//    QHash<int, QByteArray> roles;
//    roles[flipperId] = "flipperId";
//    roles[depotName] = "depotName";
//    roles[flipperIp] = "flipperIp";
//    roles[flipperPort] = "flipperPort";
//    roles[decimalPointCH1] = "decimalPointCH1";
//    roles[decimalPointCH2] = "decimalPointCH2";
//    roles[decimalPointCH3] = "decimalPointCH3";
//    roles[decimalPointCH4] = "decimalPointCH4";
//    roles[decimalPointCH5] = "decimalPointCH5";
//    roles[decimalPointCH6] = "decimalPointCH6";
//    roles[notificationMailAddress] = "notificationMailAddress";
//    roles[notificaiionPassword] = "notificaiionPassword";
//    roles[standAloneMode] = "standAloneMode";
//    roles[sendAlertNotification] = "sendAlertNotification";
//    roles[sendDailyNotification] = "sendDailyNotification";
//    roles[channelEnable] = "channelEnable";
//    roles[serverMode] = "serverMode";

//    return roles;

//}




