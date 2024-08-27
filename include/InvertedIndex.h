#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "ConverterJSON.h"

class InvertedIndex {

private:
    void getTermFrequencyFromText(const DocumentInfo& docInfo, int textId);

public:
    InvertedIndex() = default;
    InvertedIndex(const InvertedIndex&) = default;
    InvertedIndex& operator=(const InvertedIndex&) = default;

    void UpdateDocumentBase(const std::vector<DocumentInfo>& input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::map<std::string, std::vector<Entry>> m_freqDict;
};