#pragma once

#include "InvertedIndex.h"

class SearchServer {
private:
    static void addIndex(std::vector<RelativeIndex> &docRelativeIdx, const Entry &newIdx);
    static void convertAbsToRelative(std::vector<RelativeIndex> &docRelativeIdx); //array must be sorted

public:
    explicit SearchServer(InvertedIndex &freqDict) : m_freqDict(freqDict) {};
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>
                                                   &queries_input, size_t maxResponses = 5);

private:
    InvertedIndex &m_freqDict;
};