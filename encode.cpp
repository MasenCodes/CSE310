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

void insertionSort(string s[]) {
    int arr_len = s[0].size(); // assumes that the array was constructed by shifting string of len n, n times
    for(int ii=1; ii<arr_len; ii++) {
        string key = s[ii];
        int jj = ii - 1;
        while(ii>=0 and s[ii][arr_len-1] > key[arr_len-1]) {
            s[jj+1] = s[jj];
            jj -= 1;
        }
        s[jj+1] = key;
    }
}

int main() {
    string input;
    getline(cin, input);

    string input_arr[input.size()];
    input_arr[0] = input;

    for(int ii=1; ii<input.size(); ii++){
        input_arr[ii] = shift(input_arr[ii - 1]);
    }
    insertionSort(input_arr);

    return 0;
}

