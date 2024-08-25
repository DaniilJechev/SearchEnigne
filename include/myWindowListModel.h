#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <qtypes.h>

class MyWindowListModel : public QAbstractListModel{
    Q_OBJECT

public:
    enum {
        message = Qt::UserRole
    };

    explicit MyWindowListModel(QObject* parent = nullptr): QAbstractListModel(parent) {}

    bool setData(const QModelIndex& idx, const QVariant& value, int role) override;
    [[nodiscard]] int rowCount(const QModelIndex& idx) const override;
    [[nodiscard]] QVariant data (const QModelIndex& idx, int role) const override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &idx) const override;
    [[nodiscard]] QHash <int, QByteArray> roleNames() const override;
    Q_INVOKABLE void appendMessage(const QString &message);
    Q_INVOKABLE void remove(qsizetype idxStart, qsizetype countToDelete = 1);
    Q_INVOKABLE void fillData(int listModelType);
    Q_INVOKABLE QList<QString> getAllData();

private:
    QList<QString> m_data;
};
