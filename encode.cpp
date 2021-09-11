#include <iostream>
#include <string>

using namespace std;

string shift(string s) {
    char ref = s[s.size() - 1];
    for(int ii=s.size()-1; 0<ii; ii--){
        s[ii] = s[ii-1];
    }
    s[0] = ref;
    return s;
}

void insertionSort(char** s, int n) {
    for(int ii=1; ii<n; ii++) {
        char* temp = s[ii];
        int jj = ii - 1;
        while(ii>=0 and s[jj][n-1] > temp[n-1]) {
            s[jj+1] = s[jj];
            jj -= 1;
        }
        s[jj+1] = temp;
    }
}

int main() {
    string input;
    getline(cin, input);

    int size = input.size();

    char **ptr_lst = new char*[size];
    for(int ii=0; ii<size; ii++) {
        ptr_lst[ii] = new char[size];
        for(int jj=0; jj<size; jj++) {
            ptr_lst[ii][jj] = input[jj];
        }
        input = shift(input);
    }

    insertionSort(ptr_lst, size);

    for(int ii=0; ii<size; ii++) {
        for(int jj=0; jj<size; jj++) {
            cout << ptr_lst[ii][jj];
        }
        cout << endl;
    }

    return 0;
}



