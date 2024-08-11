#include "InvertedIndex.h"

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <thread>
#include <mutex>

std::mutex m_freqDict_access;

Entry::Entry(size_t docId, size_t count) : m_docId(docId), m_count(count) {}

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& docs) {
    int textId = 0;
    std::vector<std::thread> threads;
    for (const auto& doc : docs) {
        threads.emplace_back(&InvertedIndex::getTermFrequencyFromText, this, doc, textId);
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

void InvertedIndex::getTermFrequencyFromText(const std::string& text, int textId) {
    std::string word;
    std::stringstream textStream(text);
    std::map<std::string, size_t> localTermFreq;

    while (textStream >> word) {
        localTermFreq[word]++;
    }

    std::lock_guard<std::mutex> lock(m_freqDict_access);
    for (const auto& it : localTermFreq) {
        m_freqDict[it.first].emplace_back(textId, it.second);
    }
}
