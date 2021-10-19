//
// Created by arun-8593 on 19/10/21.
//

#include "csv.hpp"
#include <iostream>

using namespace csv;

int main () {
    CSVFormat format;
    format.delimiter ({ ',', ' ' }).no_header ().trim ({ '\t' });
    CSVReader reader ("/Users/arun-8593/CLionProjects/CSV/delimiter_separted_file.csv", format);

    for (auto c : reader.get_format ().get_delims ()) {
        std::cout << "ch:" << c << '\n';
    }

    for (CSVRow &row : reader) {
        for (CSVField &field : row) {
            std::cout << field.get_sv () << " | ";
        }
        std::cout << "\n-------------------------\n";
    }

    return 0;
}
