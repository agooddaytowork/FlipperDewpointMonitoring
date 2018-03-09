#include "flippersettings.h"
#include <QCoreApplication>

FlipperSetting::FlipperSetting(const QString &settingPath, QObject *parent):  QObject(parent), m_settingPath(settingPath)
{
    loadSettingFromFile();
}

void FlipperSetting::loadSettingFromFile()
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);

    // check if setting exist, otherwise overwrite with default setting
    if(!m_setting.contains("id")) m_setting.value("id", 1);
    if(!m_setting.contains("DeviceName")) m_setting.setValue("DeviceName", "Default Device");
    if(!m_setting.contains("FlipperServerAddress")) m_setting.setValue("FlipperServerAddress", 1);
    if(!m_setting.contains("FlipperIP")) m_setting.setValue("FlipperIP", "192.168.1.11");
    if(!m_setting.contains("FlipperPort")) m_setting.setValue("FlipperPort", 502);
    if(!m_setting.contains("FlipperEnableChannels")) m_setting.setValue("FlipperEnableChannels", 0b00000001);
    if(!m_setting.contains("FlipperCH1DecimalPoint")) m_setting.setValue("FlipperCH1DecimalPoint", 10);
    if(!m_setting.contains("FlipperCH2DecimalPoint")) m_setting.setValue("FlipperCH2DecimalPoint", 10);
    if(!m_setting.contains("FlipperCH3DecimalPoint")) m_setting.setValue("FlipperCH3DecimalPoint", 10);
    if(!m_setting.contains("FlipperCH4DecimalPoint")) m_setting.setValue("FlipperCH4DecimalPoint", 10);
    if(!m_setting.contains("FlipperCH5DecimalPoint")) m_setting.setValue("FlipperCH5DecimalPoint", 10);
    if(!m_setting.contains("FlipperCH6DecimalPoint")) m_setting.setValue("FlipperCH6DecimalPoint", 10);
    if(!m_setting.contains("FlipperCH1OOSpec")) m_setting.setValue("FlipperCH1OOSpec", -72.0);
    if(!m_setting.contains("FlipperCH2OOSpec")) m_setting.setValue("FlipperCH2OOSpec", -72.0);
    if(!m_setting.contains("FlipperCH3OOSpec")) m_setting.setValue("FlipperCH3OOSpec", -72.0);
    if(!m_setting.contains("FlipperCH4OOSpec")) m_setting.setValue("FlipperCH4OOSpec", -72.0);
    if(!m_setting.contains("FlipperCH5OOSpec")) m_setting.setValue("FlipperCH5OOSpec", -72.0);
    if(!m_setting.contains("FlipperCH6OOSpec")) m_setting.setValue("FlipperCH6OOSpec", -72.0);
    if(!m_setting.contains("standAloneMode")) m_setting.setValue("standAloneMode", true);
    if(!m_setting.contains("sendDailyNotification")) m_setting.setValue("sendDailyNotification", true);
    if(!m_setting.contains("sendAlertNotification")) m_setting.setValue("sendAlertNotification", true);
    if(!m_setting.contains("serverMode")) m_setting.setValue("serverMode", true);
    if(!m_setting.contains("NotificationMailAddress")) m_setting.setValue("NotificationMailAddress", "tam.duong@kla-tencor.com");
    if(!m_setting.contains("NotificationMailPassword")) m_setting.setValue("NotificationMailPassword", "default");
    if(!m_setting.contains("autoStart")) m_setting.setValue("autoStart", "false");
    if(!m_setting.contains("lockScreenPassword")) m_setting.setValue("lockScreenPassword", "1234");
    if(!m_setting.contains("SVWatchDogTimerInterval")) m_setting.setValue("SVWatchDogTimerInterval", 300000);
    if(!m_setting.contains("flipperInterfaceCollectDataInterval")) m_setting.setValue("flipperInterfaceCollectDataInterval",60000);

}

int FlipperSetting::getSVWatchDogTimerInterval() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("SVWatchDogTimerInterval").toInt();
}

int FlipperSetting::getFlipperInterfaceCollectDataInterval() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("flipperInterfaceCollectDataInterval").toInt();
}


int FlipperSetting::getid() const{

    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("id").toInt();

}


int FlipperSetting::getSVAddress() const{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperServerAddress").toInt();
}
QString FlipperSetting::getDepotName() const
{

    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("DeviceName").toString();
}

QString FlipperSetting::getFlipperIp() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperIP").toString();
}

int FlipperSetting::getFlipperPort() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperPort").toInt();
}

int FlipperSetting::getCH1DecimalPoint() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH1DecimalPoint").toInt();
}

int FlipperSetting::getCH2DecimalPoint() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH2DecimalPoint").toInt();
}

int FlipperSetting::getCH3DecimalPoint() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH3DecimalPoint").toInt();
}

int FlipperSetting::getCH4DecimalPoint() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH4DecimalPoint").toInt();
}

int FlipperSetting::getCH5DecimalPoint() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH5DecimalPoint").toInt();
}

int FlipperSetting::getCH6DecimalPoint() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH6DecimalPoint").toInt();
}

int FlipperSetting::getDecimalPoint(const int &CH) const
{
    switch (CH) {
    case 1:
        return getCH1DecimalPoint();
        break;
    case 2:
        return getCH2DecimalPoint();
        break;
    case 3:
        return getCH3DecimalPoint();
        break;
    case 4:
        return getCH4DecimalPoint();
        break;
    case 5:
        return getCH5DecimalPoint();
        break;
    case 6:
        return getCH6DecimalPoint();
        break;
    }
    return 10;
}

QString FlipperSetting::getNotificationMailAddress() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("NotificationMailAddress").toString();
}


QString FlipperSetting::getNotificationMailPassword() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("NotificationMailPassword").toString();
}

bool FlipperSetting::isStandAloneMode() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("standAloneMode").toBool();
}

bool FlipperSetting::isSendingDailyNotification() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("sendDailyNotification").toBool();
}

bool FlipperSetting::isSendingAlertNotification() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("sendAlertNotification").toBool();
}

bool FlipperSetting::isServerMode() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("serverMode").toBool();
}

bool FlipperSetting::isAutoStart() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("autoStart").toBool();
}

int FlipperSetting::getChannelEnable() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperEnableChannels").toInt();
}

double FlipperSetting::getCh1OOSpec() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH1OOSpec").toDouble();
}

double FlipperSetting::getCh2OOSpec() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH2OOSpec").toDouble();
}


double FlipperSetting::getCh3OOSpec() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH3OOSpec").toDouble();
}


double FlipperSetting::getCh4OOSpec() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH4OOSpec").toDouble();
}


double FlipperSetting::getCh5OOSpec() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH5OOSpec").toDouble();
}

double FlipperSetting::getCh6OOSpec() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("FlipperCH6OOSpec").toDouble();
}

double FlipperSetting::getChannelOOSpec(const int &CH) const
{
    switch (CH) {
    case 1:
        return getCh1OOSpec();
        break;
    case 2:
        return getCh2OOSpec();
        break;
    case 3:
        return getCh3OOSpec();
        break;
    case 4:
        return getCh4OOSpec();
        break;
    case 5:
        return getCh5OOSpec();
        break;
    case 6:
        return getCh6OOSpec();
        break;
    }
    return -50.0;
}

void FlipperSetting::updateFlipperSetting(const QString &key, const QVariant &value)
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    m_setting.setValue(key, value);
}



void FlipperSetting::updateOOSpec(const int &CH, const double &value)
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    switch (CH) {
    case 1:
        m_setting.setValue("FlipperCH1OOSpec", value);
        break;
    case 2:
        m_setting.setValue("FlipperCH2OOSpec", value);
        break;
    case 3:
        m_setting.setValue("FlipperCH3OOSpec", value);
        break;
    case 4:
        m_setting.setValue("FlipperCH4OOSpec", value);
        break;
    case 5:
        m_setting.setValue("FlipperCH5OOSpec", value);
        break;
    case 6:
        m_setting.setValue("FlipperCH6OOSpec", value);
        break;
    }
}

bool FlipperSetting::isthisChannelEnable(const int &ch)
{
    int channelEnable = getChannelEnable();
    switch (ch) {
    case 1:
        if(channelEnable & Channel1) return true;
        else return false;

        break;

    case 2:
        if(channelEnable & Channel2) return true;
        else return false;
        break;
    case 3:
        if(channelEnable & Channel3) return true;
        else return false;
        break;
    case 4:
        if(channelEnable & Channel4) return true;
        else return false;
        break;
    case 5:
        if(channelEnable & Channel5) return true;
        else return false;
        break;
    case 6:
        if(channelEnable & Channel6) return true;
        else return false;
        break;
    }
    return false;
}

void FlipperSetting::setChannelEnable(const int &ch, bool const &checked)
{
    int channelEnable = getChannelEnable();
    switch (ch) {
    case 1:
        if(checked)
        {
            channelEnable |= Channel1;
        }
        else
        {
            channelEnable &= ~(Channel1);
        }
        break;
    case 2:
        if(checked)
        {
            channelEnable |= Channel2;
        }
        else
        {
            channelEnable &= ~(Channel2);
        }
        break;
    case 3:
        if(checked)
        {
            channelEnable |= Channel3;
        }
        else
        {
            channelEnable &= ~(Channel3);
        }
        break;
    case 4:
        if(checked)
        {
            channelEnable |= Channel4;
        }
        else
        {
            channelEnable &= ~(Channel4);
        }
        break;
    case 5:
        if(checked)
        {
            channelEnable |= Channel5;
        }
        else
        {
            channelEnable &= ~(Channel5);
        }
        break;
    case 6:
        if(checked)
        {
            channelEnable |= Channel6;
        }
        else
        {
            channelEnable &= ~(Channel6);
        }
        break;
    }

    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    m_setting.setValue("FlipperEnableChannels", channelEnable);
}

void FlipperSetting::setDecimailPoint(const int &CH, const int &value)
{

    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    switch (CH) {
    case 1:
        m_setting.setValue("FlipperCH1DecimalPoint", value);
        break;
    case 2:
        m_setting.setValue("FlipperCH2DecimalPoint", value);
        break;
    case 3:
        m_setting.setValue("FlipperCH3DecimalPoint", value);
        break;
    case 4:
        m_setting.setValue("FlipperCH4DecimalPoint", value);
        break;
    case 5:
        m_setting.setValue("FlipperCH5DecimalPoint", value);
        break;
    case 6:
        m_setting.setValue("FlipperCH6DecimalPoint", value);
        break;
    }

}


QString FlipperSetting::getLockScreenPassword() const
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("lockScreenPassword").toString();
}

QString FlipperSetting::getEth0MacAddress()
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    return m_setting.value("eth0MacAddress").toString();
}


void FlipperSetting::setEth0MacAddress(const QString &Mac)
{
    QSettings m_setting(m_settingPath, QSettings::IniFormat);
    m_setting.setValue("eth0MacAddress", Mac);
}

