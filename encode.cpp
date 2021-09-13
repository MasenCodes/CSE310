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
    int nn = n;
    for(int ii=1; ii<nn; ii++) {
        char* temp = s[ii];
        int jj = ii - 1;

        while(jj>=0 and s[jj][nn-1] >= temp[nn-1]) {
            // if equal compare next character down
            if(s[jj][nn-1] == temp[nn-1]) {
                nn--;
                continue;
            }
            s[jj+1] = s[jj];
            jj -= 1;
            nn = n;
        }
        s[jj+1] = temp;
        nn = n;
    }
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if (string(argv[1]) == "insertion") {
            string input;
            while (getline(cin, input)) {
                // do not print out empty lines
                if(input.empty()) {
                    continue;
                }

                int size = int(input.size());

                // declare pointer and fill array
                char **ptr_lst = new char*[size];
                for(int ii=0; ii<size; ii++) {
                    ptr_lst[ii] = new char[size];
                    for(int jj=0; jj<size; jj++) {
                        ptr_lst[ii][jj] = input.at(jj);
                    }
                    input = shift(input);
                }

                // sort the array
                insertionSort(ptr_lst, size);

                // print the index original string appears in sorted array
                bool found = true;
                for(int ii=0; ii<size; ii++) {
                    found = true;
                    for(int jj=0; jj<size; jj++) {
                       if(input.at(jj) != ptr_lst[ii][jj]) {
                           found = false;
                           break;
                       }

                    }
                    if(found) {
                        cout << ii << endl;
                        break;
                    }
                }

                // print the encoded message
                int count = 1;
                char temp = ptr_lst[0][0];
                for(int ii=1; ii<size; ii++) {
                    if(ptr_lst[ii][0] == temp) {
                        count++;
                    }
                    else {
                        cout << count << " " << temp << " ";
                        count = 1;
                        temp = ptr_lst[ii][0];
                    }
                }
                if(count > 1) {
                    cout << count << " " << temp << " " << endl;
                }

                // print out new line
                cout << "\n" << endl;

                // free up memory
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



