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

    // make the adjacency matrix and the adjacency list (need to initialize)
    vertex** adj_matrix = create_adjacency_matrix(vertices);
    adj** list = new adj*[vertices];

    // now get all the connections in the rest of the file
    string connection;
    while(getline(cin, connection)) {
        // read in each line
        int a;  // value before space
        int b;  // value after space
        parse_line(connection, &a, &b);

        // add data to matrix
        add_connection(adj_matrix, a, b);

        // add data to stack
        add_adjacency(list, a, b);
    }

    // after reading data into adjacency matrix, print the ones with odd degrees
    print_odds(adj_matrix, vertices);

    // find shortest paths and print result
    FLOYD_WARSHALL(adj_matrix, vertices);
    print_matrix(adj_matrix, vertices);
    //print_full_matrix(adj_matrix, vertices);

    // get odd degree vertices to be used as virtual edges (returned in sorted order)
    weight_list* virtual_edges = get_virtual_edges(adj_matrix, vertices);
    //print_list(virtual_edges);

    // now get the euler circuit
    print_circuit(adj_matrix, vertices, list, virtual_edges);
    //print_adj_list(list, vertices);
}