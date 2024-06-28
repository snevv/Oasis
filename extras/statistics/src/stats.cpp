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
