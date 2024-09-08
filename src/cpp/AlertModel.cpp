#include "AlertModel.h"
#include "QAbstractListModel"

AlertModel::AlertModel(QObject *parent)
    : QAbstractListModel(parent), m_data(*AlertData::getInstance()) {
    m_data.raiseModelExists();
    QObject::connect(AlertData::getInstance(), &AlertData::startAppend,
                     this, &AlertModel::beginInsertRowsSlot);
    QObject::connect(AlertData::getInstance(), &AlertData::endAppend,
                     this, &AlertModel::endInsertRowsSlot);
}

bool AlertModel::setData(const QModelIndex &idx, const QVariant &value, int role) {
    if (idx.isValid()) {
        if (role == message && m_data[idx.row()].m_message != value.toString()) {
            m_data[idx.row()].m_message = value.toString();
            emit dataChanged(idx, idx, QList<int>() << role);
            return true;
        } else if (role == status && m_data[idx.row()].m_status != value.toInt()) {
            m_data[idx.row()].m_status = value.toInt();
            emit dataChanged(idx, idx, QList<int>() << role);
            return true;
        }
    }
    return false;
}

int AlertModel::rowCount(const QModelIndex &idx) const {
    if (!idx.isValid()) {
        return static_cast<int>(m_data.size());
    }
    return 0;
}

QVariant AlertModel::data(const QModelIndex &idx, int role) const {
    if (!idx.isValid() || idx.row() >= m_data.size()) {
        return {};
    }
    switch (role) {
        case message:
        return m_data[idx.row()].m_message;

        case status:
            return m_data[idx.row()].m_status;

        default:
            return {};
    }
}

Qt::ItemFlags AlertModel::flags(const QModelIndex &idx) const {
    return Qt::NoItemFlags;
}

QHash<int, QByteArray> AlertModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[message] = "message";
    names[status] = "status";
    return names;
}

void AlertModel::append(const QString& message, int status) {
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    AlertData::appendAlert(message.toStdString(), status);
    endInsertRows();
}

void AlertModel::beginInsertRowsSlot(int first, int last, const QModelIndex &parent) {
    beginInsertRows(parent, first, last);
}

void AlertModel::endInsertRowsSlot() {
    endInsertRows();
}