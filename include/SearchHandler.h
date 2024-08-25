#pragma once

#include <QObject>

class SearchHandler : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE void search();
};