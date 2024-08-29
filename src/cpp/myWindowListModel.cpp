#include "myWindowListModel.h"

#include "ConverterJSON.h"
#include "globals.h"

bool MyWindowListModel::setData(const QModelIndex &idx, const QVariant &value, int role) {
    if (idx.isValid() && role == message && m_data[idx.row()] != value.toString()) {
        m_data[idx.row()] = value.toString();
        emit dataChanged(idx, idx, QList<int>() << role);
        return true;
    }
    return false;
}

int MyWindowListModel::rowCount(const QModelIndex &idx) const {
    if (!idx.isValid()) {
        return static_cast<int>(m_data.size());
    }
    return 0;
}


QVariant MyWindowListModel::data(const QModelIndex& idx, int role) const{
    if (!idx.isValid() || idx.row() >= m_data.size()) {
        return {};
    }

    if (role == message) {
        return m_data.at(idx.row());
    }

    return {};
}

Qt::ItemFlags MyWindowListModel::flags(const QModelIndex &idx) const {
    if (idx.isValid()) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

QHash<int, QByteArray> MyWindowListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names [message] = "message";
    return names;
}

void MyWindowListModel::appendMessage(const QString &message)
{
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append(message);
    endInsertRows();
}

void MyWindowListModel::remove(qsizetype idxStart, qsizetype countToDelete)
{
    beginRemoveRows(QModelIndex(), idxStart, idxStart + countToDelete - 1);
    m_data.remove(idxStart, countToDelete);
    endRemoveRows();
}

void MyWindowListModel::fillData(int listModelType) {
    std::vector<std::string> data;
    switch(listModelType){
        case ListModelType::Queries:
            data = ConverterJSON::getRequests(global::jsonDir);
            if (data.size() == 0) break;
            beginInsertRows(QModelIndex(), 0, data.size() - 1);
            for (const auto &path : data){
                m_data.append(QString::fromStdString(path));
            }
            endInsertRows();
            break;

        case ListModelType::Paths:
            data = ConverterJSON::getPaths(global::jsonDir);
            if (data.size() == 0) break;
            beginInsertRows(QModelIndex(), 0, data.size() - 1);
            for (const auto &request : data){
                m_data.append(QString::fromStdString(request));
            }
            endInsertRows();
            break;

        default:
            break;
    }
}

QList<QString> MyWindowListModel::getAllData() {
    return m_data;
}
