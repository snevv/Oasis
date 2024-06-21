#include "table.hpp"
#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stdexcept>

namespace Oasis {

template <typename T>
class Table;

template <typename T>
class TableInitializer {
public:
    TableInitializer(Table<T>* table) : table(table) {}

    void populate(const std::vector<std::vector<T>>& data) {
        if (table) {
            table->setData(data);
        }
    }

private:
    Table<T>* table;
};

template <typename T>
class Table {
public:
    virtual ~Table() = default;

    [[nodiscard]] virtual auto Copy() const -> std::unique_ptr<Table> = 0;

    void setData(const std::vector<std::vector<T>>& data) {
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

    T get(size_t col, size_t row) const {
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

    size_t getRowCount(size_t col) const {
        if (col >= col_sizes.size()) {
            throw std::out_of_range("Column index out of range");
        }
        return col_sizes[col];
    }

private:
    std::vector<T> values; 

};

} // namespace Oasis


