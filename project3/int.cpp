#include <iostream>
#include <cstdlib>
#include <string>
#include "helper_functions.cpp"

using namespace std;


int main(int argc, char * argv[]) {
    // first step is to get the number of vertices and edges stores in first line
    string NxM;
    getline(cin, NxM);

    // get the sizes and assign to variables
    int vertices;
    int edges;
    parse_line(NxM, &vertices, &edges);

    // make the adjacency matrix
    vertex** adj_matrix = create_adjacency_matrix(vertices);

    // now get all the connections in the rest of the file
    string connection;
    while(getline(cin, connection)) {
        // read in each line
        int a;  // value before space
        int b;  // value after space
        parse_line(connection, &a, &b);

        // add data to matrix
        add_connection(adj_matrix, a, b);
    }

    // after reading data into adjacency matrix, print the ones with odd degrees
    print_odds(adj_matrix, vertices);

    FLOYD_WARSHALL(adj_matrix, vertices);
    print_matrix(adj_matrix, vertices);
}