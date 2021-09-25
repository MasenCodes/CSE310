#include <iostream>
#include <string>
#include <cstring>


using namespace std;


void merge(char* s, int l, int mid, int r, int n) {
    // sizes and index
    int leftSize = (mid-l) + 1;
    int rightSize = r-mid;
    int leftIndex = 0;
    int rightIndex = 0;

    // create new memory
    char* leftArray = new char[leftSize];
    char* rightArray = new char[rightSize];

    // fill arrays
    for(int ii=l; ii<mid + 1; ii++) {
        leftArray[leftIndex] = s[ii];
        leftIndex++;
    }
    for(int ii=mid + 1; ii<r + 1; ii++) {
        rightArray[rightIndex] = s[ii];
        rightIndex++;
    }

    // reset and create indexes and begin comparison
    leftIndex = 0, rightIndex = 0;
    int leftStart = l;
    int rightStart = mid + 1;
    int start = l;

    while(leftStart <= mid and rightStart <= r) {
        if(leftArray[leftIndex] < rightArray[rightIndex]) {
            s[start] = leftArray[leftIndex];
            leftStart++;
            leftIndex++;
        }
        else {
            s[start] = rightArray[rightIndex];
            rightStart++;
            rightIndex++;
        }
        start++;
    }

    // one will execute to finish the sort
    while(leftStart <= mid) {
        s[start] = leftArray[leftIndex];
        leftStart++;
        leftIndex++;
        start++;
    }
    while(rightStart <= r) {
        s[start] = rightArray[rightIndex];
        rightStart++;
        rightIndex++;
        start++;
    }

    // free memory
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(char* s, int l, int r, int n) {
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


void insertionSort(char* s, int n) {
    for(int ii=1; ii<n; ii++) {
        char temp = s[ii];
        int jj = ii - 1;

        while(jj>=0 and s[jj] > temp) {
            s[jj+1] = s[jj];
            jj -= 1;
        }
        s[jj+1] = temp;
    }
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if (string(argv[1]) == "insertion") {
            string input;
            int sortedIndex = -1;
            int stringSize = 0;
            bool goneOnce = false;
            while (getline(cin, input)) {
                // skip blanks
                if(cin.eof()) {
                    break;
                }
                if(input.empty()) {
                    cout << endl;
                    continue;
                }
                if(0 > sortedIndex) { // grab the original strings index given from encode
                    sortedIndex = stoi(input);
                    continue;
                }

                else {
                    // determine the len of original string
                    string value = "0";
                    for(char c: input) {
                        if(c < 58 and c > 47) {
                            value += c;
                        }
                        else {
                            stringSize += stoi(value);
                            value = "0";
                        }
                    }
                }

                // declare pointer and fill array
                char* first = new char[stringSize];
                char* last = new char[stringSize];

                // fill the first column of og string in both arrays
                string value = "0";
                bool firstSpace = false;
                for(int ii=0, jj=0; ii<stringSize and jj<input.size(); ii++) {
                    if(input.at(jj) == 32 and !firstSpace) {  // skip spaces
                        ii--;
                        jj++;
                        firstSpace = true;
                        continue;
                    }
                    if(input.at(jj) < 58 and input.at(jj) > 47) {  // find numbers
                        value += input.at(jj);
                        ii--;
                    }
                    else {
                        for(int kk=0; kk<stoi(value); kk++) {  // add char k times
                            first[ii] = input.at(jj);
                            last[ii] = input.at(jj);
                            ii++;
                        }
                        ii--; // loop will take care of one of these done in previous loop
                        value = "0";
                    }
                    firstSpace = false;
                    jj++;
                }

                // sort the column to achieve "last" column from og string
                insertionSort(last, stringSize);

                // comparison variables, fill used with zeros for booleans
                int posArray[stringSize];
                int usedArray[stringSize];
                for(int ii=0; ii<stringSize; ii++) {
                    usedArray[ii] = 0;
                }

                // decode arrays
                for(int ii=0; ii<stringSize; ii++) {  // index to access last and assigning index for first
                    for(int jj=0; jj<stringSize; jj++) {  // index for first
                        if(first[ii] == last[jj] and usedArray[jj] != 1) {
                            usedArray[jj] = 1;
                            posArray[jj] = ii;
                            break;
                        }
                    }
                }

                // make the original string
                char* original = new char[stringSize];
                int pos = posArray[sortedIndex];
                for(int ii=stringSize - 1; ii>=0; ii--) {
                    original[ii] = first[pos];
                    pos = posArray[pos];
                }

                // carry out decoded string
                for(int ii=0; ii<stringSize; ii++) {
                    cout << original[ii];
                }
                if(stringSize) {
                    cout << endl;
                }

                // clean up and reset variables
                delete[] original;
                delete[] first;
                delete[] last;
                sortedIndex = -1;
                stringSize = 0;
                goneOnce = true;
            }
        }
        else if (string(argv[1]) == "mergesort") {
            string input;
            int sortedIndex = -1;
            int stringSize = 0;
            bool goneOnce = false;
            while (getline(cin, input)) {
                // skip blanks
                if(cin.eof()) {
                    break;
                }
                if(input.empty()) {
                    cout << endl;
                    continue;
                }
                if(0 > sortedIndex) { // grab the original strings index given from encode
                    sortedIndex = stoi(input);
                    continue;
                }

                else {
                    // determine the len of original string
                    string value = "0";
                    for(char c: input) {
                        if(c < 58 and c > 47) {
                            value += c;
                        }
                        else {
                            stringSize += stoi(value);
                            value = "0";
                        }
                    }
                }

                // declare pointer and fill array
                char* first = new char[stringSize];
                char* last = new char[stringSize];

                // fill the first column of og string in both arrays
                string value = "0";
                bool firstSpace = false;
                for(int ii=0, jj=0; ii<stringSize and jj<input.size(); ii++) {
                    if(input.at(jj) == 32 and !firstSpace) {  // skip spaces
                        ii--;
                        jj++;
                        firstSpace = true;
                        continue;
                    }
                    if(input.at(jj) < 58 and input.at(jj) > 47) {  // find numbers
                        value += input.at(jj);
                        ii--;
                    }
                    else {
                        for(int kk=0; kk<stoi(value); kk++) {  // add char k times
                            first[ii] = input.at(jj);
                            last[ii] = input.at(jj);
                            ii++;
                        }
                        ii--; // loop will take care of one of these done in previous loop
                        value = "0";
                    }
                    firstSpace = false;
                    jj++;
                }

                // sort the column to achieve "last" column from og string
                mergeSort(last, 0, stringSize - 1, stringSize);

                // comparison variables, fill used with zeros for booleans
                int posArray[stringSize];
                int usedArray[stringSize];
                for(int ii=0; ii<stringSize; ii++) {
                    usedArray[ii] = 0;
                }

                // decode arrays
                for(int ii=0; ii<stringSize; ii++) {  // index to access last and assigning index for first
                    for(int jj=0; jj<stringSize; jj++) {  // index for first
                        if(first[ii] == last[jj] and usedArray[jj] != 1) {
                            usedArray[jj] = 1;
                            posArray[jj] = ii;
                            break;
                        }
                    }
                }

                // make the original string
                char* original = new char[stringSize];
                int pos = posArray[sortedIndex];
                for(int ii=stringSize - 1; ii>=0; ii--) {
                    original[ii] = first[pos];
                    pos = posArray[pos];
                }

                // carry out decoded string
                for(int ii=0; ii<stringSize; ii++) {
                    cout << original[ii];
                }
                if(stringSize) {
                    cout << endl;
                }

                // clean up and reset variables
                delete[] original;
                delete[] first;
                delete[] last;
                sortedIndex = -1;
                stringSize = 0;
                goneOnce = true;
            }

        }
    }
    return 0;
}

