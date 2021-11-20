#include <string>
#include "algorithms.cpp"

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

void add_connection(vertex** matrix, int a, int b) {
    // map the connection in the adjacency matrix
    matrix[a - 1][b - 1].val = 1;
    matrix[b - 1][a - 1].val = 1;

    // increment vertex (just in case we have double connections)
    matrix[a - 1][b - 1].degree += 1;
    matrix[b - 1][a - 1].degree += 1;
}

vertex** create_adjacency_matrix(int size) {
    // create memory
    auto** matrix = new vertex*[size];
    for(int ii=0; ii<size; ii++) {
        matrix[ii] = new vertex[size];

        // initialize to 0
        for(int jj=0; jj<size; jj++) {
            matrix[ii][jj].val = size * 2; // this is 'infinity'
            matrix[ii][jj].degree = 0;
        }
    }
    return matrix;
}

void print_matrix(vertex** matrix, int size) {
    /*
     * just fix to resize odds array or only print when the val is odd
     */
    vertex* odds = get_degrees(matrix, size);

    // print the title
    std::cout << "Results of Floyd-Warshall on O:\n";

    // print out upper row with all odd values
    std::cout << "     | ";  // top-most divider bar
    int odd_size = 0;  // size for the rest of the print
    for(int ii=0; ii<size; ii++) {
        if(odds[ii].degree % 2 == 0) {
            odd_size += 1;
            if(odds[ii].val > 99) {
                std::cout << " " << odds[ii].val;  // 1 space total
            }
            else if(odds[ii].val > 9) {
                std::cout << "  " << odds[ii].val;  // 2 spaces total
            }
            else {
                std::cout << "   " << odds[ii].val;  // 3 spaces total
            }
        }
    }
    std::cout << "\n";

    // print out upper table divider
    std::cout << "--- -+-";
    for(int ii=0; ii<odd_size; ii++) {
        std::cout << " ---";
    }
    std::cout << "\n";

    // print each row of table
    for(int ii=0; ii<odd_size; ii++) {
        bool first = true;
        for(int jj=0; jj<odd_size; jj++) {
            if(first) {  // only print left index of vertical once for each ii
                if(odds[ii].val > 99) {
                    std::cout << odds[ii].val << " | ";  // 1 left space
                }
                else if(odds[ii].val > 9) {
                    std::cout << " " << odds[ii].val << " | ";  // 2 left spaces
                }
                else {
                    std::cout << "  " << odds[ii].val << " | ";  // 3 left spaces
                }
            }
            first = false;

            // print the value to align with given formatting
            if(odds[ii].val > 99) {
                std::cout << " " << matrix[odds[ii].val][odds[jj].val].val;  // 1 space total
            }
            else if(odds[ii].val > 9) {
                std::cout << "  " << matrix[odds[ii].val][odds[jj].val].val;  // 2 spaces total
            }
            else {
                std::cout << "   " << matrix[odds[ii].val][odds[jj].val].val;  // 3 spaces total
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_odds(vertex** matrix, int size) {
    // calls get_degrees and prints out the odd vertex degrees in the format required:
    std::cout << "The odd-degree vertices in G: O = { ";

    // get the vertex data
    vertex* odds = get_degrees(matrix, size);

    // find all odds
    for(int ii=0; ii<size; ii++) {
        if(odds[ii].degree % 2 == 1) {
            std::cout << odds[ii].val + 1 << " ";  // add one for 0 index
        }
    }

    // print closing block
    std::cout << "}\n\n";

    // free memory
    delete[] odds;
}