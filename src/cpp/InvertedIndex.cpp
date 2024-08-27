#include "InvertedIndex.h"

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <thread>
#include <mutex>

std::mutex m_freqDict_access;

void InvertedIndex::UpdateDocumentBase(const std::vector<DocumentInfo>& docsInfo) {
    int textId = 0;
    std::vector<std::thread> threads;
    for (const auto& docInfo : docsInfo) {
        threads.emplace_back(&InvertedIndex::getTermFrequencyFromText, this, docInfo, textId);
        textId++;
    }

    for (auto& thread : threads) {
        if (thread.joinable()) thread.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::vector<Entry> freq;
    if (m_freqDict.count(word)) {
        freq = m_freqDict[word];
    }
    return freq;
}

void InvertedIndex::getTermFrequencyFromText(const DocumentInfo& docInfo, int textId) {
    std::string word;
    std::stringstream textStream(docInfo.m_docText);
    std::map<std::string, size_t> localTermFreq;

    while (textStream >> word) {
        localTermFreq[word]++;
    }

    std::lock_guard<std::mutex> lock(m_freqDict_access);
    for (const auto& it : localTermFreq) {
        m_freqDict[it.first].emplace_back(textId, it.second, docInfo.m_pathToDoc);
    }
}