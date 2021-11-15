#include <iostream>
#include <cstdlib>
#include <string>
#include "algorithms.cpp"
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

        // map the connection in the adjacency matrix
        adj_matrix[a - 1][b - 1].val = 1;
        adj_matrix[a - 1][b - 1].degree += 1;
        adj_matrix[b - 1][a - 1].val = 1;
        adj_matrix[b - 1][a - 1].degree += 1;
    }

    for(int ii=0; ii<vertices; ii++) {
        for(int jj=0; jj<vertices; jj++) {
            cout << adj_matrix[ii][jj].degree << " ";
        }
        cout << "\n";
    }
}