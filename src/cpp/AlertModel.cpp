#include "AlertModel.h"
#include "globals.h"


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

void AlertModel::append(const QString& message, int status) {
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append({message, status});
    endInsertRows();
}

int AlertModel::rowCount(const QModelIndex &idx) const {
    if (idx.isValid()) {
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
        return m_data.at(idx.row()).m_message;

        case status:
            return m_data.at(idx.row()).m_status;

        default:
            return {};
    }
}

Qt::ItemFlags AlertModel::flags(const QModelIndex &idx) const {
    if (idx.isValid()) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

QHash<int, QByteArray> AlertModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[message] = "message";
    names[status] = "status";
    return names;
}

#include "moc_AlertModel.cpp"
