#include "SearchHandler.h"
#include "InvertedIndex.h"
#include "globals.h"
#include "ConverterJSON.h"
#include "SearchServer.h"
#include "AlertData.h"


void SearchHandler::search() {
    AlertData::appendAlert("Search started");
    InvertedIndex idx;
    idx.UpdateDocumentBase(ConverterJSON::getTextDocuments(global::jsonDir,
                                                               global::resourcesDir));
    SearchServer server(idx);
    auto queries = ConverterJSON::getRequests(global::jsonDir);
    auto answers = server.search(queries,
                                 ConverterJSON::getResponsesLimit(global::jsonDir));
    ConverterJSON::putAnswers(answers, global::jsonDir, queries);
    AlertData::appendAlert("Search completed");
}
