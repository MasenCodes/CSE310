#include <string>
#include "data_structures.h"

void parse_line(const std::string& line, int* a, int* b) {
    /*
     * returns [val before space, val after space]
     */
    // break down the string to get the respective values
    std::string val = "0";
    for(char c: line) {
        if(c == ' ') { // values are separated by space
            *a = std::stoi(val);
            val = "0";
        }
        else if(c != '\r' and c != '\n') { // ignore newlines
            val += c;
        }
    }
    *b = std::stoi(val);
}

vertex** create_adjacency_matrix(int n) {
    // create memory
    auto** matrix = new vertex*[n];
    for(int ii=0; ii<n; ii++) {
        matrix[ii] = new vertex[n];

        // initialize to 0
        for(int jj=0; jj<n; jj++) {
            matrix[ii][jj].val = 0;
            matrix[ii][jj].degree = 0;
        }
    }
    return matrix;
}