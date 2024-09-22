#include "AlertData.h"

#include <iostream>
#include <mutex>

std::mutex appendMtx;
AlertData* AlertData::alertData = nullptr;

bool AlertData::isAlertModelExist() {
    return getInstance()->modelExists;
}

AlertItem &AlertData::operator[](size_t idx) {
    if (idx >= m_data.size()) throw std::out_of_range("Index out of range");
    return m_data[static_cast<qsizetype>(idx)];
}

size_t AlertData::size() {
    return m_data.size();
}

AlertData* AlertData::getInstance() {
    if (alertData == nullptr) {
        alertData = new AlertData();
    }
    return alertData;
}

void AlertData::raiseModelExists() {
    getInstance()->modelExists = true;
}

void AlertData::appendAlert(const std::string &message, int status) {
    auto alertData = AlertData::getInstance();
    std::lock_guard<std::mutex> guard(appendMtx);
    if (AlertData::isAlertModelExist()) {
        emit alertData->startAppend(alertData->m_data.size(), alertData->m_data.size(),
                         QModelIndex());
        alertData->m_data.append({QString::fromStdString(message), status});
        emit alertData->endAppend();
        return;
    }
    std::cerr << message << std::endl;
}

void AlertData::clear() {
    AlertData::getInstance()->m_data.clear();
}
