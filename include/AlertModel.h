#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QString>

#include "AlertData.h"

class AlertModel: public QAbstractListModel {
    Q_OBJECT

public:
    enum {
        message = Qt::UserRole,
        status
    };

    explicit AlertModel(QObject* parent = nullptr);

    bool setData(const QModelIndex& idx, const QVariant& value, int role) override;
    [[nodiscard]] int rowCount (const QModelIndex& idx) const override;
    [[nodiscard]] QVariant data (const QModelIndex& idx, int role) const override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex& idx) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void append(const QString& message, int status);

public slots:
    void beginInsertRowsSlot(int first, int last, const QModelIndex& parent);
    void endInsertRowsSlot();

private:
    AlertData& m_data;
};
