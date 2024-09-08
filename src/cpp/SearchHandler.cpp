#include "SearchHandler.h"

#include <QTime>
#include <string>
#include <QDebug>

#include "InvertedIndex.h"
#include "globals.h"
#include "ConverterJSON.h"
#include "SearchServer.h"
#include "AlertData.h"

std::string countDuration(const QTime &start, const QTime &end) {
    if (end < start) return "";
    QTime duration = QTime::fromMSecsSinceStartOfDay(end.msecsSinceStartOfDay() - start.msecsSinceStartOfDay());
    std::string resultDuration = "Duration (ms): " + duration.toString("zzz").toStdString();
    return resultDuration;
}

void SearchHandler::search() {
    QTime start = QTime::currentTime();
    AlertData::appendAlert(start.toString("hh:mm:ss:  ").toStdString() + "Search started" );

    InvertedIndex idx;
    idx.UpdateDocumentBase(ConverterJSON::getTextDocuments(global::jsonDir,
                                                               global::resourcesDir));
    SearchServer server(idx);
    auto queries = ConverterJSON::getRequests(global::jsonDir);
    auto answers = server.search(queries,
                                 ConverterJSON::getResponsesLimit(global::jsonDir));
    ConverterJSON::putAnswers(answers, global::jsonDir, queries);
    QTime end = QTime::currentTime();

    AlertData::appendAlert(end.toString("hh:mm:ss:  ").toStdString() + "Search completed ");
    AlertData::appendAlert(countDuration(start, end));
    AlertData::appendAlert(std::string(30, '-'));
}
