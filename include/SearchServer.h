#pragma once

#include "InvertedIndex.h"

struct RelativeIndex {
    size_t m_docId;
    float m_rank;

    bool operator==(const RelativeIndex &other) const;
    RelativeIndex() = default;
    RelativeIndex(size_t docId, float rank) :
            m_docId(docId), m_rank(rank) {};
};

class SearchServer {
private:
    static void addIndex(std::vector<RelativeIndex> &docRelativeIdx, const Entry &newIdx);
    static void convertAbsToRelative(std::vector<RelativeIndex> &docRelativeIdx); //array must be sorted

public:
    explicit SearchServer(InvertedIndex &freqDict) : m_freqDict(freqDict) {};
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input, size_t maxResponses = 5);

private:
    InvertedIndex &m_freqDict;
};