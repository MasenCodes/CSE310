#include <iostream>
#include <string>

using namespace std;

string shift(string s) {
    char ref = s[int(s.size()) - 1];
    for(int ii=int(s.size()-1); 0<ii; ii--){
        s.at(ii) = s.at(ii-1);
    }
    s.at(0) = ref;
    return s;
}

void insertionSort(char** s, int n) {
    for(int ii=1; ii<n; ii++) {
        char* temp = s[ii];
        int jj = ii - 1;
        // maybe just sum up index [:-2] and see which is bigger
        while(jj>=0 and s[jj][n-1] > temp[n-1]) {
            if(s[jj][n-1] == temp[n-1]) {
                int n2 = n - 2;
                while(jj > 0 and n2>=0) {
                    if(s[jj][n2] == temp[n2]) {
                        n--;
                    }
                    else if(s[jj][n2] > temp[n2]) {
                        s[jj+1] = s[jj];
                        jj -= 1;
                        s[jj+1] = temp;
                        break;
                    }
                    else {
                        jj -= 1;
                        s[jj+1] = temp;
                        break;
                    }
                }
            }
            else {
                s[jj+1] = s[jj];
                jj -= 1;
            }
        }
        s[jj+1] = temp;
    }
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if (string(argv[1]) == "insertion") {
            string input;
            while (getline(cin, input)) {
                int size = int(input.size());

                char **ptr_lst = new char*[size];
                for(int ii=0; ii<size; ii++) {
                    ptr_lst[ii] = new char[size];
                    for(int jj=0; jj<size; jj++) {
                        ptr_lst[ii][jj] = input.at(jj);
                    }
                    input = shift(input);
                }

                insertionSort(ptr_lst, size);

                for(int ii=0; ii<size; ii++) {
                    for (int jj = 0; jj < size; jj++) {
                        cout << ptr_lst[ii][jj];
                    }
                    cout << endl;
                }

                for(int ii=0; ii<size; ii++) {
                    delete[] ptr_lst[ii];
                }
                delete[] ptr_lst;
            }
        }
        else if (string(argv[1]) == "mergesort") {
            // come back after milestone
        }
    }

    return 0;
}



