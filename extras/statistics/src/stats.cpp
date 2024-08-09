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

    // Implementations for `lower_limit` and `upper_limit` if needed...

    template <typename T>
    std::vector<T> Stats<T>::getColumnData(size_t col) const {
        size_t rowCount = table.getColSize(col);
        std::vector<T> data(rowCount);
        for (size_t row = 0; row < rowCount; ++row) {
            data[row] = table.get(col, row);
        }
        return data;
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


// explicit instantiation for required types
template class Oasis::Stats<int>;
template class Oasis::Stats<double>;
template class Oasis::Stats<float>;
