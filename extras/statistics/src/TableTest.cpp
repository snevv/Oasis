#define CATCH_CONFIG_MAIN
#include "table.cpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Table (empty)", "[Table]") {
    std::vector<std::vector<int>> data = { {},{} };

    Oasis::Table<int> table;
    table.setData(data);

    REQUIRE(table.numCols() == 2);

    REQUIRE(table.getColSize(0) == 0);
    REQUIRE(table.getColSize(1) == 0);
}

TEST_CASE("Table (symmetric)", "[Table]") {
    std::vector<std::vector<int>> data = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    Oasis::Table<int> table;
    table.setData(data);

    REQUIRE(table.numCols() == 3);

    REQUIRE(table.get(0, 0) == 1);
    REQUIRE(table.get(1, 0) == 2);
    REQUIRE(table.get(2, 0) == 3);

    REQUIRE(table.get(0, 1) == 4);
    REQUIRE(table.get(1, 1) == 5);
    REQUIRE(table.get(2, 1) == 6);

    REQUIRE(table.get(0, 2) == 7);
    REQUIRE(table.get(1, 2) == 8);
    REQUIRE(table.get(2, 2) == 9);
}

TEST_CASE("Table (asymmetric)", "[Table]") {
    std::vector<std::vector<int>> data = {
        {1, 2, 3},
        {4, 5, 6, 7},
        {8, 9}
    };

    Oasis::Table<int> table;
    table.setData(data);

    REQUIRE(table.numCols() == 3);

    REQUIRE(table.get(0, 0) == 1);
    REQUIRE(table.get(1, 0) == 2);
    REQUIRE(table.get(2, 0) == 3);

    REQUIRE(table.get(0, 1) == 4);
    REQUIRE(table.get(1, 1) == 5);
    REQUIRE(table.get(2, 1) == 6);
    REQUIRE(table.get(3, 1) == 7);

    REQUIRE(table.get(0, 2) == 8);
    REQUIRE(table.get(1, 2) == 9);
}


TEST_CASE("Table (kooky)", "[Table]") {
    std::vector<std::vector<int>> data = {
        {1, 2, 3},
        {},
        {},
        {4}
    };

    Oasis::Table<int> table;
    table.setData(data);

    REQUIRE(table.numCols() == 4);

    REQUIRE(table.getColSize(0) == 3);
    REQUIRE(table.get(0, 0) == 1);
    REQUIRE(table.get(1, 0) == 2);
    REQUIRE(table.get(2, 0) == 3);

    REQUIRE(table.getColSize(1) == 0);

    REQUIRE(table.getColSize(2) == 0);

    REQUIRE(table.getColSize(3) == 1);
    REQUIRE(table.get(3, 0) == 4);
}

TEST_CASE("ColSizes (symmetric)", "[Table]") {
    std::vector<std::vector<int>> data = {
        {1, 2},
        {4, 5},
        {7, 8}
    };

    Oasis::Table<int> table;
    table.setData(data);

    REQUIRE(table.numCols() == 3);

    REQUIRE(table.getColSize(0) == 2);
    REQUIRE(table.getColSize(1) == 2);
    REQUIRE(table.getColSize(2) == 2);
}

TEST_CASE("ColSizes (asymmetric)", "[Table]") {
    std::vector<std::vector<int>> data = {
        {1, 2, 3},
        {4, 5, 6, 7},
        {8, 9}
    };

    Oasis::Table<int> table;
    table.setData(data);

    REQUIRE(table.numCols() == 3);

    REQUIRE(table.getColSize(0) == 3);
    REQUIRE(table.getColSize(1) == 4);
    REQUIRE(table.getColSize(2) == 2);
}