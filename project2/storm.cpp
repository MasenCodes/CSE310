#include "defns.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>


using namespace std;

string SPACE = "        ";
int HASH_TABLE_SIZE = 2293;


void printEvent(storm_event* event, string field) {
    cout << '\n';
    if (field == "state") {
        if (strcmp(event->state, "?") != 0) {
            cout << SPACE << "State: " << event->state << endl;
        }
    }
    else {
        if (strcmp(event->month_name, "?") != 0) {
            cout << SPACE << "Month Name: " << event->month_name << endl;
        }
    }
    if (event->event_id) {
        cout << SPACE << "Event ID: " << event->event_id << endl;
    }
    if (event->year) {
        cout << SPACE << "Year: " << event->year << endl;
    }
    if (strcmp(event->event_type, "?") != 0) {
        cout << SPACE << "Event Type: " << event->event_type << endl;
    }
    if (event->cz_type != '?') {
        cout << SPACE << "County/Zone Type: " << event->cz_type << endl;
    }
    if (event->cz_name[0] != '?') {
        cout << SPACE << "County/Zone Name: " << event->cz_name << endl;
    }
    else {
        cout << SPACE << "County/Zone Name: " << endl;
    }
}

void printFatality(fatality_event* fatality) {
    cout << "Fatality ID: " << fatality->fatality_id << endl;
    cout << "Event ID: " << fatality->event_id << endl;
    cout << "Fatality Type: " << fatality->fatality_type << endl;
    cout << "Fatality Date: " << fatality->fatality_date << endl;
    cout << "Fatality Age: " << fatality->fatality_age << endl;
    cout << "Fatality Sex: " << fatality->fatality_sex << endl;
    cout << "Fatality Location: " << fatality->fatality_location << endl;
}

int numberOfLines(string fileName) {
    fstream file;
    file.open(fileName, fstream::in);
    string temp;
    int count = 0;
    while(getline(file, temp)) {
        count++;
    }
    file.close();
    return count;
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

    // fixing the bad input we were given
    int len = fullRow.length();
    string properRow;
    if(fullRow.at(len - 1) == '\r') {
        properRow = fullRow.substr(0, fullRow.length() - 1); // remove \r
    }
    else {
        properRow = fullRow;
    }

    // -1 and ? are defaults
    int loopIndex = 0;
    int charIndex = 0;
    string data = "-1";
    for(char c : properRow) {
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
                fatal->fatality_date[charIndex] = c;
                charIndex++;
            }
            else {
                if (!charIndex) {
                    fatal->fatality_date[0] = '?';
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
            fatal->fatality_location[charIndex] = c;
            charIndex++;
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
    }
}

void addToStorm(storm_event* storm, string fullRow, fatality_event* fatalEvent= nullptr) {
    // 0 = EVENT_ID          7 = INJURIES_DIRECT
    // 1 = STATE             8 = INJURIES_INDIRECT
    // 2 = YEAR              9 = DEATHS_DIRECT
    // 3 = MONTH_NAME       10 = DEATHS_INDIRECT
    // 4 = EVENT_TYPE       11 = DAMAGE_PROPERTY
    // 5 = CZ_TYPE          12 = DAMAGE_CROPS
    // 6 = CZ_NAME

    // fixing the bad input we were given
    int len = fullRow.length();
    // -1 and ? are defaults
    storm->f = fatalEvent;
    int loopIndex = 0;
    int charIndex = 0;
    string data = "-1";
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
// ------------------------------ BST Algorithms -------------------------------------

// ----------------------------- Heap Algorithms -------------------------------------
void swap(heap_entry* a, heap_entry* b) {

}
void max_heapify(heap_entry* h, int index, int size) {

}
// ----------------------------- Heap Algorithms -------------------------------------

// ----------------------------- Hash Algorithms -------------------------------------
int hashID(int event_id) {
    return event_id % HASH_TABLE_SIZE;
}

hash_table_entry* convertFromEvent(storm_event* event, int index) {
    auto* entry = new hash_table_entry;
    entry->event_id = event->event_id;
    entry->event_index = index;
    entry->year = event->year;
    return entry;
}

void insertEntry(hash_table_entry* table[], hash_table_entry* entry) {
    int key = hashID(entry->event_id);
    if(table[key]->next == nullptr) {
        table[key]->next = entry;
    }
    else {
        hash_table_entry* temp = table[key]->next;
        table[key]->next = entry;
        entry->next = temp;
    }
}

// ----------------------------- Hash Algorithms -------------------------------------
int main(int argc, char * argv[]) {
    if (argc > 1) {
        // collect year bounds and create data to them
        int startYear = atoi(argv[1]);
        int upTo = atoi(argv[2]);

        // for creating memory of the csv files
        int lineCount[upTo];

        // create struct array and initialize from files
        auto* storms = new annual_storms[upTo];
        auto* table = new hash_table_entry[HASH_TABLE_SIZE];
        for (int ii = 0; ii < upTo; ii++) {
            string detail_row;
            fstream detailsFile;
            string details_file;
            // open file and prepare variables
            details_file = "details-" + to_string(startYear + ii) + ".csv";
            //lineCount[ii] = numberOfLines(details_file) - 1;
            detailsFile.open(details_file);
            getline(detailsFile, detail_row); // throw away first line
            string temp;
            int count = 0;
            while(getline(detailsFile, temp)) {
                count++;
            }
            lineCount[ii] = count;
            detailsFile.clear();
            detailsFile.seekg(0);
            getline(detailsFile, detail_row); // throw away first line
            // make annual storm
            storms[ii].year = startYear + ii;
            storms[ii].events = new storm_event[lineCount[ii]];

            // get each line of the file
            int index = 0;
            while (getline(detailsFile, detail_row)) {
                // add the event
                addToStorm(&(storms[ii].events[index]), detail_row);
                insertEntry(&table, convertFromEvent(&(storms[ii].events[index]), index));
                index++;
            }
            //detailsFile.clear();
            detailsFile.close();
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
                if (c == ' ' and not inPar) {  // this is breaking 1966
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
            queries[4] = temp;

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
            } else {  // get a select year
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
            cout << "\n";
            cout << "Query:" << line << "\n\n";
            int check = 0;
            findAndPrint(head, queries[3], queries[4], queries[2], upTo, storms, &check);
            if (check == 0) {
                cout << "\n";
                cout << SPACE << "No storm events found for the given range";
                cout << '\n';
            }
            cout << "\n";
            deleteTree(head);
            head = nullptr;
        }
        cout << "\n\n";
    }
    return 0;
}