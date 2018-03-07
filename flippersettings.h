#ifndef FLIPPERSETTING_H
#define FLIPPERSETTING_H

#include <QSettings>
#include "flipperinterface.h"

class FlipperSetting: public QObject
{

    Q_OBJECT

    QString m_settingPath;

    void loadSettingFromFile();
public:
    explicit FlipperSetting(const QString &settingPath, QObject * parent =0);
    Q_INVOKABLE int getid() const;
    Q_INVOKABLE int getSVAddress() const;
    Q_INVOKABLE QString getDepotName()const;
    Q_INVOKABLE QString getFlipperIp() const;
    Q_INVOKABLE int getFlipperPort() const;
    Q_INVOKABLE int getCH1DecimalPoint() const;
    Q_INVOKABLE int getCH2DecimalPoint() const;
    Q_INVOKABLE int getCH3DecimalPoint() const;
    Q_INVOKABLE int getCH4DecimalPoint() const;
    Q_INVOKABLE int getCH5DecimalPoint() const;
    Q_INVOKABLE int getCH6DecimalPoint() const;
    Q_INVOKABLE QString getNotificationMailAddress() const;
    Q_INVOKABLE QString getNotificationMailPassword() const;
    Q_INVOKABLE  bool isStandAloneMode() const;
    Q_INVOKABLE bool isSendingDailyNotification() const;
    Q_INVOKABLE  bool isSendingAlertNotification() const;
    Q_INVOKABLE  bool isServerMode() const;
    Q_INVOKABLE bool isAutoStart() const;
    Q_INVOKABLE  int getChannelEnable() const;
    Q_INVOKABLE bool isthisChannelEnable(int const &ch);
    Q_INVOKABLE void setChannelEnable(int const &ch, bool const &checked);
    Q_INVOKABLE  double getCh1OOSpec() const;
    Q_INVOKABLE  double getCh2OOSpec() const;
    Q_INVOKABLE  double getCh3OOSpec() const;
    Q_INVOKABLE  double getCh4OOSpec() const;
    Q_INVOKABLE  double getCh5OOSpec() const;
    Q_INVOKABLE  double getCh6OOSpec() const;
    Q_INVOKABLE  int getDecimalPoint(int const &CH) const;
    Q_INVOKABLE void setDecimailPoint(int const &CH, int const &value);
    Q_INVOKABLE double getChannelOOSpec(int const &CH) const;
    Q_INVOKABLE QString getLockScreenPassword() const;
    Q_INVOKABLE void updateOOSpec(int const &CH, double const &value);
    Q_INVOKABLE void updateFlipperSetting(QString const &key, QVariant const &value);

     Q_INVOKABLE QString getEth0MacAddress();
     void setEth0MacAddress(const QString &Mac);


};

#endif // FLIPPERSETTING_H
