#include "data_structures.h"

int min(int a, int b) {
    if(a < b) {
        return a;
    }
    return b;
}

void FLOYD_WARSHALL(vertex** matrix, int size) {
    // modifies the weight matrix in place
    for(int kk=0; kk<size; kk++) {  // intermediate
        for(int ii=0; ii<size; ii++) {  // sources
            for(int jj=0; jj<size; jj++) {  // destinations
                if(ii != jj) {  // we never use the diagonal values
                    matrix[ii][jj].val = min(matrix[ii][jj].val, matrix[ii][kk].val + matrix[kk][jj].val);
                }
                else { // change from 'infinity' to 0 to match output
                    matrix[ii][jj].val = 0;
                }
            }
        }
    }
}

vertex* get_degrees(vertex** matrix, int size) {
    // this stores the respective number of the vertex in val and degree in degree
    auto* result = new vertex[size];
    for(int ii=0; ii<size; ii++) {
        result[ii].val = ii;
        result[ii].degree = 0;
        for(int jj=0; jj<size; jj++) {
            result[ii].degree += matrix[ii][jj].degree;
        }
    }
    return result;
}
