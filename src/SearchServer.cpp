#include "SearchServer.h"
#include <vector>
#include <string>

bool RelativeIndex::operator==(const RelativeIndex &other) const {
    return (doc_id == other.doc_id && rank == other.rank);
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queriesInput) {

}
