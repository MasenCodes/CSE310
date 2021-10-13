#include "defns.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

string SPACE = "        ";

int monthToInt(string monthName) {
    if(monthName == "January") {
        return 1;
    }
    else if(monthName == "February") {
        return 2;
    }
    else if(monthName == "March") {
        return 3;
    }
    else if(monthName == "April") {
        return 4;
    }
    else if(monthName == "May") {
        return 5;
    }
    else if(monthName == "June") {
        return 6;
    }
    else if(monthName == "July") {
        return 7;
    }
    else if(monthName == "August") {
        return 8;
    }
    else if(monthName == "September") {
        return 9;
    }
    else if(monthName == "October") {
        return 10;
    }
    else if(monthName == "November") {
        return 11;
    }
    else if(monthName == "December") {
        return 12;
    }
    return -1;
}

void printEvent(storm_event* event) {
    cout << '\n';
    cout << SPACE << "state: " << event->state << endl;
    cout << SPACE << "event_id: " << event->event_id << endl;
    cout << SPACE << "year: " << event->year << endl;
    cout << SPACE << "event_type: " << event->event_type << endl;
    cout << SPACE << "cz_type: " << event->cz_type << endl;
    cout << SPACE << "cz_name: " << event->cz_name << endl;
    cout << '\n';
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
    string properRow;
    if(fullRow.at(len - 1) == '\r') {
        properRow = fullRow.substr(0, fullRow.length() - 1); // remove \r
    }
    else {
        properRow = fullRow;
    }

    // -1 and ? are defaults
    storm->f = fatalEvent;
    int loopIndex = 0;
    int charIndex = 0;
    string data = "-1";
    for(char c : properRow) {
        if(loopIndex == 1) {
            if(c != ',') {
                storm->state[charIndex] = c;
                charIndex++;
            }
            else {
                if(!charIndex) {
                    storm->state[0] = '?';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 3) {
            if(c != ',') {
                storm->month_name[charIndex] = c;
                charIndex++;
            }
            else {
                if(!charIndex) {
                    storm->month_name[0] = '?';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 4) {
            if(c != ',') {
                storm->event_type[charIndex] = c;
                charIndex++;
            }
            else {
                if(!charIndex) {
                    storm->event_type[0] = '?';
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
                storm->cz_name[charIndex] = c;
                charIndex++;
            }
            else {
                if(!charIndex) {
                    storm->cz_name[0] = '?';
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

bool largerThan(bst* p, storm_event* event, string field) {
    if(field == "state") {
        return p->s > event->state;
    }
    else if(field == "month_name") {
        return monthToInt(p->s) > monthToInt(event->month_name);
    }
    return false;
}

bool equal(bst* p, storm_event* event, string field) {
    if(field == "state") {
        return p->s == event->state;
    }
    else if(field == "month_name") {
        return monthToInt(p->s) == monthToInt(event->month_name);
    }
    return false;
}

void findAndPrint(bst* head, string leftBound, string rightBound, int year, string field) {
    // traverse the tree with the given field for the query and print out matching results
    if(field == "state") {

    }
    else if(field == "month_name") {

    }
}

void addToTree(bst* head, storm_event* event, int eventIndex, string field) {
    // left > right
    bst* p = head;
    while(p->left and p->right) {
        if (equal(p, event, field)) { // compare by id
            if (largerThan(p, event, field)) {
                p = p->left;
            }
            else { // p->event_id < event->event_id
                p = p->right;
            }
        }
        else if (largerThan(p, event, field)) {
            p = p->left;
        }
        else {  // p->s < event->state
            p = p->right;
        }
    }
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
    if(p->left) {
        p->right = temp;
    }
    else {
        p->left = temp;
    }
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        // collect year bounds and create data to them
        int startYear = atoi(argv[1]);
        int upTo = atoi(argv[2]);

        // for creating memory of the csv files
        string detail_row;
        string fatal_row;
        fstream detailsFile;
        fstream fatalitiesFile;
        string details_file;
        int lineCount[upTo];

        // create struct array and initialize from files
        annual_storms* storms[upTo];
        for(int ii=0; ii<upTo; ii++) {
            // open file and prepare variables
            details_file = "details-" + to_string((startYear + ii)) + ".csv";
            lineCount[ii] = numberOfLines(details_file) - 1;
            detailsFile.open(details_file, fstream::in);
            getline(detailsFile, detail_row); // throw away first line

            // make a new annual storm
            storms[ii] = new annual_storms;
            storms[ii]->year = startYear + ii;
            storms[ii]->events = new storm_event[lineCount[ii]];

            // get each line of the file
            int index = 0;
            while(getline(detailsFile, detail_row)) {
                // add the event
                addToStorm(&(storms[ii]->events[index]), detail_row);

                index++;
            }
        }

        // handle range queries here
        string line;
        string queries[5];  // type = 0 | year = 1 | field = 2 | leftBound = 3 | rightBound = 4
        string numberOfQueries;
        getline(cin, numberOfQueries); // first line is always number
        numberOfQueries = numberOfQueries.substr(0, numberOfQueries.length() - 1); // remove carriage return

        cout << numberOfQueries << "\n\n"; // start the printing process

        // read all queries
        while(getline(cin, line)) {
            // load the line
            int queryIndex = 0;
            string temp;
            for(char c: line) {
                if(c == ' ') {
                    queries[queryIndex] = temp;
                    queryIndex++;
                    temp = "";
                }
                else if(c != '\"' and c != '\r') {
                    temp += c;
                }
            }
            queries[4] = temp;

            // build the tree for each query
            bst* head = new bst;
            if(queries[1] == "all") {  // get all the years supplied from argv
                for(int ii=0; ii<upTo; ii++) {
                    for(int jj=0;jj<lineCount[ii]; jj++) {
                        addToTree(head, &(storms[ii]->events[jj]), jj, queries[2]);
                    }
                }
            }
            else {  // get a select year
                int stormIndex = stoi(queries[1]) - startYear; // the index of the needed storm in storms
                for(int jj=0;jj<lineCount[stormIndex]; jj++) {
                    addToTree(head, &(storms[stormIndex]->events[jj]), jj, queries[2]);
                }
            }

            // find the matching events and print them
            cout << "Query:" << line << "\n\n";
            // findAndPrint(head, queries[3], queries[4], stoi(queries[1]), queries[2]);
        }
        cout << "\n\n";
    }
    return 0;
}