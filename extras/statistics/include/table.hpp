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
    TableInitializer(Table<T>* table) : table(table) {}

    void populate(const std::vector<std::vector<T>>& data);

    virtual ~TableInitializer() = default;

private:
    Table<T>* table;
};

template <typename T>
class Table {
public:
    virtual ~Table() = default;

    [[nodiscard]] virtual auto Copy() const -> std::unique_ptr<Table> = 0;

    void setData(const std::vector<std::vector<T>>& data);

    size_t getRowCount(size_t col) const;

protected:
    std::vector<T> values; 
    std::vector<size_t> col_sizes;

};

} // namespace Oasis

#endif // OASIS_TABLE_HPP
