#include "Oasis/table.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>

namespace Oasis {

template <typename T>
class Stats {
public:
    explicit Stats(const Table<T>& table) : table(table) {}

    auto mean(size_t col) const {
        auto data = getColumnData(col);
        T sum = std::accumulate(data.begin(), data.end(), T(0));
        return sum / data.size();
    }

    auto median(size_t col) const {
        auto data = getColumnData(col);
        std::sort(data.begin(), data.end());
        size_t n = data.size();
        if (n % 2 == 0) {
            return (data[n / 2 - 1] + data[n / 2]) / T(2);
        } else {
            return data[n / 2];
        }
    }

    auto sum(size_t col) const {
        auto data = getColumnData(col);
        return std::accumulate(data.begin(), data.end(), T(0));
    }

    auto count(size_t col) const {
        return table.getRowCount(col);
    }

    auto max(size_t col) const {
        auto data = getColumnData(col);
        return *std::max_element(data.begin(), data.end());
    }

    auto min(size_t col) const {
        auto data = getColumnData(col);
        return *std::min_element(data.begin(), data.end());
    }

    auto range(size_t col) const {
        return max(col) - min(col);
    }

    auto variance(size_t col) const {
        T mean_value = mean(col);
        auto data = getColumnData(col);
        T var = std::accumulate(data.begin(), data.end(), T(0), [mean_value](T sum, T value) {
            return sum + (value - mean_value) * (value - mean_value);
        });
        return var / data.size();
    }

    auto stddev(size_t col) const {
        return std::sqrt(variance(col));
    }

    // std::map<T, size_t> mode(size_t col) const {
        
    // }

    auto skew(size_t col) const {
        T mean_value = mean(col);
        T stddev_value = stddev(col);
        auto data = getColumnData(col);
        T skewness = std::accumulate(data.begin(), data.end(), T(0), [mean_value, stddev_value](T sum, T value) {
            return sum + std::pow((value - mean_value) / stddev_value, 3);
        });
        return skewness / data.size();
    }

    auto kurtosis(size_t col) const {
        // ...
    }

    // FOR TESTING
    auto summary(size_t col) const {
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
        auto modes = mode(col);
        std::cout << "Mode: ";
        for (const auto& [value, count] : modes) {
            std::cout << value << " (count: " << count << "), ";
        }
        std::cout << "\n";
    }

private:
    const Table<T>& table;

    std::vector<T> getColumnData(size_t col) const {
        size_t rowCount = table.getRowCount(col);
        std::vector<T> data(rowCount);
        for (size_t row = 0; row < rowCount; ++row) {
            data[row] = table.get(col, row);
        }
        return data;
    }
};

} // namespace Oasis

#endif 
