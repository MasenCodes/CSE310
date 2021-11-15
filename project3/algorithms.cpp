int min(int a, int b) {
    if(a < b) {
        return a;
    }
    return b;
}

void* FLOYD_WARSHALL(int** matrix, int size) {
    // modifies the weight matrix in place
    for(int ii=0; ii<size; ii++) {  // intermediate
        for(int jj=0; jj<size; jj++) {  // sources
            for(int kk=0; kk<size; kk++) {  // destinations
                matrix[ii][jj] = min(matrix[ii][jj], matrix[ii][kk] + matrix[kk][jj]);
            }
        }
    }
}