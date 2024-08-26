#pragma once
#include <QObject>
#include <QString>


class DialogFinder: public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE QString openFileDialog();
    Q_INVOKABLE QString openDirDialog();
};
