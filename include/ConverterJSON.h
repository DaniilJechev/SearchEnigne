#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <QObject>
#include <QList>
#include <QString>

#include "SearchServer.h"

namespace fs = std::filesystem;

class ConverterJSON : public QObject {
    Q_OBJECT

private:
    explicit ConverterJSON(QObject* parent = nullptr): QObject(parent){};
    static ConverterJSON* converterJson;

public:
    ConverterJSON(ConverterJSON& other) = delete;
    void operator= (const ConverterJSON& other) = delete;
    static ConverterJSON* getInstance();

    static std::vector<std::string> getTextDocuments(const fs::path& jsonDir,
                                                     const fs::path& resourcesDir);
    static int getResponsesLimit(const fs::path& jsonDir);
    static std::vector<std::string> getRequests(const fs::path& jsonDir);
    static std::vector<std::string> getPaths(const fs::path& jsonDir);
    static void putAnswers(const std::vector<std::vector<RelativeIndex>> &relativeIndexes,
                           const fs::path &jsonDir);
    static std::string getRunMode(const fs::path& jsonDir);

    Q_INVOKABLE static void writeToJson (const QList<QString>& data, int listModelType);

private:
    static std::string getTextFromFile(const fs::path& toFile);
    static std::vector<std::string> getTextsFromDir(const fs::path& dir, bool checkSubdirs);
    static bool isStarTerminated(const fs::path& dir);
    static bool isTxtOrDirectory(const fs::path& path);
    static bool pathGuard(fs::path& path, const fs::path &resourcesDir);
};