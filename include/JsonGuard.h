#pragma once

#include <QString>
#include <QObject>

void checkConfig();
void checkRequests();
void checkAnswers();

class GuardWrapper: public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE QString checkData();
};
