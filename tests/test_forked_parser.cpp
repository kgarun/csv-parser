//
// Created by arun-8593 on 19/10/21.
//

#include "catch.hpp"
#include "csv.hpp"
#include "util.hpp"
#include <iostream>

using namespace csv;

TEST_CASE ("Test CSV with Space Delimiter") {
    CSVFormat format;
    format.delimiter ({ ' ' }).no_header ();
    CSVReader reader (GetAbsolutePath ("/tests/samples/space_separated.csv"), format);

    REQUIRE (format.get_delims ().size () == 1);
    REQUIRE (format.get_delims ().back () == ' ');

    std::vector<std::vector<std::string>> expected{ { "Ruturaj Gaikwad", "c Shivam Mavi, b Narine", "32" },
                                                    { "du Plessis", "c Venkatesh Iyer, b Shivam Mavi", "86" },
                                                    { "Uthappa", "lbw b Narine", "31" },
                                                    { "Moeen", "not out", "37" } };

    std::vector<std::vector<std::string>> actual;
    int row_index = 0;
    actual.resize (expected.size ());

    for (CSVRow &row : reader) {
        for (CSVField &field : row) {
            actual[row_index].emplace_back (field.get ());
        }
        ++row_index;
    }

    for (size_t row = 0; row < reader.n_rows (); ++row) {
        if (expected[row] != actual[row]) std::cout << row << '\n';
    }

    REQUIRE (expected == actual);
}

TEST_CASE ("Guess Space Delimiter") {
    CSVFormat format;
    format.no_header ().trim ({ '\t' });
    CSVReader reader (GetAbsolutePath ("/tests/samples/space_separated.csv"), format);

    REQUIRE (format.get_delims ().size () == 1);
    REQUIRE (format.get_delims ().back () == ' ');

    std::vector<std::vector<std::string>> expected{ { "Ruturaj Gaikwad", "c Shivam Mavi, b Narine", "32" },
                                                    { "du Plessis", "c Venkatesh Iyer, b Shivam Mavi", "86" },
                                                    { "Uthappa", "lbw b Narine", "31" },
                                                    { "Moeen", "not out", "37" } };

    std::vector<std::vector<std::string>> actual;
    int row_index = 0;
    actual.resize (expected.size ());

    for (CSVRow &row : reader) {
        for (CSVField &field : row) {
            actual[row_index].emplace_back (field.get ());
        }
        ++row_index;
    }

    for (size_t row = 0; row < reader.n_rows (); ++row) {
        if (expected[row] != actual[row]) std::cout << row << '\n';
    }

    REQUIRE (expected == actual);
}

TEST_CASE ("Test CSV with Multiple Delimiters") {
    CSVFormat format;
    format.delimiter ({ ',', ' ' }).no_header ().trim ({ '\t' }).quote ('\"');
    CSVReader reader (GetAbsolutePath ("/tests/samples/delimiter_separted_file.csv"), format);

    REQUIRE (format.get_delims ().size () == 2);
    REQUIRE (format.get_delims ().front () == ',');
    REQUIRE (format.get_delims ().back () == ' ');

    std::vector<std::vector<std::string>> expected{ { "1.2999", "an", "cd", "zoho@zohocorp.com", "3", R"("zoho" "on" " zoho ")" },
                                                    { "1", "1/2", "01/01/00", "this string\nspans to\nmultiple lines", "88", "7777000" },
                                                    { "", "", "", "", "" },
                                                    { "29u29", "", "\"", "some \"\nstring", "xx" } };

    std::vector<std::vector<std::string>> actual;
    int row_index = 0;
    actual.resize (expected.size ());

    for (CSVRow &row : reader) {
        for (CSVField &field : row) {
            actual[row_index].emplace_back (field.get ());
        }
        ++row_index;
    }

    for (size_t row = 0; row < reader.n_rows (); ++row) {
        if (expected[row] != actual[row]) std::cout << row << '\n';
    }

    REQUIRE (expected == actual);
}
