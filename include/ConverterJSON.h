#ifndef SEARCHENGINE_CONVERTERJSON_H
#define SEARCHENGINE_CONVERTERJSON_H
#endif //SEARCHENGINE_CONVERTERJSON_H

#include <vector>
#include <string>

class ConverterJSON {
public:
    ConverterJSON() = default;

    static std::vector<std::string> getTextDocuments();
    static int getResponsesLimit();
    static std::vector<std::string> getRequests();
    static void putAnswers(std::vector<std::vector<std::pair<int, float>>>); // implement later
};