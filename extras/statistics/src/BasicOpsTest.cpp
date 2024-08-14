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

TEST_CASE("Upper Quartile (normal / unscrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7, 8} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.upper_quartile(0) == 6);
}

TEST_CASE("Upper Quartile (scrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {7, 1, 3, 8, 5, 2, 6, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.upper_quartile(0) == 6);
}

TEST_CASE("Upper Quartile (odd number of elements)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.upper_quartile(0) == 6);
}

TEST_CASE("Lower Quartile (normal / unscrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7, 8} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.lower_quartile(0) == 3);
}

TEST_CASE("Lower Quartile (scrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {7, 1, 3, 8, 5, 2, 6, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.lower_quartile(0) == 3);
}

TEST_CASE("Lower Quartile (odd number of elements)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.lower_quartile(0) == 2.5);
}

TEST_CASE("Interquartile Range (normal / unscrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7, 8} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.iqr(0) == 3);
}

TEST_CASE("Interquartile Range (scrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {7, 1, 3, 8, 5, 2, 6, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.iqr(0) == 3);
}

TEST_CASE("Interquartile Range (odd number of elements)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.iqr(0) == 3.5);
}

TEST_CASE("Kurtosis (normal / unscrambled)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 2, 3, 4, 5, 6, 7, 8} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.kurtosis(0), Catch::Matchers::WithinAbs(-1.2, 0.01));
}

TEST_CASE("Kurtosis (scrambled)", "[Stats]") {
    std::vector<std::vector<double>> data = { {7, 1, 3, 8, 5, 2, 6, 4} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.kurtosis(0), Catch::Matchers::WithinAbs(-1.2, 0.01)); 
}

TEST_CASE("Kurtosis (odd number of elements)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 2, 3, 4, 5, 6, 7} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.kurtosis(0), Catch::Matchers::WithinAbs(-1.23, 0.01)); 
}

TEST_CASE("Kurtosis (empty dataset)", "[Stats]") {
    std::vector<std::vector<int>> data = {{}};

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(std::isnan(stats.kurtosis(0)));
}


TEST_CASE("Kurtosis (small dataset with negative numbers)", "[Stats]") {
    std::vector<std::vector<int>> data = {{-5, -10, -15, -20}};

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    double calculated_kurtosis = stats.kurtosis(0);
    double expected_kurtosis = 1.5;  

    REQUIRE_THAT(calculated_kurtosis, Catch::Matchers::WithinAbs(expected_kurtosis, 0.01)); 
}


TEST_CASE("Z-Score (normal / unscrambled)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 2, 3, 4, 5, 6, 7, 8} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.z_score(0, 5.0), Catch::Matchers::WithinAbs(0.0, 0.01)); 
    REQUIRE_THAT(stats.z_score(0, 1.0), Catch::Matchers::WithinAbs(-1.5, 0.01)); 
}

TEST_CASE("Z-Score (scrambled)", "[Stats]") {
    std::vector<std::vector<double>> data = { {7, 1, 3, 8, 5, 2, 6, 4} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.z_score(0, 5.0), Catch::Matchers::WithinAbs(0.0, 0.01));
    REQUIRE_THAT(stats.z_score(0, 1.0), Catch::Matchers::WithinAbs(-1.5, 0.01)); 
}

TEST_CASE("Z-Score (odd number of elements)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1, 2, 3, 4, 5, 6, 7} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.z_score(0, 5.0), Catch::Matchers::WithinAbs(0.0, 0.01)); 
    REQUIRE_THAT(stats.z_score(0, 1.0), Catch::Matchers::WithinAbs(-1.5, 0.01)); 
}

TEST_CASE("Upper Quartile (normal / unscrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7, 8} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.upper_quartile(0) == 6);
}

TEST_CASE("Upper Quartile (scrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {7, 1, 3, 8, 5, 2, 6, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.upper_quartile(0) == 6);
}

TEST_CASE("Upper Quartile (odd number of elements)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.upper_quartile(0) == 6);
}

TEST_CASE("Lower Quartile (normal / unscrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7, 8} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.lower_quartile(0) == 3);
}

TEST_CASE("Lower Quartile (scrambled)", "[Stats]") {
    std::vector<std::vector<int>> data = { {7, 1, 3, 8, 5, 2, 6, 4} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.lower_quartile(0) == 3);
}

TEST_CASE("Lower Quartile (odd number of elements)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5, 6, 7} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.lower_quartile(0) == 2);
}

TEST_CASE("Coefficient of Variation (normal)", "[Stats]") {
    std::vector<std::vector<int>> data = { {1, 2, 3, 4, 5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE_THAT(stats.coefficient_variation(0), Catch::Matchers::WithinAbs(0.527, 0.01));
}

TEST_CASE("Coefficient of Variation (floats)", "[Stats]") {
    std::vector<std::vector<double>> data = { {1.1, 2.2, 3.3, 4.4, 5.5} };

    Oasis::Table<double> table;
    table.setData(data);
    Oasis::Stats<double> stats(table);

    REQUIRE_THAT(stats.coefficient_variation(0), Catch::Matchers::WithinAbs(0.539, 0.01));
}

TEST_CASE("Coefficient of Variation (repeated values)", "[Stats]") {
    std::vector<std::vector<int>> data = { {7, 7, 7, 7, 7} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE_THAT(stats.coefficient_variation(0), Catch::Matchers::WithinAbs(0.0, 0.01));
}

TEST_CASE("Coefficient of Variation (single value)", "[Stats]") {
    std::vector<std::vector<int>> data = { {5} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE_THAT(stats.coefficient_variation(0), Catch::Matchers::WithinAbs(0.0, 0.01));
}

TEST_CASE("Coefficient of Variation (empty)", "[Stats]") {
    std::vector<std::vector<int>> data = { {} };

    Oasis::Table<int> table;
    table.setData(data);
    Oasis::Stats<int> stats(table);

    REQUIRE(stats.coefficient_variation(0) == NULL);
}
