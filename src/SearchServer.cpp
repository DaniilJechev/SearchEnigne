#include "SearchServer.h"
#include "InvertedIndex.h"

#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

bool RelativeIndex::operator==(const RelativeIndex &other) const {
    return (m_docId == other.m_docId && m_rank == other.m_rank);
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queriesInput) {
    std::vector<std::vector<RelativeIndex>> result;
    for (const auto &query: queriesInput) {
        std::string word;
        std::stringstream stream(query);
        std::vector<RelativeIndex> docRelativeIdx;
        while (stream >> word) {
            for (const auto &it: m_freqDict.GetWordCount(word)) {
                SearchServer::addIndex(docRelativeIdx, it);
            }
        }
        std::sort(docRelativeIdx.begin(), docRelativeIdx.end(),
                  [](const RelativeIndex &first, const RelativeIndex &second) {
                      if (first.m_rank == second.m_rank) {
                          return (first.m_docId < second.m_docId);
                      }
                      return (first.m_rank > second.m_rank);
                  });
        convertAbsToRelative(docRelativeIdx);
        result.push_back(std::move(docRelativeIdx));
    }
    return result;
}

void SearchServer::addIndex(std::vector<RelativeIndex> &docRelativeIdx, const Entry &newIdx) {
    for (auto &it: docRelativeIdx) {
        if (it.m_docId == newIdx.m_docId) {
            it.m_rank += static_cast<float>(newIdx.m_count);
            return;
        }
    }
    docRelativeIdx.emplace_back(newIdx.m_docId, static_cast<float>(newIdx.m_count));
}

void SearchServer::convertAbsToRelative(std::vector<RelativeIndex> &docRelativeIdx) { //array must be sorted
    if (docRelativeIdx.empty()) return;
    float maxIdx = docRelativeIdx[0].m_rank;
    for (auto &it: docRelativeIdx) {
        it.m_rank /= maxIdx;
    }
}

