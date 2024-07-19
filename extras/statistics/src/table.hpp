#ifndef OASIS_TABLE_HPP
#define OASIS_TABLE_HPP

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
    TableInitializer(std::vector<std::vector<T>>& data) : data(data), table(new Table<T>) {} 

    void populate();

    virtual ~TableInitializer() = default;

private:
    std::vector<std::vector<T>> data;
    std::unique_ptr<Table<T>> table;
};

template <typename T>
class Table {
public:
    virtual ~Table() = default;

    // [[nodiscard]] virtual auto Copy() const -> std::unique_ptr<Table> = 0;

    void setData(const std::vector<std::vector<T>>& data);

    [[nodiscard]] size_t getColSize(size_t col) const;

    [[nodiscard]] T get(size_t col, size_t row) const;

    size_t numCols() const { return col_sizes.size(); }

    [[nodiscard]] std::vector<T> getColumnData(size_t col) const;
    
private:
    std::vector<T> values;
    std::vector<T> col_sizes; 
};

} // namespace Oasis

#endif // OASIS_TABLE_HPP
