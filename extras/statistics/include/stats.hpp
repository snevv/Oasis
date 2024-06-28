#ifndef OASIS_STATS_H
#define OASIS_STATS_H

#include "Oasis/table.hpp"

#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>

namespace Oasis {

template <typename T>
class Stats {
public:
    virtual ~Stats() = default();

    explicit Stats(const Table<T>& table) : table(table) {}

    [[nodiscard]] auto mean(size_t col) const;

    [[nodiscard]] auto median(size_t col) const;

    [[nodiscard]] auto sum(size_t col) const;

    [[nodiscard]] auto count(size_t col) const;

    [[nodiscard]] auto max(size_t col) const;

    [[nodiscard]] auto min(size_t col) const;

    [[nodiscard]] auto range(size_t col) const;

    [[nodiscard]] auto variance(size_t col) const;

    [[nodiscard]] auto stddev(size_t col) const;

    // [[nodiscard]] std::map<T, size_t> mode(size_t col) const;

    [[nodiscard]] auto skew(size_t col) const;

    [[nodiscard]] auto kurtosis(size_t col) const;

    void summary(size_t col) const;

private:
    const Table<T>& table;
    [[nodiscard]] std::vector<T> getColumnData(size_t col) const;

};

} // namespace OASIS


#endif 
