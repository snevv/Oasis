#define CATCH_CONFIG_MAIN
#include "table.cpp"
#include "stats.cpp"
#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

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

    REQUIRE(stats.median(0) == 3);
}

TEST_CASE("Median (normal / scrambled / odd)", "[Stats]") {
    std::vector<std::vector<int>> data = { {3, 1, 2, 5, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.median(0) == 3);
}

TEST_CASE("Median (normal / scrambled / even)", "[Stats]") {
    std::vector<std::vector<int>> data = { {3, 1, 2, 5, 6, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.median(0) == 3.5);
}

TEST_CASE("Sum (normal)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.sum(0) == 10);
}

TEST_CASE("Sum (single)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.sum(0) == 1);
}

TEST_CASE("Sum (empty)", "[Stats]") {
    std::vector<std::vector<int>> data = { {} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.sum(0) == 0);
}

TEST_CASE("Count (normal)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.count(0) == 5);
}

TEST_CASE("Count (empty)", "[Stats]") {
    std::vector<std::vector<int>> data = { {} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.count(0) == 0);
}

TEST_CASE("Max (normal)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.max(0) == 5);
}

TEST_CASE("Max (duplicates)", "[Stats]") {
    std::vector<std::vector<int>> data = { {3, 1, 2, 5, 4, 5, 5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.max(0) == 5);
}

TEST_CASE("Max (empty)", "[Stats]") {
    std::vector<std::vector<int>> data = { {} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.max(0) == NULL);
}

TEST_CASE("Min (normal)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.min(0) == 1);
}

TEST_CASE("Min (duplicates)", "[Stats]") {
    std::vector<std::vector<int>> data = { {3, 1, 2, 5, 4, 5, 1, 1} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.min(0) == 1);
}

TEST_CASE("Min (empty)", "[Stats]") {
    std::vector<std::vector<int>> data = { {} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.min(0) == NULL);
}

TEST_CASE("Range (normal)", "[Stats]") {
    std::vector<std::vector<int>> data = { {3, 1, 2, 5, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.range(0) == 4);
}

TEST_CASE("Range (duplicates)", "[Stats]") {
    std::vector<std::vector<int>> data = { {3, 1, 2, 5, 4, 5, 5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.range(0) == 4);
}

TEST_CASE("Range (single)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.range(0) == 0);
}

TEST_CASE("Range (empty)", "[Stats]") {
    std::vector<std::vector<int>> data = { {} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.range(0) == NULL);
}

TEST_CASE("Variance (simple)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.variance(0) == 2.5);
}

TEST_CASE("Variance (single)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.variance(0) == 0);
}

TEST_CASE("Variance (repeated values)", "[Stats]") {
    std::vector<std::vector<int>> data = { {7, 7, 7, 7, 7} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE_THAT(stats.variance(0), Catch::Matchers::WithinAbs(2.5, 0.01));
}

TEST_CASE("Variance (floats)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1.1, 2.2, 3.3, 4.4, 5.5} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.variance(0), Catch::Matchers::WithinAbs(2.97, 0.01));
    
}

TEST_CASE("Variance (mixed)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 2.5, 3, 4.5, 5} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.variance(0), Catch::Matchers::WithinAbs(2.75, 0.01));
}

TEST_CASE("Variance (mixed)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 2.5, 3, 4.5, 5} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.variance(0), Catch::Matchers::WithinAbs(2.75, 0.01));
}

TEST_CASE("Standard Deviation (empty)", "[Stats]") {
    std::vector<std::vector<double>> data = { {} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE(stats.stddev(0) == NULL);
}

TEST_CASE("Standard Deviation (repeated values)", "[Stats]") {
    std::vector<std::vector<int>> data = { {7, 7, 7, 7, 7} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE_THAT(stats.stddev(0), Catch::Matchers::WithinAbs(0.0, 0.01));
}

TEST_CASE("Standard Deviation (floats)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1.1, 2.2, 3.3, 4.4, 5.5} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.stddev(0), Catch::Matchers::WithinAbs(1.72, 0.01));
}

TEST_CASE("Standard Deviation (mixed)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 2.5, 3, 4.5, 5} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.stddev(0), Catch::Matchers::WithinAbs(1.66, 0.01));
}

TEST_CASE("Skew (empty)", "[Stats]") {
    std::vector<std::vector<double>> data = { {} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE(stats.skew(0) == NULL);
}

TEST_CASE("Skew (all equal values)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1.0, 1.0, 1.0} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.skew(0), Catch::Matchers::WithinAbs(0.0, 0.001));
}

TEST_CASE("Skew (symmetric)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1.0, 2.0, 3.0, 4.0, 5.0} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.skew(0), Catch::Matchers::WithinAbs(0.0, 0.01));
}

TEST_CASE("Skew (skew right)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 1, 2, 2, 2, 3} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.skew(0), Catch::Matchers::WithinAbs(0.3126, 0.01));
}

TEST_CASE("Skew (skew left)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 2, 2, 2, 3, 3} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.skew(0), Catch::Matchers::WithinAbs(-0.3126, 0.01));
}

// TEST_CASE("Skew (floats)", "[Stats]") {
//     std::vector<std::vector<double>> data = { {1, 2, 2, 2, 3, 3} };

//     Oasis::Table<double> table;
//     table.setData(data);
//     Oasis::Stats<double> stats(table);

//     REQUIRE_THAT(stats.skew(0), Catch::Matchers::WithinAbs(-0.3126, 0.01));
// }

// TEST_CASE("Skew (mixed)", "[Stats]") {
//     std::vector<std::vector<double>> data = { {1, 2, 2, 2, 3, 3} };

//     Oasis::Table<double> table;
//     table.setData(data);
//     Oasis::Stats<double> stats(table);

//     REQUIRE_THAT(stats.skew(0), Catch::Matchers::WithinAbs(-0.3126, 0.01));
// }