#ifndef OASIS_STATS_H
#define OASIS_STATS_H

#include "table.cpp"

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

    explicit Stats(Table<T>& table) : table(table) {}

    [[nodiscard]] auto mean(size_t col) const;

    [[nodiscard]] auto median(size_t col) const;

    [[nodiscard]] auto sum(size_t col) const;

    [[nodiscard]] auto count(size_t col) const;

    [[nodiscard]] auto max(size_t col) const;

    [[nodiscard]] auto min(size_t col) const;

    [[nodiscard]] auto range(size_t col) const;

    [[nodiscard]] auto variance(size_t col) const;

    [[nodiscard]] auto stddev(size_t col) const;

    [[nodiscard]] std::vector<T> mode(size_t col) const;

    [[nodiscard]] auto skew(size_t col) const;

    [[nodiscard]] auto kurtosis(size_t col) const;

    [[nodiscard]] auto z_score(size_t col, T observed) const;

    [[nodiscard]] auto iqr(size_t col) const;

    [[nodiscard]] auto coefficient_variation(size_t col) const;

    [[nodiscard]] auto lower_limit(size_t col) const;

    [[nodiscard]] auto upper_limit(size_t col) const;

    [[nodiscard]] auto lower_quartile(size_t col) const;

    [[nodiscard]] auto upper_quartile(size_t col) const;

    [[nodiscard]] std::pair<double, double> confidence_interval_mean(size_t col, double confidence_level) const;

    [[nodiscard]] std::pair<double, double> confidence_interval_proportion(size_t col, double confidence_level) const;

    [[nodiscard]] double z_test(size_t col, double population_mean) const;

    [[nodiscard]] double chi_square_test_independence(const std::vector<size_t>& row_groups, const std::vector<size_t>& col_groups) const;

    [[nodiscard]] double chi_square_goodness_of_fit() const;

    [[nodiscard]] double correlationCoefficient() const;

    void summary(size_t col) const;

private:
    Table<T>& table;
    [[nodiscard]] std::vector<T> getColumnData(size_t col) const;

};

} // namespace OASIS


#endif 
