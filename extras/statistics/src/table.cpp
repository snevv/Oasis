#include "table.hpp"
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>

namespace Oasis {

    template <typename T>
    void TableInitializer<T>::populate() {
        if (table) {
            table->setData(data);
        }
    }

    template <typename T>
    void Table<T>::setData(const std::vector<std::vector<T>>& data) {
        size_t total_size = 0;
        for (const auto& column : data) {
            total_size += column.size();
        }

        values.clear();
        values.reserve(total_size);

        for (const auto& column : data) {
            values.insert(values.end(), column.begin(), column.end());
        }

        col_sizes.clear();
        for (const auto& column : data) {
            col_sizes.push_back(column.size());
        }
    }

    template <typename T>
    T Table<T>::get(size_t col, size_t row) const {
        if (col >= col_sizes.size()) {
            throw std::out_of_range("Column index out of range");
        }

        size_t start_index = 0;
        for (size_t i = 0; i < col; ++i) {
            start_index += col_sizes[i];
        }

        if (row >= col_sizes[col]) {
            throw std::out_of_range("Row index out of range");
        }

        return values[start_index + row];
    }

    template <typename T>
    size_t Table<T>::getColSize(size_t col) const {
        if (col >= col_sizes.size()) {
            throw std::out_of_range("Column index out of range");
        }
        return col_sizes[col];
    }

    template <typename T>
    std::vector<T> Table<T>::getColumnData(size_t col) const {
        if (col >= width) {
            throw std::out_of_range("Column index out of range");
        }

        size_t offset = 0;
        for (size_t i = 0; i < col; ++i) {
            offset += col_sizes[i];
        }

        return std::vector<T>(values.begin() + offset, values.begin() + offset + col_sizes[col]);
    }
    
} // namespace Oasis


