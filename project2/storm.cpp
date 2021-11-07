#include "defns.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>


using namespace std;


void printEvent(storm_event* event, string field) {
    cout << '\n';
    if (field == "state") {
        if (strcmp(event->state, "?") != 0) {
            cout << "State: " << event->state << endl;
        }
    }
    else {
        if (strcmp(event->month_name, "?") != 0) {
            cout << "Month Name: " << event->month_name << endl;
        }
    }
    if (event->event_id) {
        cout << "Event ID: " << event->event_id << endl;
    }
    if (event->year) {
        cout << "Year: " << event->year << endl;
    }
    if (strcmp(event->event_type, "?") != 0) {
        cout << "Event Type: " << event->event_type << endl;
    }
    if (event->cz_type != '?') {
        cout << "County/Zone Type: " << event->cz_type << endl;
    }
    if (event->cz_name[0] != '?') {
        cout << "County/Zone Name: " << event->cz_name << endl;
    }
    else {
        cout << "County/Zone Name: " << endl;
    }
}

void printNewEvent(storm_event* event) {
    cout << '\n';
    if (event->event_id) {
        cout << "Event ID: " << event->event_id << endl;
    }
    if (strcmp(event->state, "?") != 0) {
        cout << "State: " << event->state << endl;
    }
    if (event->year) {
        cout << "Year: " << event->year << endl;
    }
    if (strcmp(event->month_name, "?") != 0) {
        cout << "Month Name: " << event->month_name << endl;
    }
    if (strcmp(event->event_type, "?") != 0) {
        cout << "Event Type: " << event->event_type << endl;
    }
    if (event->cz_type != '?') {
        cout << "County/Zone Type: " << event->cz_type << endl;
    }
    if (event->cz_name[0] != '?') {
        cout << "County/Zone Name: " << event->cz_name << endl;
    }
    else {
        cout << "County/Zone Name: " << endl;
    }
    cout << "Injuries Direct: " << event->injuries_direct << endl;
    cout << "Injuries Indirect: " << event->injuries_indirect << endl;
    cout << "Deaths Direct: " << event->deaths_direct << endl;
    cout << "Deaths Indirect: " << event->deaths_indirect << endl;
    cout << "Damage Property: $" << event->damage_property << endl;
    cout << "Damage Crops: $" << event->damage_crops << endl;
}

void printFatality(fatality_event* fatality, string space="") {
    if (fatality->fatality_id) {
        cout << space << "Fatality ID: " << fatality->fatality_id << endl;
    }
    if (fatality->event_id) {
        cout << space << "Event ID: " << fatality->event_id << endl;
    }
    if (fatality->fatality_type != '?') {
        cout << space << "Fatality Type: " << fatality->fatality_type << endl;
    }
    else {
        cout << space << "Fatality Type: " << endl;
    }
    if (strcmp(fatality->fatality_date, "?") != 0) {
        cout << space << "Fatality Date: " << fatality->fatality_date << endl;
    }
    else {
        cout << space << "Fatality Date: " << endl;
    }
    if (fatality->fatality_age != -1) {
        cout << space << "Fatality Age: " << fatality->fatality_age << endl;
    }
    else {
        cout << space << "Fatality Age: " << endl;
    }
    if (fatality->fatality_sex != '?') {
        cout << space << "Fatality Sex: " << fatality->fatality_sex << endl;
    }
    else {
        cout << space << "Fatality Sex: " << endl;
    }
    if (strcmp(fatality->fatality_location, "?") != 0) {
        cout << space << "Fatality Location: " << fatality->fatality_location << endl;
    }
    else {
        cout << space << "Fatality Location: " << endl;
    }
}

bool isPrime(int num) {
    for (int ii=2; ii < num; ii++)
        if (num % ii == 0)
            return false;
    return true;
}

int getHashSize(int upTo, int startYear) {
    int totalCount = 0;
    for(int ii=0; ii < upTo; ii++) {
        string fileName = "details-" + to_string(startYear + ii) + ".csv";
        fstream file;
        file.open(fileName, fstream::in);
        string temp;
        getline(file, temp); // throw away first line
        int count = 0;
        while(getline(file, temp)) {
            count++;
        }
        file.close();
        totalCount += count;
    }
    totalCount = totalCount * 3;
    while(!isPrime(totalCount)) {
        totalCount += 1;
    }
    return totalCount;
}

int convert(string val) {
    int len = val.length();
    // cut off letter and -1
    if(val[len - 1] == 'k' or val[len - 1] == 'K') {
        return int(1000 * std::stof(val.substr(2, len - 3)));
    }
    else if(val[len - 1] == 'm' or val[len - 1] == 'M') {
        return int(1000000 * std::stof(val.substr(2, len - 3)));
    }
    else if(val[len - 1] == 'b' or val[len - 1] == 'B') {
        return int(1000000000 * std::stof(val.substr(2, len - 3)));
    }
    // default -1
    else if(len == 2){
        return stoi(val);
    }
    // cut of -1 at beginning
    else {
        return stoi(val.substr(2, len - 2));
    }
}

void addToFatality(fatality_event* fatal, string fullRow) {
    // 0 = FATALITY_ID      4 = FATALITY_AGE
    // 1 = EVENT_ID         5 = FATALITY_SEX
    // 2 = FATALITY_TYPE    6 = FATALITY_LOCATION
    // 3 = FATALITY_DATE

    // -1 and ? are defaults
    int loopIndex = 0;
    int charIndex = 0;
    string data = "-1";
    for(char c : fullRow) {
        if(loopIndex == 2) {
            if(c != ',') {
                fatal->fatality_type = c;
                charIndex++;
            }
            else {
                if (!charIndex) {
                    fatal->fatality_type = '?';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 3) {
            if (c != ',') {
                if(charIndex < 24) {
                    fatal->fatality_date[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 24) {
                    fatal->fatality_date[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if (!charIndex) {
                    fatal->fatality_date[0] = '?';
                    fatal->fatality_date[1] = '\0';
                }
                else if (charIndex <= 24) {
                    fatal->fatality_date[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 5) {
            if(c != ',') {
                fatal->fatality_sex = c;
                charIndex++;
            }
            else {
                if (!charIndex) {
                    fatal->fatality_sex = '?';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 6) {
            if (c != ',') {
                if(charIndex < 29) {
                    fatal->fatality_location[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 29) {
                    fatal->fatality_date[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if (!charIndex) {
                    fatal->fatality_location[0] = '?';
                    fatal->fatality_location[1] = '\0';
                }
                else if (charIndex <= 29) {
                    fatal->fatality_location[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(c == ',') {
            if(loopIndex == 0) {
                fatal->fatality_id = convert(data);
            }
            else if(loopIndex == 1) {
                fatal->event_id = convert(data);
            }
            else if (loopIndex == 4) {
                fatal->fatality_age = convert(data);
            }
            data = "-1";
            loopIndex++;
        }
        else {
            data += c;
        }
    }
    if(!charIndex) {
        fatal->fatality_location[0] = '?';
        fatal->fatality_location[1] = '\0';
    }
    else {
        fatal->fatality_location[charIndex] = '\0';
    }
    fatal->next = nullptr;
}

void addToStorm(storm_event* storm, string fullRow) {
    // 0 = EVENT_ID          7 = INJURIES_DIRECT
    // 1 = STATE             8 = INJURIES_INDIRECT
    // 2 = YEAR              9 = DEATHS_DIRECT
    // 3 = MONTH_NAME       10 = DEATHS_INDIRECT
    // 4 = EVENT_TYPE       11 = DAMAGE_PROPERTY
    // 5 = CZ_TYPE          12 = DAMAGE_CROPS
    // 6 = CZ_NAME

    // -1 and ? are defaults
    int loopIndex = 0;
    int charIndex = 0;
    string data = "-1";
    storm->f = nullptr;
    for(char c : fullRow) {
        if(loopIndex == 1) {
            if(c != ',') {
                if(charIndex < 19) {
                    storm->state[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 19) {
                    storm->state[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if(!charIndex) {
                    storm->state[0] = '?';
                    storm->state[1] = '\0';
                }
                else if (charIndex <= 19) {
                    storm->state[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 3) {
            if(c != ',') {
                if(charIndex < 14) {
                    storm->month_name[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 14) {
                    storm->month_name[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if(!charIndex) {
                    storm->month_name[0] = '?';
                    storm->month_name[1] = '\0';
                }
                else if (charIndex <= 14) {
                    storm->month_name[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 4) {
            if(c != ',') {
                if(charIndex < 29) {
                    storm->event_type[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 29) {
                    storm->event_type[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if(!charIndex) {
                    storm->event_type[0] = '?';
                    storm->event_type[1] = '\0';
                }
                else if (charIndex <= 29) {
                    storm->event_type[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }

        }
        else if(loopIndex == 5) {
            if(c != ',') {
                storm->cz_type = c;
                charIndex++;
            }
            else {
                if(!charIndex) {
                    storm->cz_type = '?';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 6) {
            if(c != ',') {
                if(charIndex < 34) {
                    storm->cz_name[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 34) {
                    storm->cz_name[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if(!charIndex) {
                    storm->cz_name[0] = '?';
                    storm->cz_name[1] = '\0';
                }
                else if (charIndex <= 34) {
                    storm->cz_name[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }

        }
        else if(c == ',') {
            if(loopIndex == 0) {
                storm->event_id = convert(data);
            }
            else if(loopIndex == 2) {
                storm->year = convert(data);
            }
            else if(loopIndex == 7) {
                storm->injuries_direct = convert(data);
            }
            else if(loopIndex == 8) {
                storm->injuries_indirect = convert(data);
            }
            else if(loopIndex == 9) {
                storm->deaths_direct = convert(data);
            }
            else if(loopIndex == 10) {
                storm->deaths_indirect = convert(data);
            }
            else if(loopIndex == 11) {
                storm->damage_property = convert(data);
            }
            data = "-1";
            loopIndex++;
        }
        else {
            data += c;
        }
    }
    storm->damage_crops = convert(data);
}

// ------------------------------ BST Algorithms -------------------------------------
bool lessThan(bst* p, storm_event* event, string field) {
    if(field == "state") {
        if (strcmp(p->s, event->state) > 0) {
            //cout << p->s << " is less than " << event->state << endl;
            return true;
        }
        return false;
    }
    else if(field == "month_name") {
        if (strcmp(p->s, event->month_name) > 0) {
            return true;
        }
        return false;
    }
}

bool equal(bst* p, storm_event* event, string field) {
    if(field == "state") {
        if(strcmp(p->s, event->state) == 0) {
            return true;
        }
        return false;
    }
    else if(field == "month_name") {
        if(strcmp(p->s, event->month_name) == 0) {
            return true;
        }
        return false;
    }
}

void findAndPrint(bst* head, string leftBound, string rightBound, string field, int stormsLen, annual_storms storms[], int* count) {
    // traverse the tree with the given field for the query and print out matching results
    if(head != nullptr) {
        findAndPrint(head->left, leftBound, rightBound, field, stormsLen, storms, count);
        if(field == "state") {
            for(int ii=0; ii<stormsLen; ii++) {
                storm_event storm = storms[ii].events[head->event_index];
                if(storm.event_id == head->event_id) {
                    if(storm.state >= leftBound and storm.state <= rightBound) {
                        printEvent(&storm, field);
                        (*count)++;
                    }
                }
            }
        }
        else if(field == "month_name") {
            for(int ii=0; ii<stormsLen; ii++) {
                storm_event storm = storms[ii].events[head->event_index];
                if(storm.event_id == head->event_id) {
                    if(storm.month_name >= leftBound and storm.month_name <= rightBound) {
                        printEvent(&storm, field);
                        (*count)++;
                    }
                }
            }
        }
        findAndPrint(head->right, leftBound, rightBound, field, stormsLen, storms, count);
    }
}


bst* createNode(storm_event* event, int eventIndex, string field) {
    bst* temp = new bst;
    if(field == "state") {
        temp->s = event->state;
    }
    else {
        temp->s = event->month_name;
    }
    temp->event_id = event->event_id;
    temp->year = event->year;
    temp->event_index = eventIndex;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

bst* insertNode(bst* p, storm_event* event, int eventIndex, string field) {
    if (p == nullptr) {
        return createNode(event, eventIndex, field);
    }
    if (equal(p, event, field)) { // compare by id
        if (p->event_id > event->event_id) {
            p->left = insertNode(p->left, event, eventIndex, field);
        }
        else {
            p->right = insertNode(p->right, event, eventIndex, field);
        }
    }
    else if (lessThan(p, event, field)) {
        p->left = insertNode(p->left, event, eventIndex, field);
    }
    else {
        p->right = insertNode(p->right, event, eventIndex, field);
    }
    return p;
}

void deleteTree(bst* head) {
    if(head == nullptr) {
        return;
    }
    deleteTree(head->left);
    deleteTree(head->right);
    delete head;
}
// ------------------------------ End BST Algorithms ---------------------------------

// ----------------------------- Heap Algorithms -------------------------------------

bool largerThan(heap_entry* lrg, heap_entry* sml) {
    if(lrg->damage_amount == sml->damage_amount) {
        if(lrg->year == sml->year) {
            return lrg->event_id > sml->event_id; // innermost compare case (will never be equal)
        }
        return lrg->year > sml->year; // not equal just compare
    }
    return lrg->damage_amount > sml->damage_amount; // not equal just compare
}

void max_heapify(heap_entry* h[], int index, int size) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int largest = index;

    if(left < size and largerThan(h[left], h[largest])) {
        largest = left;
    }
    if(right < size and largerThan(h[right], h[largest])) {
        largest = right;
    }
    if(largest != index) {
        swap(h[index], h[largest]);
        max_heapify(h, largest, size);
    }
}

void build_heap(heap_entry* h[], int size) {
    for(int ii=(size - 1)/2; ii >= 0; ii--) {
        max_heapify(h, ii, size);
    }
}

heap_entry deleteHeapEntry(heap_entry* h[], int* size, int index) {
    heap_entry deleted = *h[index]; // this is what we return
    swap(h[index], h[*size - 1]);
    delete h[*size - 1]; // free memory
    *size -= 1; // adjust size
    max_heapify(h, 0, *size);
    return deleted;
}
// ----------------------------- End Heap Algorithms ---------------------------------

// ----------------------------- Hash Algorithms -------------------------------------
int hashID(int event_id, int tableSize) {
    return event_id % tableSize;
}

hash_table_entry* convertFromEvent(storm_event* event, int index) {
    auto* entry = new hash_table_entry;
    entry->event_id = event->event_id;
    entry->event_index = index;
    entry->year = event->year;
    entry->event_id = event->event_id;
    entry->next = nullptr;
    return entry;
}

int findEntryIndex(hash_table_entry* table[], int event_id, int tableSize) {
    // finds the event index for given event id, returns -1 if not found
    int key = hashID(event_id, tableSize);
    if(key > tableSize) {
        return -1;
    }
    hash_table_entry* entry = table[key];
    if(entry == nullptr) {
        return -1;
    }
    while(entry->event_id != event_id) {
        if(entry->next == nullptr and entry->event_id != event_id) {
            return -1;
        }
        entry = entry->next;
    }
    return entry->event_index;
}

void insertEntry(hash_table_entry* table[], storm_event* event, int tableSize, int index) {
    int key = hashID(event->event_id, tableSize);
    if(table[key] == nullptr) {
        table[key] = convertFromEvent(event, index);
    }
    else {
        hash_table_entry* temp = table[key];
        table[key] = convertFromEvent(event, index);;
        table[key]->next = temp;
    }
}

void insertFatality(storm_event* event, fatality_event* fatal) {
    if(event->f == nullptr) {
        event->f = fatal;
        event->f->next = nullptr;
    }
    else {
        fatality_event* trav = event->f;
        while(trav->next != nullptr and trav->fatality_id > fatal->fatality_id) {
            trav = trav->next;
        }
        fatality_event* temp = trav;
        trav = fatal;
        trav->next = temp;
    }
}
// ----------------------------- End Hash Algorithms ---------------------------------

int main(int argc, char * argv[]) {
    if (argc > 1) {
        // collect year bounds and create data to them
        int startYear = atoi(argv[1]);
        int upTo = atoi(argv[2]);
        int tableSize = getHashSize(upTo, startYear);

        // for creating memory of the csv files
        int lineCount[upTo];

        // create struct array and initialize from files
        auto* storms = new annual_storms[upTo];
        // create and initialize the hash table
        hash_table_entry* table[tableSize];
        for (int ii = 0; ii < tableSize; ii++) {
            table[ii] = nullptr;
        }
        for (int ii = 0; ii < upTo; ii++) {
            // get the details for the given year
            string detail_row;
            fstream detailsFile;
            string details_file;
            details_file = "details-" + to_string(startYear + ii) + ".csv";
            detailsFile.open(details_file);
            getline(detailsFile, detail_row); // throw away first line
            string temp;
            // get the line count for file
            int count = 0;
            while(getline(detailsFile, temp)) {
                count++;
            }
            lineCount[ii] = count;
            detailsFile.clear();  // reset file
            detailsFile.seekg(0); // reset file
            getline(detailsFile, detail_row); // throw away first line

            // make annual storm
            storms[ii].year = startYear + ii;
            storms[ii].events = new storm_event[lineCount[ii]];

            // get each line of the details file
            int index = 0;
            while (getline(detailsFile, detail_row)) {
                // add the event
                addToStorm(&(storms[ii].events[index]), detail_row);
                insertEntry(table, &(storms[ii].events[index]), tableSize, index);
                index++;
            }
            detailsFile.close();

            // get the fatalities for given year
            string fatal_row;
            fstream fatalitiesFile;
            string fatalities_file;
            fatalities_file = "fatalities-" + to_string(startYear + ii) + ".csv";
            fatalitiesFile.open(fatalities_file);
            getline(fatalitiesFile, fatal_row); // throw away first line

            // get each line for the fatalities file and add to respective event
            while(getline(fatalitiesFile, fatal_row)) {
                auto* fatalEntry = new fatality_event;
                addToFatality(fatalEntry, fatal_row);
                int eventIndex = findEntryIndex(table, fatalEntry->event_id, tableSize);
                insertFatality(&(storms[ii].events[eventIndex]), fatalEntry); // insert the fatality into the events LL
            }
            fatalitiesFile.close();
        }

        // handle range queries here
        string line;
        string queries[5];  // type = 0 | year = 1 | field = 2 | leftBound = 3 | rightBound = 4
        string numberOfQueries;
        getline(cin, numberOfQueries); // first line is always number

        cout << numberOfQueries << '\n'; // start the printing process

        // build the tree for each query
        bst *head = nullptr;
        // read all queries
        while (getline(cin, line)) {
            // load the line
            int queryIndex = 0;
            bool inPar = false;
            string temp;
            for (char c: line) {
                if (c == ' ' and not inPar) {
                    queries[queryIndex] = temp;
                    queryIndex++;
                    temp = "";
                } else if (c != '\"' and c != '\r') {
                    temp += c;
                }
                else if (c == '\"') {
                    if(not inPar) {
                        inPar = true;
                    }
                    else {
                        inPar = false;
                    }
                }
            }
            queries[queryIndex] = temp;

            // start by printing the query
            cout << "\n";
            cout << "Query: " << line << "\n";

            // Handling of all query types:
            if (queries[0] == "range"){  // range query
                bool first = true;
                if (queries[1] == "all") {  // get all the years supplied from argv
                    for (int ii = 0; ii < upTo; ii++) {
                        for (int jj = 0; jj < lineCount[ii]; jj++) {
                            if (first) {
                                head = insertNode(head, &(storms[ii].events[jj]), jj, queries[2]);
                                first = false;
                            } else {
                                insertNode(head, &(storms[ii].events[jj]), jj, queries[2]);
                            }
                        }
                    }

                }
                else { // get a select year
                    int stormIndex = stoi(queries[1]) - startYear; // the index of the needed storm in storms
                    for (int jj = 0; jj < lineCount[stormIndex]; jj++) {
                        if (first) {
                            head = insertNode(head, &(storms[stormIndex].events[jj]), jj, queries[2]);
                            first = false;
                        } else {
                            insertNode(head, &(storms[stormIndex].events[jj]), jj, queries[2]);
                        }
                    }
                }
                // find the matching events and print them
                int check = 0;
                findAndPrint(head, queries[3], queries[4], queries[2], upTo, storms, &check);
                if (check == 0) {
                    cout << "\n";
                    cout << '\t' << "No storm events found for the given range";
                }
                deleteTree(head);
                head = nullptr;
            }
            else if (queries[2] == "fatality") { // find max fatality
                int size;
                int topMost = stoi(queries[4]);
                heap_entry** heap;
                if (queries[3] == "all") { // all years
                    // get the size for the heap
                    size = 0;
                    for(int ii=0; ii<upTo; ii++) {
                        size += lineCount[ii];
                    }
                    // make the array for heap
                    heap = new heap_entry*[size];
                    int index = 0;
                    for(int ii=0; ii<upTo; ii++) {
                        for(int jj=0; jj<lineCount[ii]; jj++, index++) {
                            heap[index] = new heap_entry;
                            heap[index]->event_index = jj;
                            heap[index]->year = storms[ii].events[jj].year;
                            heap[index]->event_id = storms[ii].events[jj].event_id;
                            heap[index]->damage_amount = storms[ii].events[jj].deaths_direct +
                                                      storms[ii].events[jj].deaths_indirect;
                        }
                    }
                }
                else { // select year
                    // calculate years and indexing
                    int year = stoi(queries[3]);
                    int index = year - startYear;
                    size = lineCount[index];
                    // make the array for heap
                    heap = new heap_entry*[size];
                    for (int ii = 0; ii < size; ii++) {
                        heap[ii] = new heap_entry;
                        heap[ii]->event_index = ii;
                        heap[ii]->year = storms[index].events[ii].year;
                        heap[ii]->event_id = storms[index].events[ii].event_id;
                        heap[ii]->damage_amount = storms[index].events[ii].deaths_direct +
                                storms[index].events[ii].deaths_indirect;
                    }
                }
                // build the heap after the respective array was created
                build_heap(heap, size);
                while(size != 1) {
                    heap_entry print = deleteHeapEntry(heap, &size, 0);
                    if(topMost) {
                        cout << "\n";
                        for(int ii=0; ii<upTo; ii++) {
                            if(storms[ii].events[print.event_index].event_id == print.event_id) {
                                printFatality(storms[ii].events[print.event_index].f);
                            }
                        }
                        topMost -= 1;
                    }
                }
                // finish deleting the heap
                delete heap[0];
                heap = nullptr;
            }
            else if (queries[1] == "max") { // find max damage_type
                int size;
                int topMost = stoi(queries[4]);
                heap_entry** heap;
                if (queries[2] == "all") { // all years
                    // get the size for the heap
                    size = 0;
                    for(int ii=0; ii<upTo; ii++) {
                        size += lineCount[ii];
                    }

                    // make the array for heap
                    heap = new heap_entry*[size];
                    int index = 0;
                    for(int ii=0; ii<upTo; ii++) {
                        for(int jj=0; jj<lineCount[ii]; jj++, index++) {
                            heap[index] = new heap_entry;
                            heap[index]->event_index = jj;
                            heap[index]->year = storms[ii].events[jj].year;
                            heap[index]->event_id = storms[ii].events[jj].event_id;
                            if(queries[3] == "damage_crops") {
                                heap[index]->damage_amount = storms[ii].events[jj].damage_crops;
                            }
                            else { // damage property
                                heap[index]->damage_amount = storms[ii].events[jj].damage_property;
                            }
                        }
                    }
                }
                else { // select year
                    // calculate years and indexing
                    int year = stoi(queries[2]);
                    int index = year - startYear;
                    size = lineCount[index];

                    // make the array for heap
                    heap = new heap_entry*[size];
                    for (int ii = 0; ii < size; ii++) {
                        heap[ii] = new heap_entry;
                        heap[ii]->event_index = ii;
                        heap[ii]->year = storms[index].events[ii].year;
                        heap[ii]->event_id = storms[index].events[ii].event_id;
                        if (queries[3] == "damage_crops") {
                            heap[ii]->damage_amount = storms[index].events[ii].damage_crops;
                        } else { // damage property
                            heap[ii]->damage_amount = storms[index].events[ii].damage_property;
                        }
                    }
                }
                // build the heap after the respective array was created
                build_heap(heap, size);
                while(size != 1) {
                    heap_entry print = deleteHeapEntry(heap, &size, 0);
                    if(topMost) {
                        cout << "\n";
                        cout << "Event ID: " << print.event_id << "; Event Type: ";
                        for(int ii=0; ii<upTo; ii++) {
                            if(storms[ii].events[print.event_index].event_id == print.event_id) {
                                cout << storms[ii].events[print.event_index].event_type;
                            }
                        }
                        cout << "; Damage Amount: $" << print.damage_amount << endl;
                        topMost -= 1;
                    }
                }
                // finish deleting the heap
                delete heap[0];
                heap = nullptr;
            }
            else if (queries[1] == "event") { // find event in hash table to print fatalities
                int event_id = stoi(queries[2]);
                int index = findEntryIndex(table, event_id, tableSize);
                // default return -1 means invalid index
                if (index == -1) {
                    cout << '\n';
                    cout << "Storm event " << event_id << " not found" << endl;
                }
                else {
                    storm_event* found = nullptr;
                    for(int ii=0; ii<upTo; ii++) {
                        if(storms[ii].events[index].event_id == event_id) {
                            found = &(storms[ii].events[index]);
                        }
                    }
                    // print the event
                    printNewEvent(found);

                    // no fatalities were found
                    if(found->f == nullptr) {
                        cout << endl;
                        cout << '\t' << "No fatalities" << endl;
                    }
                    else {
                        // print all associated fatalities
                        fatality_event* trav = found->f;
                        do {
                            printFatality(trav);
                            if(trav->next != nullptr) {
                                trav = trav->next;
                            }
                        } while (trav->next != nullptr);
                    }
                }
            }
        }
        cout << "\n";
    }
    return 0;
}