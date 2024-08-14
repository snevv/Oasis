#include "stats.hpp"
#include <iostream>
#include <numeric>
#include <cmath>
#include <unordered_map>

namespace Oasis {

    template <typename T>
    auto Stats<T>::mean(size_t col) const {
        auto data = getColumnData(col);
        T sum = std::accumulate(data.begin(), data.end(), T(0));
        return sum / data.size();
    }

    template <typename T>
    auto Stats<T>::median(size_t col) const {
        auto data = getColumnData(col);
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        if (n % 2 == 0) {
            return (data[n / 2 - 1] + data[n / 2]) / 2.0;
        } else {
            return data[n / 2];
        }
    }

    template <typename T>
    auto Stats<T>::sum(size_t col) const {
        auto data = getColumnData(col);
        return std::accumulate(data.begin(), data.end(), T(0));
    }

    template <typename T>
    auto Stats<T>::count(size_t col) const {
        return table.getRowCount(col);
    }

    template <typename T>
    auto Stats<T>::max(size_t col) const {
        auto data = getColumnData(col);
        if (data.empty()) {
            throw std::runtime_error("Column is empty");
        }
        return *std::max_element(data.begin(), data.end());
    }

    template <typename T>
    auto Stats<T>::min(size_t col) const {
        auto data = getColumnData(col);
        if (data.empty()) {
            throw std::runtime_error("Column is empty");
        }
        return *std::min_element(data.begin(), data.end());
    }

    template <typename T>
    auto Stats<T>::range(size_t col) const {
        return max(col) - min(col);
    }

    template <typename T>
    auto Stats<T>::variance(size_t col) const {
        T mean_value = mean(col);
        auto data = getColumnData(col);
        if (data.empty()) {
            throw std::runtime_error("Column is empty");
        }
        T var = std::accumulate(data.begin(), data.end(), T(0), [mean_value](T sum, T value) {
            return sum + (value - mean_value) * (value - mean_value);
        });
        return var / data.size();
    }

    template <typename T>
    auto Stats<T>::stddev(size_t col) const {
        return std::sqrt(variance(col));
    }

    template <typename T>
    std::vector<T> Stats<T>::mode(size_t col) const {
        auto data = getColumnData(col);
        if (data.empty()) {
            return {};
        }

        std::unordered_map<T, int> frequency;
        for (const auto &value : data) {
            ++frequency[value];
        }

        int maxCount = 0;
        for (const auto &pair : frequency) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
            }
        }

        std::vector<T> modes;
        for (const auto &pair : frequency) {
            if (pair.second == maxCount) {
                modes.push_back(pair.first);
            }
        }

        return modes;
    }

    template <typename T>
    auto Stats<T>::skew(size_t col) const {
        T mean_value = mean(col);
        T stddev_value = stddev(col);
        auto data = getColumnData(col);
        if (data.empty()) {
            throw std::runtime_error("Column is empty");
        }
        T skewness = std::accumulate(data.begin(), data.end(), T(0), [mean_value, stddev_value](T sum, T value) {
            return sum + std::pow((value - mean_value) / stddev_value, 3);
        });
        return skewness / data.size();
    }

    template <typename T>
    auto Stats<T>::kurtosis(size_t col) const {
        auto data = getColumnData(col);
        if (data.empty()) {
            throw std::runtime_error("Column is empty");
        }

        T mean_value = mean(col);
        T stddev_value = stddev(col);
        size_t N = data.size();

        T kurt = std::accumulate(data.begin(), data.end(), T(0), [mean_value, stddev_value](T sum, T value) {
            return sum + std::pow((value - mean_value) / stddev_value, 4);
        });

        T normalization_factor = N * (N + 1) / ((N - 1) * (N - 2) * (N - 3));
        T excess_kurtosis = normalization_factor * kurt - 3 * std::pow(N - 1, 2) / ((N - 2) * (N - 3));

        return excess_kurtosis;
    }

    template <typename T>
    auto Stats<T>::z_score(size_t col, T observed) const {
        T mean_value = mean(col);
        T stddev_value = stddev(col);
        if (stddev_value == 0) {
            throw std::runtime_error("Standard deviation is zero, cannot calculate z-score.");
        }
        return (observed - mean_value) / stddev_value;
    }

    template <typename T>
    auto Stats<T>::coefficient_variation(size_t col) const {
        return (stddev(col) / mean(col)) * 100;
    }

    template <typename T>
    auto Stats<T>::lower_quartile(size_t col) const {
        auto data = getColumnData(col);
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        size_t mid_index = n / 2;
        std::vector<T> lower_half(data.begin(), data.begin() + mid_index);

        if (lower_half.size() % 2 == 0) {
            return (lower_half[lower_half.size() / 2 - 1] + lower_half[lower_half.size() / 2]) / 2.0;
        } else {
            return lower_half[lower_half.size() / 2];
        }
    }

    template <typename T>
    auto Stats<T>::upper_quartile(size_t col) const {
        auto data = getColumnData(col);
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        size_t mid_index = (n % 2 == 0) ? n / 2 : (n / 2 + 1);
        std::vector<T> upper_half(data.begin() + mid_index, data.end());

        if (upper_half.size() % 2 == 0) {
            return (upper_half[upper_half.size() / 2 - 1] + upper_half[upper_half.size() / 2]) / 2.0;
        } else {
            return upper_half[upper_half.size() / 2];
        }
    }

    template <typename T>
    auto Stats<T>::iqr(size_t col) const {
        return upper_quartile(col) - lower_quartile(col);
    }

    // Q1 - 1.5 * IQR
    template <typename T>
    auto Stats<T>::lower_limit(size_t col) const {
        T q1 = lower_quartile(col);
        T iqr_value = iqr(col);
        return q1 - 1.5 * iqr_value;
    }

    // Q3 + 1.5 * IQR
    template <typename T>
    auto Stats<T>::upper_limit(size_t col) const {
        T q3 = upper_quartile(col);
        T iqr_value = iqr(col);
        return q3 + 1.5 * iqr_value;
    }

    template <typename T>
    std::vector<T> Stats<T>::getColumnData(size_t col) const {
        size_t rowCount = table.getColSize(col);
        std::vector<T> data(rowCount);
        for (size_t row = 0; row < rowCount; ++row) {
            data[row] = table.get(col, row);
        }
        return data;
    }

    // FIND WAY TO IMPORT ACTUAL NORMAL DISTRIBUTION INTO LIBRARY!!!!
    // TEMP CONFIDENCE_INTERVAL_MEAN IMPLEMENTATION

    template <typename T>
    std::pair<double, double> Stats<T>::confidence_interval_mean(size_t col, double confidence_level) const {
        auto data = getColumnData(col);
        size_t n = data.size();
        if (n < 2) {
            throw std::runtime_error("Not enough data to compute confidence interval.");
        }

        T mean_value = mean(col);
        T stddev_value = stddev(col);

        double z_score = 1.96;  // 95% confidence level
        if (confidence_level == 0.99) {
            z_score = 2.576; // 99% confidence level
        } else if (confidence_level == 0.90) {
            z_score = 1.645; // 90% confidence level
        }

        double margin_of_error = z_score * (stddev_value / std::sqrt(n));
        return {mean_value - margin_of_error, mean_value + margin_of_error};
    }

    /* IMPLEMENT FUNCTIONALITY THAT ALLOWS CLIENT TO WHICH COLUMNS 
     * FROM INPUT WILL BE USED FOR (L1, L2, L3, etc.) like IN TI-84 CALCULATOR
     */ 

    /* TODO: decide how to handle errors, currently throwing runtime errors
     */ 

    template <typename T>
    double Stats<T>::chi_square_goodness_of_fit() const {
        auto data = getColumnData(0); 
        auto frequencies = getColumnData(1); // observed frequencies
        
        size_t n = frequencies.size();
        if (n == 0) {
            throw std::runtime_error("No data available for chi-square test.");
        }

        double total_observed = std::accumulate(frequencies.begin(), frequencies.end(), 0.0);

        std::vector<double> expected_frequencies(n, total_observed / n);

        // ???? what to do w this error
        if (expected_frequencies.size() != frequencies.size()) {
            throw std::invalid_argument("Expected and observed frequency counts do not match.");
        }

        double chi_square_statistic = 0.0;

        for (size_t i = 0; i < n; ++i) {
            double observed = static_cast<double>(frequencies[i]);
            double expected = expected_frequencies[i];

            if (expected == 0) {
                throw std::invalid_argument("Expected frequency cannot be zero.");
            }

            chi_square_statistic += std::pow(observed - expected, 2) / expected;
        }

        return chi_square_statistic;
    }

    template <typename T>
    double Stats<T>::chi_square_test_independence(const std::vector<size_t>& row_groups, const std::vector<size_t>& col_groups) const {
        size_t num_rows = row_groups.size();
        size_t num_cols = col_groups.size();
        
        // throw runtime error or return null?
        if (num_rows == 0 || num_cols == 0) {
            throw std::runtime_error("No data available for chi-square test");
        }

        std::vector<std::vector<double>> observed(num_rows, std::vector<double>(num_cols, 0));
        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = 0; j < num_cols; ++j) {
                observed[i][j] = table.get(row_groups[i], col_groups[j]);
            }
        }

        std::vector<double> row_totals(num_rows, 0);
        std::vector<double> col_totals(num_cols, 0);
        double total = 0;

        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = 0; j < num_cols; ++j) {
                row_totals[i] += observed[i][j];
                col_totals[j] += observed[i][j];
                total += observed[i][j];
            }
        }

        std::vector<std::vector<double>> expected(num_rows, std::vector<double>(num_cols, 0));
        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = 0; j < num_cols; ++j) {
                expected[i][j] = (row_totals[i] * col_totals[j]) / total;
            }
        }

        double chi_square_statistic = 0;
        for (size_t i = 0; i < num_rows; ++i) {
            for (size_t j = 0; j < num_cols; ++j) {
                if (expected[i][j] != 0) {
                    chi_square_statistic += std::pow(observed[i][j] - expected[i][j], 2) / expected[i][j];
                }
            }
        }

        return chi_square_statistic;
    }

    template <typename T>
    double Stats<T>::correlationCoefficient() const {

        std::vector<T> x = getCol(xCol);
        std::vector<T> y = getCol(yCol);

        if (x.size() != y.size()) {
            throw std::logic_error("columns must have the same number of rows");
        }

        size_t n = x.size();
        if (n == 0) {
            throw std::logic_error("columns must not be empty");
        }

        double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
        double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
        double sum_x2 = std::accumulate(x.begin(), x.end(), 0.0, [](double sum, T xi) { return sum + xi * xi; });
        double sum_y2 = std::accumulate(y.begin(), y.end(), 0.0, [](double sum, T yi) { return sum + yi * yi; });
        double sum_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);

        double numerator = n * sum_xy - sum_x * sum_y;
        double denominator = std::sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));

        if (denominator == 0) {
            throw std::runtime_error("zero denominator");
        }

        return numerator / denominator;
    }
    
    template <typename T>
    void Stats<T>::summary(size_t col) const {
        std::cout << "Summary for column " << col << ":\n";
        std::cout << "Count: " << count(col) << "\n";
        std::cout << "Mean: " << mean(col) << "\n";
        std::cout << "Median: " << median(col) << "\n";
        std::cout << "Sum: " << sum(col) << "\n";
        std::cout << "Max: " << max(col) << "\n";
        std::cout << "Min: " << min(col) << "\n";
        std::cout << "Range: " << range(col) << "\n";
        std::cout << "Variance: " << variance(col) << "\n";
        std::cout << "Standard Deviation: " << stddev(col) << "\n";
        std::cout << "Skewness: " << skew(col) << "\n";
        std::cout << "Kurtosis: " << kurtosis(col) << "\n";
        std::cout << "Lower Quartile: " << lower_quartile(col) << "\n";
        std::cout << "Upper Quartile: " << upper_quartile(col) << "\n";
        std::cout << "Interquartile Range (IQR): " << iqr(col) << "\n";
        std::cout << "Coefficient of Variation: " << coefficient_variation(col) << "%\n";
        // std::cout << "Z-Scores: ";

        auto modes = mode(col);
        std::cout << "Mode: ";
        for (const auto& value : modes) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

} // namespace Oasis


template class Oasis::Stats<int>;
template class Oasis::Stats<double>;
template class Oasis::Stats<float>;
