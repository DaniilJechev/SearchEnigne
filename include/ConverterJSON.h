#ifndef SEARCHENGINE_CONVERTERJSON_H
#define SEARCHENGINE_CONVERTERJSON_H
#endif //SEARCHENGINE_CONVERTERJSON_H

#include <fstream>
#include "nlohmann/json.hpp"

enum fileType{
    config,
    requests,
    answers
};

class ConverterJSON {
public:
    ~ConverterJSON();
    explicit ConverterJSON(std::string path = "");
    ConverterJSON(const ConverterJSON& other);
    ConverterJSON& operator= (const ConverterJSON& other);
    ConverterJSON(ConverterJSON&& other) noexcept;
    ConverterJSON& operator= (ConverterJSON&& other) noexcept;

    void setPath(const std::string &path);
    void setData(const nlohmann::json &mData);
    std::string getPath() const;
    const nlohmann::json &getData() const;

    void read();
    void write();

private:
    int currentFile = -1;
    std::string m_path;
    std::ifstream m_reader;
    std::ofstream m_writer;
    nlohmann::json m_data;
};