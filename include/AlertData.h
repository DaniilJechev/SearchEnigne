#pragma once

#include <QList>
#include <QString>
#include <QModelIndex>
#include <QObject>

#include "globals.h"


struct AlertItem {
    QString m_message;
    int m_status;
    AlertItem (const QString &message, int status):
        m_message(message), m_status(status){}
};

class AlertData : public QObject {
    Q_OBJECT

private:
    static bool isAlertModelExist();
    static AlertData* alertData;
    AlertData() = default;

public:
    AlertData(AlertData& other) = delete;
    AlertData operator= (const AlertData& other) = delete;

    AlertItem& operator[](size_t idx);
    [[nodiscard]] size_t size();

    static AlertData* getInstance();
    static void raiseModelExists();
    static void appendAlert(const std::string &message, int status = AlertStates::Safely);

signals:
    void startAppend(int first, int second, const QModelIndex& parent);
    void endAppend();

private:
    QList<AlertItem> m_data;
    bool modelExists = false;
};
