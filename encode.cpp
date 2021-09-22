#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string shift(string s) {
    char ref = s[int(s.size()) - 1];
    for(int ii=int(s.size()-1); 0<ii; ii--){
        s.at(ii) = s.at(ii-1);
    }
    s.at(0) = ref;
    return s;
}

bool smaller(char* a, char* b) {
    // returns if a < b
    if(a[0] == b[0]) {
        int ii = 1;
        while(a[ii] < b[ii]) {
            ii++;
        }
        return a[ii] < b[ii];
    }
    else return a[0] < b[0];
}

void merge(char** s, int l, int mid, int r) {
    // indexes
    int leftStart = l;
    int leftEnd = mid;
    int rightStart = mid+1;
    int rightEnd = r;

    // create new memory
    char** tempArray = new char*[(r-l) + 1];
    for(int ii=0; ii<((r-l) + 1); ii++) {
        tempArray[ii] = new char[strlen(s[0])];
    }

    // after determining equality, fill temporary memory
    int ii = l;
    while(leftStart <= leftEnd and rightStart <= rightEnd) {
        if(smaller(s[leftStart], s[rightStart])) {
            tempArray[ii] = s[leftStart];
            leftStart++;
        }
        else {
            tempArray[ii] = s[rightStart];
            rightStart++;
        }
        ii++;
    }

    // one will execute to finish the sort
    while(leftStart <= leftEnd) {
        tempArray[ii] = s[leftStart];
        leftStart++;
        ii++;
    }
    while(rightStart <= rightEnd) {
        tempArray[ii] = s[rightStart];
        rightStart++;
        ii++;
    }

    // copy temp memory back to original and delete it
    for(ii=l; ii<=r; ii++) {
        s[ii] = tempArray[ii];
        delete[] tempArray[ii-l];
    }
    delete[] tempArray;
}

void mergeSort(char** s, int l, int r) {
    if(l < r) {
        int mid = (l + r) / 2;
        mergeSort(s, l, mid);
        mergeSort(s, mid + 1, r);
        merge(s, l, mid, r);
    }
    else {
        return;
    }
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

                cout << count << " " << temp << endl;
                cout << endl;

                // free up memory
                for(int ii=0; ii<size; ii++) {
                    delete[] ptr_lst[ii];
                }
                delete[] ptr_lst;
            }
        }
        else if (string(argv[1]) == "mergesort") {
            // come back after milestone
            string input;
            while (getline(cin, input)) {
                // do not print out empty lines
                if (input.empty()) {
                    continue;
                }

                int size = int(input.size());

                // declare pointer and fill array
                char **ptr_lst = new char *[size];
                for (int ii = 0; ii < size; ii++) {
                    ptr_lst[ii] = new char[size];
                    for (int jj = 0; jj < size; jj++) {
                        ptr_lst[ii][jj] = input.at(jj);
                    }
                    input = shift(input);
                }

                // sort the array
                mergeSort(ptr_lst, 0, size-1);

                // print the index original string appears in sorted array
                bool found = true;
                for (int ii = 0; ii < size; ii++) {
                    found = true;
                    for (int jj = 0; jj < size; jj++) {
                        if (input.at(jj) != ptr_lst[ii][jj]) {
                            found = false;
                            break;
                        }

                    }
                    if (found) {
                        cout << ii << endl;
                        break;
                    }
                }

                // print the encoded message
                int count = 1;
                char temp = ptr_lst[0][0];
                for (int ii = 1; ii < size; ii++) {
                    if (ptr_lst[ii][0] == temp) {
                        count++;
                    } else {
                        cout << count << " " << temp << " ";
                        count = 1;
                        temp = ptr_lst[ii][0];
                    }
                }

                cout << count << " " << temp << endl;
                cout << endl;

                // free up memory
                for (int ii = 0; ii < size; ii++) {
                    delete[] ptr_lst[ii];
                }
                delete[] ptr_lst;
            }
        }
    }
    return 0;
}



