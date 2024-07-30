#include "ConverterJson.h"
#include <utility>

ConverterJSON::~ConverterJSON() {
    m_writer.close();
    m_reader.close();
}

ConverterJSON::ConverterJSON(std::string path): m_path(path){}

ConverterJSON::ConverterJSON(const ConverterJSON &other) :
        ConverterJSON(other.getPath()) {
    m_data = other.m_data;
}

ConverterJSON &ConverterJSON::operator=(const ConverterJSON &other) {
    if (this != &other) {
        setPath(other.getPath());
        m_data = other.m_data;
    }
    return *this;
}

ConverterJSON::ConverterJSON(ConverterJSON &&other) noexcept{
    m_path = std::move(other.m_path);
    m_data = std::move(other.m_data);
}

ConverterJSON &ConverterJSON::operator=(ConverterJSON &&other) noexcept {
    if (this != &other) {
        m_path = std::move(other.m_path);
        m_data = std::move(other.m_data);
    }
    return *this;
}


void ConverterJSON::setPath(const std::string &path) {
    m_path = path;
}

void ConverterJSON::setData(const nlohmann::json &mData) {
    m_data = mData;
}

std::string ConverterJSON::getPath() const {
    return m_path;
}

const nlohmann::json &ConverterJSON::getData() const {
    return m_data;
}


void ConverterJSON::read() {
    m_reader.open(m_path);
    m_reader >> m_data;
    m_reader.close();
}

void ConverterJSON::write() {
    m_writer.open(m_path);
    m_writer << m_data.dump(4);
    m_writer.close();
}