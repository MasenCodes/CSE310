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
        while(ii>=0 and s[jj][arr_len-1] > key[arr_len-1]) {
            s[jj+1] = s[jj];
            jj -= 1;
        }
        s[jj+1] = key;
    }
}
/*
void insertionSort(string s[]) {
    int arr_len = s[0].size(); // assumes that the array was constructed by shifting string of len n, n times
    for(string* outer_str_ptr = &s[0]; outer_str_ptr <= &s[arr_len-1]; outer_str_ptr++) {
        string key = *outer_str_ptr;
        string* inner_str_ptr = outer_str_ptr - arr_len;
        // build case if char is == key, sort based on next letter
        while(outer_str_ptr>=&s[0] and (*outer_str_ptr)[arr_len-1] > key[arr_len-1]) {
            *(inner_str_ptr + arr_len) = *inner_str_ptr;
            inner_str_ptr--;
        }
        *(inner_str_ptr + arr_len) = key;
    }
}
*/
int main() {
    string input;
    getline(cin, input);

    string input_arr[input.size()];
    input_arr[0] = input;


    for(int ii=1; ii<input.size(); ii++){
        input_arr[ii] = shift(input_arr[ii - 1]);
    }
    insertionSort(input_arr);
    for(string* arr_start = &input_arr[0]; arr_start <= &input_arr[input.size() - 1]; arr_start++){
        cout << *arr_start << endl;
    }
    return 0;
}

