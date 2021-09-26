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

bool smaller(char* a, char* b, int size) {
    // returns if a < b
    if(a[size - 1] == b[size - 1]) {
        int ii = size - 2;
        while(a[ii] == b[ii] and ii >= 0) {
            ii--;
        }
        return a[ii] < b[ii];
    }
    else return a[size - 1] < b[size - 1];
}

void merge(char** s, int l, int mid, int r, int n) {
    // sizes and index
    int leftSize = (mid-l) + 1;
    int rightSize = r-mid;
    int leftIndex = 0;
    int rightIndex = 0;

    // create new memory
    char** leftArray = new char*[leftSize];
    char** rightArray = new char*[rightSize];
    for(int ii=0; ii<leftSize; ii++) {
        leftArray[ii] = new char[n];
    }
    for(int ii=0; ii<rightSize; ii++) {
        rightArray[ii] = new char[n];
    }

    // fill arrays
    for(int ii=l; ii<mid + 1; ii++) {
        for(int jj=0; jj<n; jj++) {
            leftArray[leftIndex][jj] = s[ii][jj];
        }
        leftIndex++;
    }
    for(int ii=mid + 1; ii<r + 1; ii++) {
        for(int jj=0; jj<n; jj++) {
            rightArray[rightIndex][jj] = s[ii][jj];
        }
        rightIndex++;
    }

    // reset and create indexes and begin comparison
    leftIndex = 0, rightIndex = 0;
    int leftStart = l;
    int rightStart = mid + 1;
    int start = l;

    while(leftStart <= mid and rightStart <= r) {
        if(smaller(leftArray[leftIndex], rightArray[rightIndex], n)) {
            for(int ii=0; ii<n; ii++) {
                s[start][ii] = leftArray[leftIndex][ii];
            }
            leftStart++;
            leftIndex++;
        }
        else {
            for(int ii=0; ii<n; ii++) {
                s[start][ii] = rightArray[rightIndex][ii];
            }
            rightStart++;
            rightIndex++;
        }
        start++;
    }

    // one will execute to finish the sort
    while(leftStart <= mid) {
        for(int ii=0; ii<n; ii++) {
            s[start][ii] = leftArray[leftIndex][ii];
        }
        leftStart++;
        leftIndex++;
        start++;
    }
    while(rightStart <= r) {
        for(int ii=0; ii<n; ii++) {
            s[start][ii] = rightArray[rightIndex][ii];
        }
        rightStart++;
        rightIndex++;
        start++;
    }

    // free memory
    leftSize = (mid-l) + 1;
    rightSize = r-mid;
    for(int ii=0; ii<leftSize; ii++) {
        delete[] leftArray[ii];
    }
    for(int ii=0; ii<rightSize; ii++) {
        delete[] rightArray[ii];
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(char** s, int l, int r, int n) {
    if(l < r) {
        int mid = (l + r) / 2;
        mergeSort(s, l, mid, n);
        mergeSort(s, mid + 1, r, n);
        merge(s, l, mid, r, n);
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
        string charsOnly;
        int charCount = 0;
        string input;
        bool goneOnce = false;
        while (getline(cin, input)) {
            // handling new lines / end of file
            if (input.empty()) { // maybe add == 13 case here
                cout << endl;
                continue;
            }
            if (goneOnce) {
                cout << endl;
            }

            // delete newline char
            int size = int(input.length());
            if (input[size - 1] == 13) {
                input.erase(size - 1);
                size -= 1;
            }

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
            if (string(argv[1]) == "insertion") {
                insertionSort(ptr_lst, size);
            } else {
                mergeSort(ptr_lst, 0, size - 1, size);
            }

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
            cout << count << " " << temp;

            // free up memory
            for (int ii = 0; ii < size; ii++) {
                delete[] ptr_lst[ii];
            }
            delete[] ptr_lst;
            goneOnce = true;
        }
        cout << '\n';
    }
    return 0;
}



