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

}

int main() {
    string input;
    getline(cin, input);

    string input_arr[input.size()];
    input_arr[0] = input;

    for(int ii=1; ii<input.size(); ii++){
        input_arr[ii] = shift(input_arr[ii - 1]);
    }

    return 0;
}

