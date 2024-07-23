#define CATCH_CONFIG_MAIN
#include "table.cpp"
#include "stats.cpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("Mean (normal)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.mean(0) == 2);
}

TEST_CASE("Mean (empty)", "[Stats]") {
    std::vector<std::vector<int>> data = { {} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.mean(0) == 0);
}

TEST_CASE("Mean (multiple cols)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3}, {4, 5, 6} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.mean(1) == 5);
}

TEST_CASE("Median (normal / unscrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.mean(0) == 3);
}

TEST_CASE("Median (normal / scrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {3, 1, 2, 5, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.mean(0) == 3);
}