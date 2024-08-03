#pragma once

#include <vector>
#include <string>
#include <map>

struct Entry {
    size_t m_docId, m_count;
    Entry (size_t docId, size_t count);

    bool operator== (const Entry &other) const {
        return (m_count == other.m_count
            && m_docId == other.m_docId);
    }
};

class InvertedIndex {
private:
    void getTermFrequencyFromText (const std::string& text, int textId);

public:
    InvertedIndex() = default;
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::map<std::string, std::vector<Entry>> m_freqDict;
};