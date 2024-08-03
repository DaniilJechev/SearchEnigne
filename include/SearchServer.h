#pragma once

#include <vector>
#include <string>

#include "InvertedIndex.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const;
};

class SearchServer {
public:
    explicit SearchServer(InvertedIndex& idx) : m_index(idx){};
    std::vector<std::vector<RelativeIndex>> search(const
                std::vector<std::string>& queries_input);
private:
    InvertedIndex& m_index;
};
