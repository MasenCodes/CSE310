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
    vertex* vertices = get_degrees(matrix, size);

    // print the title
    std::cout << "Results of Floyd-Warshall on O:\n";

    // print out upper row with all odd values
    std::cout << "     | ";  // top-most divider bar
    int odd_size = 0;  // size for the rest of the print
    for(int ii=0; ii<size; ii++) {
        if(vertices[ii].degree % 2 != 0) {
            odd_size += 1;
            if(vertices[ii].val + 1 > 99) {
                std::cout << " " << vertices[ii].val + 1;  // 1 space total
            }
            else if(vertices[ii].val + 1 > 9) {
                std::cout << "  " << vertices[ii].val + 1;  // 2 spaces total
            }
            else {
                std::cout << "   " << vertices[ii].val + 1;  // 3 spaces total
            }
        }
    }
    std::cout << "\n";

    // make array to hold only odd degree vertices
    auto* odds = new vertex[odd_size];
    int index = 0;
    for(int ii=0; ii<size; ii++) {
        if(vertices[ii].degree % 2 != 0) {
            odds[index] = vertices[ii];
            index++;
        }
    }

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
                if(odds[ii].val + 1 > 99) {
                    std::cout << odds[ii].val + 1 << "  | ";  // 0 left spaces
                }
                else if(odds[ii].val + 1 > 9) {
                    std::cout << " " << odds[ii].val + 1 << "  | ";  // 1 left space
                }
                else {
                    std::cout << "  " << odds[ii].val + 1 << "  | ";  // 2 left spaces
                }
                first = false;
            }

            // print the value to align with given formatting
            int path_len = matrix[odds[ii].val][odds[jj].val].val;  // index the matrix at given vertices
            if(path_len > 99) {
                std::cout << " " << path_len;  // 1 space total
            }
            else if(path_len > 9) {
                std::cout << "  " << path_len;  // 2 spaces total
            }
            else {
                std::cout << "   " << path_len;  // 3 spaces total
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // free memory
    delete[] vertices;
    delete[] odds;
}

void print_full_matrix(vertex** matrix, int size) {
    vertex* vertices = get_degrees(matrix, size);

    // print the title
    std::cout << "Results of Floyd-Warshall on O:\n";

    // print out upper row with all odd values
    std::cout << "     | ";  // top-most divider bar
    for(int ii=0; ii<size; ii++) {
        if(vertices[ii].val + 1 > 99) {
            std::cout << " " << vertices[ii].val + 1;  // 1 space total
        }
        else if(vertices[ii].val + 1> 9) {
            std::cout << "  " << vertices[ii].val + 1;  // 2 spaces total
        }
        else {
            std::cout << "   " << vertices[ii].val + 1;  // 3 spaces total
        }
    }
    std::cout << "\n";

    // print out upper table divider
    std::cout << "--- -+-";
    for(int ii=0; ii<size; ii++) {
        std::cout << " ---";
    }
    std::cout << "\n";

    // print each row of table
    for(int ii=0; ii<size; ii++) {
        bool first = true;
        for(int jj=0; jj<size; jj++) {
            if(first) {  // only print left index of vertical once for each ii
                if(vertices[ii].val + 1 > 99) {
                    std::cout << vertices[ii].val + 1 << "  | ";  // 0 left spaces
                }
                else if(vertices[ii].val + 1 > 9) {
                    std::cout << " " << vertices[ii].val + 1 << "  | ";  // 1 left space
                }
                else {
                    std::cout << "  " << vertices[ii].val + 1 << "  | ";  // 2 left spaces
                }
                first = false;
            }

            // print the value to align with given formatting
            int path_len = matrix[vertices[ii].val][vertices[jj].val].val;  // index the matrix at given vertices
            if(path_len > 99) {
                std::cout << " " << path_len;  // 1 space total
            }
            else if(path_len > 9) {
                std::cout << "  " << path_len;  // 2 spaces total
            }
            else {
                std::cout << "   " << path_len;  // 3 spaces total
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    // free memory
    delete[] vertices;
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

void print_list(weight_list* h) {
    weight_list* itr = h;
    int prev = -1;
    while(itr != nullptr) {
        if(itr->e.weight > prev) {
            if(prev != -1) {
                std::cout << "\n";
            }
            std::cout << "Edges of length " <<  itr->e.weight << ": ";
            prev = itr->e.weight;
        }
        std::cout << " (" << itr->e.u + 1 << "," << itr->e.v + 1 << ")";
        itr = itr->next;
    }
    std::cout << "\n";
}

void print_adj_list(adj** list, int size) {
    for(int ii=0; ii<size; ii++) {
        adj* itr = list[ii];
        std::cout << ii + 1 << ": ";
        while(itr != nullptr) {
            std::cout << itr->val + 1 << " ";
            itr = itr->next;
        }
        std::cout <<"\n";
    }
}
