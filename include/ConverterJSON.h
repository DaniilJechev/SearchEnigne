#pragma once

#include <utility>
#include <vector>
#include <string>
#include <filesystem>

#include <QObject>
#include <QList>
#include <QString>

#include "globals.h"

struct DocumentInfo { // for reading txt filex
    std::string m_docText, m_pathToDoc;

    DocumentInfo(const std::string &docText, const std::string &pathToDoc = "") :
            m_docText(docText), m_pathToDoc(pathToDoc){}
};

struct Entry { // for invertedIndex dictionary
    size_t m_docId, m_count;
    std::string m_pathToFile;

    Entry(size_t docId, size_t count, std::string pathToFile = "")
            : m_docId(docId), m_count(count), m_pathToFile(std::move(pathToFile)) {};

    bool operator==(const Entry &other) const;
};

struct RelativeIndex { // for answers to queries
    size_t m_docId{};
    float m_rank{};
    std::string m_pathToFile;

    bool operator==(const RelativeIndex &other) const;
    RelativeIndex() = default;
    RelativeIndex(size_t docId, float rank, const std::string& pathToFile = "") :
            m_docId(docId), m_rank(rank), m_pathToFile(pathToFile) {};
};

namespace fs = std::filesystem;

class ConverterJSON : public QObject {
    Q_OBJECT

private:
    explicit ConverterJSON(QObject *parent = nullptr) : QObject(parent) {};
    static ConverterJSON *converterJson;

public:
    ConverterJSON(ConverterJSON &other) = delete;
    void operator=(const ConverterJSON &other) = delete;
    static ConverterJSON *getInstance();

    static std::vector<DocumentInfo> getTextDocuments(const fs::path &jsonDir = global::jsonDir,
                                                      const fs::path &resourcesDir = global::resourcesDir);
    static std::vector<std::string> getRequests(const fs::path &jsonDir = global::jsonDir);
    static std::vector<std::string> getPaths(const fs::path &jsonDir = global::jsonDir);
    static void putAnswers(const std::vector<std::vector<RelativeIndex>> &relativeIndexes,
                           const fs::path &jsonDir = global::jsonDir, const std::vector<std::string>& queries = {});
    static std::string getRunMode(const fs::path &jsonDir = global::jsonDir);

    Q_INVOKABLE static int getResponsesLimit(const fs::path &jsonDir = global::jsonDir);
    Q_INVOKABLE static void setResponsesLimit(int maxResponses, const fs::path &jsonDir = global::jsonDir);
    Q_INVOKABLE static void writeToJson(const QList<QString> &data, int listModelType);
    Q_INVOKABLE static QString getAnswers();

private:
    static std::string createRequestName(int requestId);
    static std::string getTextFromFile(const fs::path& toFile);
    static std::vector<DocumentInfo> getTextsFromDir(const fs::path& dir, bool checkSubdirs);
    static bool isStarTerminated(const fs::path& dir);
    static bool isTxtOrDirectory(const fs::path& path);
    static bool pathGuard(fs::path& path, const fs::path &resourcesDir = global::resourcesDir);
};
